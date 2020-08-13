#include "uba_channelsClass.h"
#include "uba_constants.h"
#include "uba_potentialClass.h"
#include <complex>
#include <gsl/gsl_complex.h>
#include <math.h>

Potential::Potential(Channel &iChannel)
{
    counter = 0;
}
void Potential::setNewPotential(double iType, double iShape, double iP1, double iP2, double iP3,
                                double iP4, double iP5, double iP6)
{
    pArray[counter][0] = iType;
    pArray[counter][1] = iShape;
    pArray[counter][2] = iP1;
    pArray[counter][3] = iP2;
    pArray[counter][4] = iP3;
    pArray[counter][5] = iP4;
    pArray[counter][6] = iP5;
    pArray[counter][7] = iP6;
    counter++;
}

void Potential::woodsSaxon(double R, std::complex<double> &complexArg)
{
    std::complex<double> tempComplex;
    tempComplex.real(-pArray[n][2] / (1 + exp((R - pArray[n][3]) / pArray[n][4])));
    tempComplex.imag(-pArray[n][5] / (1 + exp((R - pArray[n][6]) / pArray[n][7])));
    complexArg += tempComplex;
}

void Potential::coulomb(double R, std::complex<double> &complexArg)
{
    double doubleTemp;
    double Rc = pArray[n][2];
    if (R > Rc)
        doubleTemp = eSquare * 2. * 6. / R;
    else
        doubleTemp = eSquare * 2 * 6 * 0.5 / Rc * (3.0 - R * R / Rc / Rc);
    complexArg.real(doubleTemp + complexArg.real());
}

std::complex<double> Potential::getPotential(double R)
{
    std::complex<double> sumPotential(0.0, 0.0);
    for (n = 0; n < counter; n++)
    {
        if (pArray[n][0] == 0)
            coulomb(R, sumPotential);
        if (pArray[n][0] == 1)
            woodsSaxon(R, sumPotential);
    }
    return sumPotential;
}
