#include <math.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include "uba_threeBodyWaveFunction.h"
using namespace std;

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
