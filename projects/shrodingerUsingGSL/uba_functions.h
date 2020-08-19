#include <complex>
#ifndef uba_functions_h
#define uba_functions_h


std::complex<double> sphericalHarmonicY(int l, int m, double theta, double phi);
double clebschGordonCoeff(double j1, double m1, double j2, double m2, double j, double m);

#endif
