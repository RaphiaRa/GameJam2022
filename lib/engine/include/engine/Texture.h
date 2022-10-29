#ifndef ENGINE_TEXTURE_HPP
#define ENGINE_TEXTURE_HPP
namespace engine
{
class Texture {
  public:
    virtual ~Texture()                  = default;
    virtual int width() const noexcept  = 0;
    virtual int height() const noexcept = 0;
};
} // namespace engine
#endif
