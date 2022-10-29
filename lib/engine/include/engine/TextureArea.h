#ifndef ENGINE_TEXTURE_AREA_HPP
#define ENGINE_TEXTURE_AREA_HPP
#include "Renderer.h"
#include "Texture.h"

namespace engine
{
class TextureArea : public Texture {
  public:
    virtual ~TextureArea() = default;
    TextureArea()          = default;
    TextureArea(const Texture* texture, Area area);
    void copyTo(Renderer& renderer, const Area& dest, double rot, bool isFlipped) const;
    int width() const noexcept override;
    int height() const noexcept override;
    operator bool() const { return texture_ != NULL; }

  private:
    const Texture* texture_ = nullptr;
    Area area_              = engine::nullArea;
};
} // namespace engine
#endif
