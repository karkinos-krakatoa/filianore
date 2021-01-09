#ifndef _INTEGRATOR_H
#define _INTEGRATOR_H

#include <vector>
#include "elemental.h"
#include "illuminant.h"

namespace filianore
{

    class Integrator
    {
    public:
        virtual ~Integrator() {}

        virtual void PrepareTheRenderer(const Scene &scene, Sampler &sampler) = 0;
        virtual Color Li(const Ray &_ray, const Scene &scene, Sampler &sampler, int depth) const = 0;
    };

    Color UniformSampleAllLights(const Interaction &it, const Scene &scene, Sampler &sampler, bool handleMedia = false);

    Color EstimateDirect(const Interaction &it, const StaticArray<float, 2> &uShading, const Illuminant &illuminant, const StaticArray<float, 2> &uLight,
                         const Scene &scene, Sampler &sampler, bool handleMedia = false, bool specular = false);

} // namespace filianore

#endif