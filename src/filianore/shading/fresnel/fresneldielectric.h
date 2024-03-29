#ifndef _FRESNEL_DIELECTRIC_H
#define _FRESNEL_DIELECTRIC_H

#include "fresnel.h"

namespace filianore {

class FresnelDielectric : public Fresnel {
public:
    FresnelDielectric(float _etaI, float _etaT)
        : etaI(_etaI), etaT(_etaT) {
    }

    PrincipalSpectrum evaluate(float cosThetaI) const;

private:
    mutable float etaI, etaT;
};

} // namespace filianore

#endif