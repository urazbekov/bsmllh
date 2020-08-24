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

std::complex<double> sphericalHarmonicY(int l, int m, coordinateOfJacobi x)
{
   double          normalizedLegandreP;
   complex<double> phidependentPart;
   double          phase = 1;

   if (m < 0)
   {
      phase = pow(-1, m);
      x.phi = -x.phi;
      m     = abs(m);
   }
   normalizedLegandreP = gsl_sf_legendre_sphPlm(l, m, cos(x.theta));
   phidependentPart    = exp(1i * double(m) * x.phi);

   return phase * normalizedLegandreP * phidependentPart;
}


double clebschGordonCoeff(double j1, double m1,
                          double j2, double m2, double j, double m)
{
   double aCoefficient = 1;

   aCoefficient = gsl_sf_coupling_3j(2 * int(j1), 2 * int(j2), 2 * int(j),
                                     2 * int(m1), 2 * int(m2), -2 * int(m));
   aCoefficient *= sqrt(2 * j + 1);
   aCoefficient *= pow(-1, m + j1 - j2);
   return aCoefficient;
}


std::complex<double> hyperSphericalHarmonicY(int l1, int l2, int l,
                                             coordinateOfJacobi x, coordinateOfJacobi y)
{
   std::complex<double> sum = 0;

   for (int m1 = -l1; m1 <= l1; m1++)
   {
      for (int m2 = -l2; m2 <= l2; m2++)
      {
         sum += clebschGordonCoeff(l1, m1, l2, m2, l, l)
                * sphericalHarmonicY(l1, m1, x) * sphericalHarmonicY(l2, m2, y);
      }
   }
   return sum;
}
