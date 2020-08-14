#include "uba_nucleusClass.h"
#ifndef uba_channelsClass_h
#define uba_channelsClass_h

class Channel
{
public:
   Channel(Nucleus& projectile, Nucleus& target, double eLab);
   double eIcm;         // energy in center mass
   double mu;           // reduced mass
   double muMdf;        // 2*mu/hsq
   double k;            // wave number
   double kSquare;
   double eta;
};

#endif
