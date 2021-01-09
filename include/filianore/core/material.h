#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "elemental.h"
#include "../maths/static_array.h"

namespace filianore
{

    class Material
    {
    public:
        virtual ~Material() {}

        virtual void ComputeScatteringFunctions(SurfaceInteraction *isect) const = 0;
    };

} // namespace filianore

#endif