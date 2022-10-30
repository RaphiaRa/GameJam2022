#include "SdlRenderer.h"

#include "SdlError.h"

#include <SDL_image.h>

using engine::Area;

class SdlTexture : public engine::Texture {
  public:
    SdlTexture(SDL_Texture* texture);
    ~SdlTexture();
    int width() const noexcept override { return width_; }
    int height() const noexcept override { return height_; }

  private:
    friend class sdl::Renderer;
    SDL_Texture* texture_;
    int width_;
    int height_;
};

SdlTexture::SdlTexture(SDL_Texture* texture)
        : texture_(texture)
{
    if (SDL_QueryTexture(texture_, NULL, NULL, &this->width_, &this->height_) < 0)
        throw std::system_error(-1, sdl::errorCategory(), SDL_GetError());
}

SdlTexture::~SdlTexture()
{
    SDL_DestroyTexture(texture_);
}

sdl::Renderer::Renderer(const Area& winArea, std::string_view title, unsigned int flags)
{
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
        throw std::system_error(-1, sdl::errorCategory(), SDL_GetError());

    std::string titleString(title);
    SDL_Window* win = SDL_CreateWindow(titleString.c_str(), winArea.x, winArea.y, winArea.width, winArea.height, SDL_WINDOW_SHOWN | flags);
    if (win == NULL)
        throw std::system_error(-1, sdl::errorCategory(), SDL_GetError());
    window_ = win;

    SDL_Renderer* renderer = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        throw std::system_error(-1, sdl::errorCategory(), SDL_GetError());
    renderer_ = renderer;
}

sdl::Renderer::~Renderer()
{
    SDL_DestroyWindow(window_);
    SDL_DestroyRenderer(renderer_);
}

void sdl::Renderer::render(const engine::Texture& tex, const Area& src, const Area& dest, double rot, bool flip)
{
    SDL_Rect sdl_dest;
    sdl_dest.x = dest.x; // - dest.width/2;
    sdl_dest.y = dest.y; // - dest.height/2;
    sdl_dest.w = dest.width;
    sdl_dest.h = dest.height;

    /**
    if (sdl_dest.w == 0 && sdl_dest.h == 0) {
        sdl_dest.w = tex.width();
        sdl_dest.h = tex.height();
    }
    **/

    const SdlTexture& sdlTex = dynamic_cast<const SdlTexture&>(tex);
    if (src == engine::nullArea) {
        SDL_RenderCopyEx(renderer_, sdlTex.texture_, NULL, &sdl_dest, rot, NULL, (SDL_RendererFlip)flip);
    } else {
        SDL_Rect sdl_src;
        sdl_src.x = src.x;
        sdl_src.y = src.y;
        sdl_src.w = src.width;
        sdl_src.h = src.height;
        SDL_RenderCopyEx(renderer_, sdlTex.texture_, &sdl_src, &sdl_dest, rot, NULL, (SDL_RendererFlip)flip);
    }
}

std::unique_ptr<engine::Texture> sdl::Renderer::createTexture(std::filesystem::path file)
{
    SDL_Surface* surface = IMG_Load(file.c_str());
    if (surface == NULL)
        throw std::system_error(-1, sdl::errorCategory(), SDL_GetError());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
    if (texture == NULL)
        throw std::system_error(-1, sdl::errorCategory(), SDL_GetError());
    return std::make_unique<SdlTexture>(texture);
}

void sdl::Renderer::clear()
{
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer_);
}

void sdl::Renderer::update()
{
    SDL_RenderPresent(renderer_);
}
