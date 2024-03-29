#ifndef _TEXTURE_CONSTANT_H
#define _TEXTURE_CONSTANT_H

#include "texture.h"

namespace filianore {

template <typename T>
class ConstantTexture : public Texture<T> {
public:
    ConstantTexture(const T &_value)
        : value(_value) {
    }

    T evaluate(const SurfaceInteraction &isect) const {
        return value;
    }

private:
    T value;
};

} // namespace filianore

#endif