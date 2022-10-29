#include "Assets.h"

std::unique_ptr<Assets> Assets::instance_;

Assets::Assets(engine::Renderer& renderer, std::filesystem::path path)
{
    textures_.emplace("floor1", renderer.createTexture(path / "graphics/floor1.png"));
    textures_.emplace("char1", renderer.createTexture(path / "graphics/char1.png"));
}

engine::Texture* Assets::getTexture(std::string_view id)
{
    return textures_.at(std::string(id)).get();
}
