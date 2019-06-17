#include <cstring>

int euler_step(double *w, double Fprime(size_t i), double timestep, size_t i){
	double fprime = Fprime(i);
	w[i+1] = w[i] + fprime*timestep;
	return 0;
}
