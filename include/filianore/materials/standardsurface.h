#ifndef _STANDARD_SURFACE_MATERIAL_H
#define _STANDARD_SURFACE_MATERIAL_H

#include "../core/elemental.h"
#include "../core/material.h"

namespace filianore
{

    class StandardSurfaceMaterial : public Material
    {
    public:
        StandardSurfaceMaterial(const float _kdweight,
                                const std::shared_ptr<Texture<PrincipalSpectrum>> &_kd,
                                const std::shared_ptr<Texture<float>> &_kdroughness,

                                const float _metallicWeight,

                                const float _ksweight,
                                const std::shared_ptr<Texture<PrincipalSpectrum>> &_ks,
                                const std::shared_ptr<Texture<float>> &_ksroughness,
                                const std::shared_ptr<Texture<float>> &_ksanisotropic,
                                const float _ksIOR,

                                const float _sheenweight,
                                const std::shared_ptr<Texture<PrincipalSpectrum>> &_sheenColor,
                                const std::shared_ptr<Texture<float>> &_sheenroughness,

                                const float _ktweight,
                                const std::shared_ptr<Texture<PrincipalSpectrum>> &_kt,

                                const float _krcoatweight,
                                const std::shared_ptr<Texture<PrincipalSpectrum>> &_krcoat,
                                const float _krcoatior,
                                const float _krcoatgloss)
            : kd(_kd), kdroughness(_kdroughness), kdweight(_kdweight),
              metallicWeight(_metallicWeight),
              ks(_ks), ksroughness(_ksroughness), ksweight(_ksweight), ksanisotropic(_ksanisotropic), ksIOR(_ksIOR),
              sheenweight(_sheenweight), sheenColor(_sheenColor), sheenroughness(_sheenroughness),
              kt(_kt), ktweight(_ktweight),
              krcoatweight(_krcoatweight), krcoat(_krcoat), krcoatior(_krcoatior), krcoatgloss(_krcoatgloss)
        {
        }

        void ComputeScatteringFunctions(SurfaceInteraction *isect) const;

    private:
        // Diffuse Foundation
        const std::shared_ptr<Texture<PrincipalSpectrum>> kd;
        const std::shared_ptr<Texture<float>> kdroughness;
        const float kdweight;

        // Metallic
        const float metallicWeight;

        // Specular
        const std::shared_ptr<Texture<PrincipalSpectrum>> ks;
        const std::shared_ptr<Texture<float>> ksroughness;
        const std::shared_ptr<Texture<float>> ksanisotropic;
        const float ksweight;
        const float ksIOR;

        // Sheen
        const std::shared_ptr<Texture<PrincipalSpectrum>> sheenColor;
        const std::shared_ptr<Texture<float>> sheenroughness;
        const float sheenweight;

        // Transmission
        const std::shared_ptr<Texture<PrincipalSpectrum>> kt;
        const float ktweight;

        // Clearcoat
        const float krcoatweight;
        const std::shared_ptr<Texture<PrincipalSpectrum>> krcoat;
        const float krcoatior;
        const float krcoatgloss;
    };

} // namespace filianore

#endif