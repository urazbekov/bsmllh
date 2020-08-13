#ifndef uba_nucleusClass_h
#define uba_nucleusClass_h
class Nucleus
{
  public:
    Nucleus(double tZ, double tA);
    int    ID;
    double Z;  // Z number
    double A;  // Atomic Number
    double BE; // binding energy / A in MeV
    double AM; // atomic mass in au
    double P;  // parity
    double J;  // spin
};
#endif
