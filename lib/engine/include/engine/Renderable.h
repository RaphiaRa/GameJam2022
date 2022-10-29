#ifndef ENGINE_RENDERABLE_HPP
#define ENGINE_RENDERABLE_HPP
#include "Renderer.h"
#include "SceneObject.h"
namespace engine
{
class Renderable : public SceneObject {
  public:
    virtual ~Renderable() override                = default;
    virtual void copyTo(Renderer& renderer) const = 0;
    bool isRenderable() override { return true; }
};
} // namespace engine
#endif
