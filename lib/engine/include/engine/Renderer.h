#ifndef ENGINE_RENDERER_HPP
#define ENGINE_RENDERER_HPP
#include "Texture.h"

#include <filesystem>
#include <string_view>

namespace engine
{
struct NullArea {
    explicit constexpr NullArea() {}
};
inline constexpr NullArea nullArea;

struct Area {
    Area(int xpos, int ypos, int w, int h) : x(xpos), y(ypos), width(w), height(h) {}
    Area(NullArea) : x(0), y(0), width(0), height(0) {}
    Area() : x(0), y(0), width(0), height(0) {}
    
    int x;
    int y;
    int width;
    int height;
};
inline bool operator==(const Area& a, const Area& b) { return a.x == b.x && a.y == b.y && a.width == b.width && a.height == b.height; };
inline bool operator!=(const Area& a, const Area& b) { return !(a == b); };
inline bool operator==(const Area& a, const NullArea& b) { (void)b; return a == Area{ 0, 0, 0, 0 }; };
inline bool operator!=(const Area& a, const NullArea& b) { return !(a == b); };

class Renderer {
  public:
    enum class Backend {
        sdl,
        opengl,
    };
    virtual ~Renderer() = default;
    static std::unique_ptr<Renderer> create(Backend backend, const Area& winArea, std::string_view title, unsigned int flags = 0);
    virtual void render(const Texture& tex, const Area& src, const Area& dest, double rot, bool isFlipped) = 0;
    virtual std::unique_ptr<engine::Texture> createTexture(std::filesystem::path file)                     = 0;
    virtual void clear()                                                                                   = 0;
    virtual void update()                                                                                  = 0;
};

} // namespace engine

#endif
