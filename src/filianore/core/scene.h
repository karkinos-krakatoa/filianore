#ifndef _SCENE_H
#define _SCENE_H

#include "../bvh/bvh.h"
#include "../illuminants/illuminant.h"
#include "../maths/geometry.h"
#include "primitive.h"
#include <vector>

namespace filianore {

class Scene {
public:
    Scene(const SceneGeometry &SceneGeometry, const std::vector<std::shared_ptr<Illuminant>> &_illuminants);

    ~Scene();

    const AABB &world_bound() const {
        return worldBound;
    }

    bool intersect(const Ray &ray, SurfaceInteraction *isect) const;

    bool intersect_p(const Ray &ray) const;

    std::vector<std::shared_ptr<Illuminant>> illuminants;

private:
    BVH bvh;
    AABB worldBound;
};

} // namespace filianore

#endif