#ifndef ENGINE_SPRITE_H
#define ENGINE_SPRITE_H
#include "Renderable.h"
#include "TextureArea.h"
namespace engine
{
class Sprite : public Renderable {
  public:
    Sprite(const TextureArea* texArea);
    virtual ~Sprite() = default;
    void copyTo(Renderer& renderer) const override;

  private:
    void update(const math::Vector<double, 3>& pos, const math::Vector<double, 2>& scale, double rot, bool isFlipped, bool isVisible) override;

    const TextureArea* texArea_;
    math::Vector<double, 3> pos_;
    math::Vector<double, 2> scale_;
    double rot_;
    bool isFlipped_;
    bool isVisible_;
};
} // namespace engine

#endif
