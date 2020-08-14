#include <string>
#include <fstream>
#include <vector>
#ifndef uba_threeBodyWaveFunction_h
#define uba_threeBodyWaveFunction_h
class ThreeBodyWaveFunction {
public:
   ThreeBodyWaveFunction(const char *filename);
   std::vector<std::vector<double> > a1;
   std::vector<std::vector<double> > b1;
   std::vector<std::vector<double> > C;
   std::vector<std::vector<int> > gamma;
};


#endif
