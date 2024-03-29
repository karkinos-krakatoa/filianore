#ifndef _SHAPE_CREATOR_H
#define _SHAPE_CREATOR_H

#include "../core/elemental.h"
#include <vector>

namespace filianore {

class ShapeCreator {
public:
    ShapeCreator() {}

    std::vector<std::shared_ptr<Shape>> create_quad(const Transform &_transform);
};

} // namespace filianore

#endif
