#ifndef ENGINE_SCENE_OBJECT_H
#define ENGINE_SCENE_OBJECT_H
#include "Math.h"
namespace engine
{
class SceneNode;
class SceneObject {

    virtual void update(const math::Vector<double, 3>& pos, const math::Vector<double, 2>& scale, double rot, bool isFlipped, bool isVisible) = 0;
    virtual bool isRenderable() { return false; }
    virtual bool isSolid() { return false; }

  public:
    virtual ~SceneObject() = default;
    friend class SceneNode;
};
} // namespace engine

#endif
