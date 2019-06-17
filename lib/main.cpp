#include <iostream>
#include <fstream>
#include <cmath>
#include <numeric>
#include "euler.h"

using namespace std;
#define TIME_STEPS 10000
#define TIME 100
#define B 4.0
double y[TIME_STEPS], x[TIME_STEPS], v_y[TIME_STEPS], v_x[TIME_STEPS], v0 = 700.,dt = (double)TIME/(double)TIME_STEPS, theta=0;
double m=0;


void results() {
	ofstream results;
  results.open ("output/results.csv");
	results << "x, y, v_x, v_y"<<endl;
	for (size_t i = 0; i < TIME_STEPS; i++) {
		results << x[i]<<", "<<y[i]<<", "<<v_x[i]<<", "<<v_y[i]<<endl;
	}
  results.close();
}

void initialize() {
	cout<<"Theta: "<<endl;
	cin>>theta;
	cout<<"Mass: "<<endl;
	cin>>m;
	::v_x[0] = ::v0*cos(theta);
	::v_y[0] = ::v0*sin(theta);
	::x[0] = 0;
  ::y[0] = 0;
	cout<<"v_x:"<<::v_x[0]<<endl;
	cout<<"v_y:"<<::v_y[0]<<endl;
	cout<<"x:"<<::x[0]<<endl;
	cout<<"y:"<<::y[0]<<endl;
}

double drag(size_t i) {
	return -1*(B*sqrt(pow(v_y[i],2)+pow(v_x[i],2))/::m);
}

double xprime(size_t i) {
	return ::v_x[i];
}

double yprime(size_t i) {
	return ::v_y[i];
}

double v_xprime(size_t i) {
	return drag(i)*v_x[i];
}

double v_yprime(size_t i) {
	return (-9.81 + drag(i)*v_y[i]); 
}


int main() {
	initialize();
	int err[4];
	size_t i = 0;
	while (y[i] >= 0 and i < TIME_STEPS){
			err[0] = euler_step(x, xprime, dt, i);
			err[1] = euler_step(v_x, v_xprime, dt, i);
			err[2] = euler_step(y, yprime, dt, i);
			err[3] = euler_step(v_y, v_yprime, dt, i);
			if (accumulate(begin(err), end(err), 0, plus<int>()) != 0) {
				cout << "euler_step failed at "<<i<<"."<<endl;
				break;
			}
			i +=1;
	}
	while (i < TIME_STEPS) {
		x[i] = x[i-1];
		y[i] = 0;
		v_x[i] = 0;
		v_y[i] = 0;
		i +=1;
	}
	results();
}

