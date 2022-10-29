#include <engine/TileSet.h>

using engine::TextureArea;
using engine::TileSet;

TileSet::TileSet(Texture* texture, int width, int height)
        : width_(width), height_(height)
{
    int cell_width  = texture->width() / width;
    int cell_height = texture->height() / height;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            areas_.emplace_back(texture, Area(x * cell_width, y * cell_height, cell_width, cell_height));
        }
    }
}

TextureArea& TileSet::at(int x, int y)
{
    return areas_.at((size_t)(width_ * y + x));
}
