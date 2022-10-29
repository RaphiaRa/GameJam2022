#include "SdlTexture.h"

#include <Renderer.h>

namespace engine
{
class Renderer::Impl {
  public:
    void render(SdlTexture& tex, const Texture::Area& src, const Texture::Area& dest, double rot, bool isFlipped);
};
} // namespace engine
