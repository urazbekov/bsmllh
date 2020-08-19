#include "uba_functions.h"
#include <iostream>
#include <math.h>
#include <complex>
#include <cmath>
#include "gsl/gsl_sf_legendre.h"
#include "gsl/gsl_sf_coupling.h"
#include <iomanip>
using namespace std;
using namespace std::complex_literals;


std::complex<double> sphericalHarmonicY(int l, int m, double theta, double phi)
{
   double          normalizedLegandreP;
   complex<double> phidependentPart;
   double          phase = 1;

   if (m < 0)
   {
      phase = pow(-1, m);
      phi   = -phi;
      m     = abs(m);
   }
   normalizedLegandreP = gsl_sf_legendre_sphPlm(l, m, cos(theta));
   phidependentPart    = exp(1i * double(m) * phi);

   return phase * normalizedLegandreP * phidependentPart;
}


double clebschGordonCoeff(double j1, double m1, double j2, double m2, double j, double m)
{
   double aCoefficient;

   aCoefficient = gsl_sf_coupling_3j(2 * j1, 2 * j2, 2 * j, 2 * m1, 2 * m2, 2 * m);
   printf("%lf\n", aCoefficient);
   aCoefficient *= sqrt(2 * j + 1);
   aCoefficient *= pow(-1, m + j1 - j2);
   return aCoefficient;
}
