#include <math.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include "uba_threeBodyWaveFunction.h"
#include "uba_functions.h"
#include <gsl/gsl_monte_miser.h>
#include <gsl/gsl_monte.h>
#include <gsl/gsl_math.h>
#include <stdlib.h>

ThreeBodyWaveFunction::ThreeBodyWaveFunction(const char *filename)
{
   FILE *pFile;

   pFile = fopen(filename, "r");
   char                mys[100];
   double              double1, double2, double3;
   int                 int1, int2, int3;
   bool                newQuantumNumbersQ = false;
   std::vector<int>    tempInt;
   std::vector<double> tempDouble1;
   std::vector<double> tempDouble2;
   std::vector<double> tempDouble3;

   while (fgets(mys, 100, pFile))
   {
      if (mys[1] != '.')
      {
         sscanf(mys, "%d\t%d\t%d", &int1, &int2, &int3);
         tempInt.push_back(int1);
         tempInt.push_back(int2);
         tempInt.push_back(int3);
         gamma.push_back(tempInt);
         tempInt.clear();
         newQuantumNumbersQ = true;
      }
      else
      {
         sscanf(mys, "%lf\t%lf\t%lf", &double1, &double2, &double3);
         tempDouble1.push_back(double1);
         tempDouble2.push_back(double2);
         tempDouble3.push_back(double3);
      }

      if (newQuantumNumbersQ && (gamma.size() != 1))
      {
         a1.push_back(tempDouble1);
         b1.push_back(tempDouble2);
         C.push_back(tempDouble3);
         tempDouble1.clear();
         tempDouble2.clear();
         tempDouble3.clear();
         newQuantumNumbersQ = false;
      }
   }

   a1.push_back(tempDouble1);
   b1.push_back(tempDouble2);
   C.push_back(tempDouble3);
   tempDouble1.clear();
   tempDouble2.clear();
   tempDouble3.clear();
   fclose(pFile);
}


double ThreeBodyWaveFunction::radialPartOfTheWaveFunction(int k, int i, double x, double y)
{
   double aVariable;

   aVariable = C[k][i] * pow(x, gamma[k][0]) * pow(x, gamma[k][1])
               * exp(-0.5 * a1[k][i] * x * x - 0.5 * b1[k][i] * y * y);
   return aVariable;
}


std::complex<double> ThreeBodyWaveFunction::Psi(int k, int i, coordinateOfJacobi x, coordinateOfJacobi y)
{
   std::complex<double> aVariable;

   aVariable  = hyperSphericalHarmonicY(gamma[k][0], gamma[k][1], gamma[k][2], x, y);
   aVariable *= radialPartOfTheWaveFunction(k, i, x.r, y.r);
   return aVariable;
}


double g(double *iVariable, size_t dim, void *params)
{
   ThreeBodyWaveFunction             waveFunction = *(ThreeBodyWaveFunction *)params;
   std::complex<double>              sum = 0;
   coordinateOfJacobi                x, y;
   std::vector<std::vector<double> > a1 = waveFunction.a1;
   std::vector<std::vector<double> > b1 = waveFunction.b1;
   std::vector<std::vector<double> > C  = waveFunction.C;

   x.r     = waveFunction.xr;
   y.r     = waveFunction.yr;
   x.theta = iVariable[0];
   y.theta = iVariable[1];
   x.phi   = iVariable[2];
   y.phi   = iVariable[3];

   for (size_t i = 0; i < 1; i++)
   {
      for (size_t j = 0; j < 1; j++)
      {
         sum += C[waveFunction.k][i] * C[waveFunction.k][j]
                * waveFunction.Psi(waveFunction.k, i, x, y) * std::conj(waveFunction.Psi(waveFunction.k, j, x, y));
      }
   }
   (void)(dim); /* avoid unused parameter warnings */
   return sum.real();
}


double ThreeBodyWaveFunction::W1()
{
   size_t             dimention = 4;
   double             res, err;
   double             xl[4] = { 0, 0, 0, 0 };
   double             xu[4] = { M_PI, M_PI, 2 * M_PI, 2 * M_PI };
   const gsl_rng_type *theRandomNumberGeneratorType;
   gsl_rng            *theRandomNumberGenerator;
   gsl_monte_function G     = { &g, dimention, this };
   size_t             calls = 100000;

   gsl_rng_env_setup();
   theRandomNumberGeneratorType = gsl_rng_default;
   theRandomNumberGenerator     = gsl_rng_alloc(theRandomNumberGeneratorType);
   gsl_monte_miser_state *allocatedWorkspace = gsl_monte_miser_alloc(dimention);

   gsl_monte_miser_integrate(&G, xl, xu, dimention, calls,
                             theRandomNumberGenerator, allocatedWorkspace,
                             &res, &err);
   gsl_monte_miser_free(allocatedWorkspace);

   printf("MISER: %lf\t%lf\n", res, err);
   return res;
}
