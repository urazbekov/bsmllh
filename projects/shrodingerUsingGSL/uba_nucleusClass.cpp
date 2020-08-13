#include "uba_constants.h"
#include "uba_nucleusClass.h"
#include <iostream>


Nucleus::Nucleus(double tZ, double tA)
{
    P = 1;
    J = 0;
    Z = tZ;
    A = tA;
    int  i;
    bool test = false;
    for (i = 0; i < 5000; i++)
    {
        test = chargeNumber[i] == Z && atomicNumber[i] == A;
        if (test)
            break;
    }
    if (!test) {
      printf("Nucleus not found\n" );
      exit(1);
    }
    BE = bindingEnergy[i];
    AM = atomicMass[i];
    ID = i;
}
