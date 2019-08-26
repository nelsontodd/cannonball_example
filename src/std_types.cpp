#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <numeric>
#include <string>

using namespace std;

template <typename real_t> struct cannon {
  real_t x, y, v_x, v_y, m;
  constexpr static real_t B = 4.0;
  constexpr static real_t g = -9.81;
  void euler_step(real_t dt) {
    x += v_x * dt;
    y += v_y * dt;
    // drag is missing a factor of velocity
    const real_t drag = -B * hypot(v_x, v_y) / m;
    v_x += drag * v_x * dt;
    v_y += (g + drag * v_y) * dt;
  }
};

template <typename precision>
void precision_poweriment(string outfile, precision dt) {
  using real_t = precision;
  real_t theta = 0.7853, m = 100000;
  const real_t v0 = 700;

  cannon<real_t> ball = {0, 0, v0 * cos(theta), v0 * sin(theta), m};
  ofstream results("output/" + outfile + ".csv");
  results << "x, y, v_x, v_y" << endl;

  uint64_t i = 0;
  while (ball.y >= 0) {
    ball.euler_step(dt);
    if ((i > (int)(1. / dt) and i % (int)(1. / dt) == 0) or ball.y <= 0) {
      results << setprecision(numeric_limits<real_t>::max_digits10) << ball.x
              << ", " << ball.y << ", " << ball.v_x << ", " << ball.v_y << endl;
    }
    i++;
  }
}

int main() {
  for (int i = 0; i < 6; i++) {
    precision_poweriment<long double>("longdouble_" + to_string(i),
                                      pow(10, i) / pow(10, 5));
    precision_poweriment<double>("double_" + to_string(i),
                                 pow(10, i) / pow(10, 5));
    precision_poweriment<float>("float_" + to_string(i),
                                pow(10, i) / pow(10, 5));
  }
}
