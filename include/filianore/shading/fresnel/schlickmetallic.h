#ifndef _SCHLICK_METALLIC_H
#define _SCHLICK_METALLIC_H

#include "../../core/fresnel.h"

namespace filianore
{

    class SchlickMetallic : public Fresnel
    {
    public:
        SchlickMetallic(const PrincipalSpectrum &_ro)
            : ro(_ro)
        {
        }

        PrincipalSpectrum Evaluate(float cosThetaI) const;

    private:
        const PrincipalSpectrum ro;
    };

} // namespace filianore

#endif