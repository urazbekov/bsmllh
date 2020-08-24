#include <complex>
#ifndef uba_functions_h
#define uba_functions_h

struct coordinateOfJacobi
{
   double r;
   double theta;
   double phi;
};

std::complex<double> sphericalHarmonicY(int l, int m, coordinateOfJacobi x);
std::complex<double> hyperSphericalHarmonicY(int l1, int l2, int l, coordinateOfJacobi x, coordinateOfJacobi y);
double clebschGordonCoeff(double j1, double m1, double j2, double m2, double j, double m);

#endif
