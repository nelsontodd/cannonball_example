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
const cnl::fixed_point<int, -28> B = 4;
const double g = 9.81;

template <class T> void f(T) = delete;

template <int shift, typename rep, int exponent>
auto precision_shift(cnl::fixed_point<rep, exponent> x) {
  return cnl::elastic_number<cnl::digits_v<rep> + shift, exponent - shift>(x);
}

template <int new_digits, typename rep, int exponent>
auto set_precision(cnl::fixed_point<rep, exponent> x) {
  return precision_shift<new_digits - cnl::digits_v<rep>>(
      x); // consider using cnl::digits instead of numeric_limits
}

// Hopefully make_elastic_number fulfills stretch's purpose
template <typename rep, int exponent>
auto stretch(cnl::fixed_point<rep, exponent> x) {
  return cnl::elastic_number<cnl::digits_v<rep>, exponent>(x);
}

template <typename Vel> Vel hypotn(Vel a, Vel b) {
	return ::sqrt(set_precision<31>(a * a + b * b));
}

template <class Pos, class Vel = Pos, class Mass = Pos> struct cannon {
  Pos x, y;
  Vel v_x, v_y;
  Mass m;
  template <typename Time> void euler_step(Time dt) {
    x += v_x * dt;
    y += v_y * dt;
    ////drag is missing a factor of velocity
    auto drag = set_precision<31>(-B * hypotn(v_x, v_y) / m);
    auto accel_y = (drag * v_y);
    accel_y -= g;
    Vel new_accel_y = set_precision<32>(accel_y);
    Vel dv_y = set_precision<32>(accel_y) * dt;
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
    if (i > (int)(1. / dt) and i % (int)(1. / dt) == 0) {
      results << setprecision(numeric_limits<Pos>::max_digits10) << ball.x
              << ", " << ball.y << ", " << ball.v_x << ", " << ball.v_y << endl;
    }
    i += 1;
  }
}

int main() {
  using pos = cnl::fixed_point<cnl::elastic_integer<>, -15>;
  using vel = cnl::fixed_point<cnl::elastic_integer<28>,
                               -19>; // Use set_precision later
  using mass = cnl::fixed_point<cnl::elastic_integer<19>, 0>;
  cnl::fixed_point<std::int32_t, -27> dt = .01;
  // Vary dt to see where error max (vs longdouble) and min are.
  precision_experiment<pos, vel, mass>(
      "cnl_0", cnl::fixed_point<std::int32_t, -27>(.00001));
  precision_experiment<pos, vel, mass>(
      "cnl_1", cnl::fixed_point<std::int32_t, -27>(.0001));
  precision_experiment<pos, vel, mass>(
      "cnl_2", cnl::fixed_point<std::int32_t, -27>(.001));
  precision_experiment<pos, vel, mass>(
      "cnl_3", cnl::fixed_point<std::int32_t, -27>(.01));
  precision_experiment<pos, vel, mass>("cnl_4",
                                       cnl::fixed_point<std::int32_t, -27>(.1));
  precision_experiment<pos, vel, mass>("cnl_5",
                                       cnl::fixed_point<std::int32_t, -27>(1));
}
