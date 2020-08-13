#include "uba_channelsClass.h"
#include "uba_constants.h"
#include "uba_nucleusClass.h"
#include<math.h>

Channel::Channel(Nucleus &projectile, Nucleus &target, double eLab)
{
    eIcm    = eLab * target.AM / (projectile.AM + target.AM);
    mu      = target.AM * projectile.AM / (projectile.AM + target.AM);
    muMdf   = 2.0 * mu / hSquare;
    k       = sqrt(abs(2 * mu * eIcm / hSquare));
    kSquare = 2 * mu * eIcm / hSquare;
    eta     = eSquare * mu* projectile.Z * target.Z / k / hSquare;
}
