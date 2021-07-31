#include "filianore/materials/matte.h"
#include "filianore/shading/bxdfs/orennayar.h"
#include "filianore/shading/bxdfs/lambert.h"
#include "filianore/core/interaction.h"
#include "filianore/core/bsdf.h"
#include "filianore/core/texture.h"

namespace filianore
{

    void MatteMaterial::ComputeScatteringFunctions(SurfaceInteraction *isect) const
    {
        isect->bsdf = std::make_shared<BSDF>(*isect);

        PrincipalSpectrum r = kd->Evaluate(*isect).SpectrumClamp();
        float rough = roughness->Evaluate(*isect);

        if (rough == 0)
        {
            std::unique_ptr<BxDF> lambBRDF = std::make_unique<LambertBRDF>(r, weight);
            isect->bsdf->Add(lambBRDF);
        }
        else
        {
            // Remap [0-1] roughness to [0-90] sigma
            float sigma = rough * 90.f;
            std::unique_ptr<BxDF> orenBrdf = std::make_unique<OrenNayarBRDF>(r, weight, sigma);
            isect->bsdf->Add(orenBrdf);
        }
    }

} // namespace filianore
