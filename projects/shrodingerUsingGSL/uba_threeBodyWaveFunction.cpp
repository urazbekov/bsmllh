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
   double              a, b, c;
   int                 int1, int2, int3;
   bool                newQuantumNumbersQ = false;
   std::vector<int>    tempGamma;
   std::vector<double> tempA;
   std::vector<double> tempB;
   std::vector<double> tempC;

   while (fgets(mys, 100, pFile))
   {
      if (mys[1] != '.')
      {
         sscanf(mys, "%d\t%d\t%d", &int1, &int2, &int3);
         tempGamma.push_back(int1);
         tempGamma.push_back(int2);
         tempGamma.push_back(int3);
         gamma.push_back(tempGamma);
         tempGamma.clear();
         if (gamma.size() != 1)
         {
            newQuantumNumbersQ = true;
         }
      }
      else
      {
         sscanf(mys, "%lf\t%lf\t%lf", &a, &b, &c);
         tempA.push_back(a);
         tempB.push_back(b);
         tempC.push_back(c);
         if (newQuantumNumbersQ)
         {
            a1.push_back(tempA);
            b1.push_back(tempB);
            C.push_back(tempC);
            tempA.clear();
            tempB.clear();
            tempC.clear();
            newQuantumNumbersQ = false;
         }

//     printf("%f\t%f\t%f\n", double1, double2, double3);
      }
   }
   fclose(pFile);

   a1.push_back(tempA);
   b1.push_back(tempB);
   C.push_back(tempC);
   tempA.clear();
   tempB.clear();
   tempC.clear();

   a1[0].erase(a1[0].begin());
   b1[0].erase(b1[0].begin());
   C[0].erase(C[0].begin());

   for (size_t i = 0; i < a1[0].size(); i++)
   {
      std::cout << a1[0][i] << '\n';
   }
}
