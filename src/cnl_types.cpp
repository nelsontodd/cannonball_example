#include <cmath>
#include <cnl/elastic_integer.h>
#include <cnl/elastic_number.h>
#include <cnl/fixed_point.h>
#include <fstream>
#include <iomanip> // std::setprecision
#include <iostream>
#include <numeric>

using namespace std;
// B is chosen so that B/m = 4*10^-5, which is a sensible drag force constant.
// You can also try to make this small (eg elastic_integer<3> as rep here in place of int) to avoid using a set_precision when calculating drag, but that is actually slightly less accurate.
const cnl::fixed_point<int, -29> B = 4;
//Give g a max of 2^4 = 16 and a width of 13 to make sure we have the .01... this small size lets us avoid a set_precision when adding onto the accel_y
const cnl::fixed_point<cnl::elastic_integer<13>, -8> g = 9.81;

template <class T> void f(T) = delete;

template <int shift, typename rep, int exponent>
auto precision_shift(cnl::fixed_point<rep, exponent> x) {
  return cnl::elastic_number<cnl::digits_v<rep> + shift, exponent - shift>(x);
}

// Often, binary operations give us too much range. Leads to overflow.
// This allows us to cut unnecessary 0s off the top.
template <int new_digits, typename rep, int exponent>
auto set_precision(cnl::fixed_point<rep, exponent> x) {
  return precision_shift<new_digits - cnl::digits_v<rep>>(x);
}

template <typename rep, int exponent>
auto stretch(cnl::fixed_point<rep, exponent> x) {
  return cnl::elastic_number<cnl::digits_v<rep>, exponent>(x);
}

template <typename Vel> Vel hypotn(Vel a, Vel b) {
  // a*a + b*b here will have 57 bits without this set_precision.
  //(28*2 bits for the squaring +1 bit for the addition)
  return sqrt(set_precision<31>(a * a + b * b));
}

template <class Pos, class Vel = Pos, class Mass = Pos> struct cannon {
  Pos x, y;
  Vel v_x, v_y;
  Mass m;
  template <typename Time> void euler_step(Time dt) {
    x += v_x * dt;
    y += v_y * dt;
    ////drag is missing a factor of velocity
    // set_precision here cuts the drag from 59 to 35 bits.
    // 59 bits is not too wide, but when multiplied by v_y it becomes too wide.
		// 35 bits is the maximum here.
    auto drag = set_precision<35>(-B * hypotn(v_x, v_y) / m);
    //accel_y need
		auto accel_y = set_precision<32>(drag * v_y);
    accel_y -= g;
		//After this subtraction, accel_y has 32 bits with an exponent of -10. No need to set_precision when mult by dt.
    Vel dv_y = accel_y * dt;
    Vel dv_x = set_precision<32>(drag * v_x) * dt;
    v_x += dv_x;
    v_y += dv_y;
  }
};

template <typename Pos, typename Vel, typename Mass, typename Time>
void precision_experiment(string outfile, Time dt) {
  Mass m;
  Vel theta;
  const Vel v0 = 700;
  theta = .7853;
  m = 100000;
  cannon<Pos, Vel, Mass> ball = {0, 0, v0 * cos(theta), v0 * sin(theta), m};
  ofstream results("output/" + outfile + ".csv");
  results << "x, y, v_x, v_y" << endl;

  results << ball.x << ", " << ball.y << ", " << ball.v_x << ", " << ball.v_y
          << endl;
  uint64_t i = 0;
  while (ball.y >= 0) {
    ball.euler_step(dt);
    if (( i > (int)(1. / dt) and i % (int)(1. / dt) == 0) or ball.y <= 0) {
      results << setprecision(numeric_limits<Pos>::max_digits10) << ball.x
              << ", " << ball.y << ", " << ball.v_x << ", " << ball.v_y << endl;
    }
    i += 1;
  }
}

int main() {
  // elastic_integer has a default width of 32, no reason to change it.
  // the exponent is -15 because 2^17 is about 160k, which is a reasonable
  // upper bound in the limit of ball having no mass.
  using pos = cnl::fixed_point<cnl::elastic_integer<>, -16>;
  // 2^10 = 1024, which is a good upper bound for the velocity.
  // The width is 28 bits to avoid overflow in the hypotn function.
  using vel = cnl::fixed_point<cnl::elastic_integer<28>,
                               -18>; // Use set_precision later
  // The mass only needs nineteen digits because we only expect a max
  // size of 100k. 500k suffices. Obviously don't care about fractions.
  // but note that modifying this to be less (say 18 bits) doesnt yield
  // any error reduction.
  using mass = cnl::fixed_point<cnl::elastic_integer<19>, 0>;
  // We vary dt to get an idea of where the max and min error (difference from
  // long double) are. The answer is that it gets less accurate (compared to
  // longdouble) as the time step shrinks
  
	
	//Note that 29 bits is the most precision we can give this without having to use set_precision to avoid an undefined type (>63 bits) when multiplying by v_x or v_y.
	precision_experiment<pos, vel, mass>(
      "cnl_0", cnl::fixed_point<std::int32_t, -29>(.00001));
  precision_experiment<pos, vel, mass>(
      "cnl_1", cnl::fixed_point<std::int32_t, -29>(.0001));
  precision_experiment<pos, vel, mass>(
      "cnl_2", cnl::fixed_point<std::int32_t, -29>(.001));
  precision_experiment<pos, vel, mass>(
      "cnl_3", cnl::fixed_point<std::int32_t, -29>(.01));
  precision_experiment<pos, vel, mass>("cnl_4",
                                       cnl::fixed_point<std::int32_t, -29>(.1));
  precision_experiment<pos, vel, mass>("cnl_5",
                                       cnl::fixed_point<std::int32_t, -29>(1));
}
