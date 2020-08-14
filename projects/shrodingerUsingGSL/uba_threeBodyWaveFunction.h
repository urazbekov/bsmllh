#include <string>
#include <fstream>
#ifndef uba_threeBodyWaveFunction_h
#define uba_threeBodyWaveFunction_h
using namespace std;
class ThreeBodyWaveFunction {
public:
   ThreeBodyWaveFunction(string filename);
   double data;
   int n;
};


#endif
