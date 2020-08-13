#ifndef uba_potentialClass_h
#define uba_potentialClass_h
#include <complex>
#include <gsl/gsl_complex.h>

class Potential
{
  public:
    Potential(Channel &iChannel);
    void                 setNewPotential(double iType, double iShape, double iP1, double iP2 = 1e-6,
                                         double iP3 = 1e-6, double iP4 = 1e-6, double iP5 = 1e-6,
                                         double iP6 = 1e-6);
    std::complex<double> getPotential(double R);
    std::complex<double> potential;
    double               pArray[10][8];
    double               kernelFunction(double R);
    int                  counter;
    int                  n;
    void                 coulomb(double R, std::complex<double> &complexArg);
    void                 centrifugal(double R, std::complex<double> &complexArg);
    void                 woodsSaxon(double R, std::complex<double> &complexArg);

  private:
};

#endif
