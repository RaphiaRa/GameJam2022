#ifndef ENGINE_TILE_SET_H
#define ENGINE_TILE_SET_H
#include "TextureArea.h"

#include <vector>

namespace engine
{
class TileSet {
  public:
    virtual ~TileSet() = default;
    TileSet(Texture* texture, int width, int height);
    TextureArea& at(int x, int y);

  private:
    int width_;
    int height_;
    std::vector<engine::TextureArea> areas_;
};
} // namespace engine
#endif
