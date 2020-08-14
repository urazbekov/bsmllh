#include <math.h>
#include <string>
#include <fstream>
#include <iostream>
#include "uba_threeBodyWaveFunction.h"
using namespace std;

ThreeBodyWaveFunction::ThreeBodyWaveFunction(string filename)
{
   ifstream file(filename.c_str());   //opens file

   if (!file)
   {
      cout << "Cannot open file\n";
      return;
   }
   cout << "File is opened\n";
   file.close();   //closes file
}
