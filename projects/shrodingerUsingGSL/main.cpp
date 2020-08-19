#include "uba_channelsClass.h"
#include "uba_constants.h"
#include "uba_nucleusClass.h"
#include "uba_ode.h"
#include "uba_potentialClass.h"
#include "uba_functions.h"
#include "uba_threeBodyWaveFunction.h"
#include <string.h>
#include <stdio.h>
#include <complex>
#include <iostream>

int main(void)
{
   double aVariable;

   aVariable = clebschGordonCoeff(2, 1, 1, 0, 3, 1);
   std::cout << aVariable << '\n';
   return 0;

   const char            *filename = "9be.txt";
   ThreeBodyWaveFunction be9(filename);

   Nucleus   projectile(2, 4);
   Nucleus   target(4, 9);
   Channel   firstChannel(projectile, target, 23.0);
   Potential potFirstChannel(firstChannel);

   potFirstChannel.setNewPotential(0, 0, 1.8);
   potFirstChannel.setNewPotential(1, 0, 34.0, 1.5, 0.6, 34.0, 1.5, 0.6);
   std::cout << potFirstChannel.getPotential(1.3) << '\n';
}


/*
 * void interactionPotential(double R, gsl_complex z)
 * {
 *  // gsl_complex potentail;
 *  // gsl_complex waveFunction;
 *  // gsl_complex dWaveFunction; //derivative of wave function;
 *  gsl_complex complexPotential;
 *  GSL_SET_REAL(&complexPotential, 1232);
 *  GSL_SET_IMAG(&complexPotential, 23);
 *  double(*myComplex)[2];
 *  myComplex = &complexPotential.dat;
 *  std::cout << *myComplex[0] << '\n';
 *
 *  GSL_SET_REAL(&z, 40.0 / (1.0 + exp((R - 1.25) / 0.6)));
 *  GSL_SET_IMAG(&z, 20.0 / (1.0 + exp((R - 1.2) / 0.6)));
 * }
 */
