#include <iostream>
#include <fstream>
#include <cmath>
#include <numeric>

using namespace std;
const double B = 4.0;
const double g = 9.81;

template <typename real_t> struct cannon {
	real_t x,y,v_x, v_y, m;
	void euler_step(real_t dt) {
		x+=v_x*dt;
		y+=v_y*dt;
		//drag is missing a factor of velocity
		const real_t drag = -B*hypot(v_x,v_y)/m;
		v_x+=drag*v_x*dt;
		v_y+=(-g + drag*v_y)*dt;
	}
};

template <typename precision>
void precision_experiment(string outfile) {
	using real_t = precision;
	real_t theta, m;
	const real_t dt = .01;
	const real_t v0 = 700;

	ifstream config("config.cfg");
	config>>theta;
	config>>m;
	config.close();
	cannon<real_t> ball = {0,0,v0*cos(theta),v0*sin(theta),m};
	cout<<"v_x:"<<ball.v_x<<endl;
	cout<<"v_y:"<<ball.v_y<<endl;
	cout<<"x:"<<ball.x<<endl;
	cout<<"y:"<<ball.y<<endl;
	ofstream results("output/"+outfile+".csv");
	results << "x, y, v_x, v_y"<<endl;

	while (ball.y >= 0) {
			ball.euler_step(dt);
			results <<ball.x<<", "<<ball.y<<", "<<ball.v_x<<", "<<ball.v_y<<endl;
	}
}


int main() {
	precision_experiment<long double>("longdouble");
	precision_experiment<double>("double");
	precision_experiment<float>("float");
}

