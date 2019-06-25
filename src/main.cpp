#include <cmath>
#include <cnl/elastic_integer.h>
#include <cnl/elastic_number.h>
#include <cnl/fixed_point.h>
#include <fstream>
#include <iostream>
#include <numeric>

using namespace std;
const cnl::fixed_point<int, -29> B = 4; //.0004;
const double g = 9.81;                  // 98100;  // 10 nm/cs^2

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

template <typename vel_precision>
vel_precision hypotn(vel_precision a, vel_precision b) {
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
    auto drag = set_precision<10>(-B*hypotn(v_x,v_y)/m);
    //auto drag = (-B*hypotn(v_x,v_y)/m);
    // //Unsure about the result of signed and unsigned division cout<<"v_x:
    // "<<v_x<<endl; cout<<"Drag: "<<drag<<endl; cout<<"drag*v_x*dt:
    // "<<drag*v_x*dt<<endl; Vel dv_x = (drag*v_x*dt); v_x += dv_x;
    Vel dv_y = (-g) * dt;
    // cout<<"v_y: "<<v_y<<endl;
    // cout<<"dv_y: "<<dv_y<<endl;
    v_y += dv_y;
    // cout<<"v_y: "<<v_y<<endl;
  }
};

template <typename pos_precision, typename vel_precision,
          typename mass_precision>
void precision_experiment(string outfile) {
  mass_precision m;
  double theta;
  cnl::fixed_point<std::int32_t, -27> dt = .01; // 1;   // centiseconds
  const vel_precision v0 = 700;                 // 700000000; // 10 nm/cs
  cout << "v0: " << v0 << endl;
  cout << "dt: " << dt << endl;

  // cin>>theta;
  // cin>>m;
  theta = .78553;
  m = 100000;
  cout << "theta: " << theta << endl;
  cout << "mass: " << m << endl;
  cannon<pos_precision, vel_precision, mass_precision> ball = {
      0, 0, v0 * cos(theta), v0 * sin(theta), m};
  cout << "v_x:" << ball.v_x << endl;
  cout << "v_y:" << ball.v_y << endl;
  cout << "x:" << ball.x << endl;
  cout << "y:" << ball.y << endl;
  ofstream results("output/" + outfile + ".csv");
  results << "x, y, v_x, v_y" << endl;

  results << ball.x << ", " << ball.y << ", " << ball.v_x << ", " << ball.v_y
          << endl;
  // ball.euler_step(dt);
  // ball.euler_step(dt);
  // ball.euler_step(dt);
  while (ball.y >= 0) {
    ball.euler_step(dt);
    results << ball.x << ", " << ball.y << ", " << ball.v_x << ", " << ball.v_y
            << endl;
  }
}

int main() {
  // precision_experiment<long double>("longdouble");
  // precision_experiment<double>("double");
  // precision_experiment<float>("float");
  using pos = cnl::fixed_point<cnl::elastic_integer<>, -15>;
  using vel = cnl::fixed_point<cnl::elastic_integer<>, -19>;
  precision_experiment<pos, vel, cnl::fixed_point<std::uint32_t, -12>>("cnl");
}
