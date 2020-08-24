#include <string>
#include <fstream>
#include <vector>
#include "uba_functions.h"
#ifndef uba_threeBodyWaveFunction_h
#define uba_threeBodyWaveFunction_h
class ThreeBodyWaveFunction {
public:
   ThreeBodyWaveFunction(const char *filename);
   std::vector<std::vector<double> > a1;
   std::vector<std::vector<double> > b1;
   std::vector<std::vector<double> > C;
   std::vector<std::vector<int> > gamma;
   double xr;
   double yr;
   int k;
   std::complex<double> Psi(int k, int i, coordinateOfJacobi x, coordinateOfJacobi y);
   double radialPartOfTheWaveFunction(int k, int i, double x, double y);
   double W1();
};

double g(double *k, size_t dim, void *params);


#endif
