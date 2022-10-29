#ifndef ASSETS_H
#define ASSETS_H

#include <engine/Sprite.h>
#include <engine/Texture.h>
#include <engine/TileSet.h>
#include <filesystem>
#include <map>
#include <mutex>
#include <string_view>

class Assets {
  public:
    static void init(engine::Renderer& renderer, std::filesystem::path path)
    {
        instance_ = std::unique_ptr<Assets>(new Assets(renderer, path));
    }
    static Assets& get()
    {
        return *instance_;
    }

    engine::Texture* getTexture(std::string_view id);

  private:
    Assets(engine::Renderer& renderer, std::filesystem::path path);

    static std::unique_ptr<Assets> instance_;
    std::map<std::string, std::unique_ptr<engine::Texture>> textures_;
};

#endif
