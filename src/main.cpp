#include <iostream>
#include <fstream>
#include <cmath>
#include <numeric>

using namespace std;
using real_t = double;
const real_t B = 4.0;
const real_t g = 9.81;

struct cannon {
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

int main() {
	real_t theta, m;
	const real_t dt = .01;
	const real_t v0 = 700;

	cout<<"Theta: "<<endl;
	cin>>theta;
	cout<<"Mass: "<<endl;
	cin>>m;
	cannon ball = {0,0,v0*cos(theta),v0*sin(theta),m};
	cout<<"v_x:"<<ball.v_x<<endl;
	cout<<"v_y:"<<ball.v_y<<endl;
	cout<<"x:"<<ball.x<<endl;
	cout<<"y:"<<ball.y<<endl;
	ofstream results("output/results.csv");
	results << "x, y, v_x, v_y"<<endl;

	while (ball.y >= 0) {
			ball.euler_step(dt);
			results <<ball.x<<", "<<ball.y<<", "<<ball.v_x<<", "<<ball.v_y<<endl;
	}
}
