#include <SDL.h>
#include <engine/Renderer.h>
#include <vector>

namespace sdl
{
class Renderer : public engine::Renderer {
  public:
    Renderer(const engine::Area& winArea, std::string_view title, unsigned int flags = 0);
    ~Renderer() override;
    void render(const engine::Texture& tex, const engine::Area& src, const engine::Area& dest, double rot, bool flip) override;
    std::unique_ptr<engine::Texture> createTexture(std::filesystem::path file) override;
    void clear() override;
    void update() override;

  private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;

    std::vector<SDL_Texture*> textures_;
};
} // namespace sdl
