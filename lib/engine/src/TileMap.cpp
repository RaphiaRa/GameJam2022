#include <cmath>
#include <engine/TileMap.h>

using engine::TileMap;

TileMap::TileMap(int width, int height, int cellWidth, int cellHeight)
        : width_(width), height_(height), cellWidth_(cellWidth), cellHeight_(cellHeight)
{
    areas_.resize(width_ * height_);
}

void TileMap::setCell(int x, int y, const TextureArea* area)
{
    areas_.at((size_t)(width_ * y + x)) = area;
}

void TileMap::copyTo(Renderer& renderer) const
{
    if (!isVisible_)
        return;
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            Area area((int)std::floor(pos_[0] + scale_[0] * x * cellWidth_), (int)std::floor(pos_[1] + scale_[1] * y * cellHeight_), (int)std::ceil(scale_[0] * cellWidth_), (int)std::ceil(scale_[1] * cellHeight_));
            areas_.at((size_t)(width_ * y + x))->copyTo(renderer, area, rot_, isFlipped_);
        }
    }
}

void TileMap::update(const math::Vector<double, 3>& pos, const math::Vector<double, 2>& scale, double rot, bool isFlipped, bool isVisible)
{
    pos_       = pos;
    scale_     = scale;
    rot_       = rot;
    isFlipped_ = isFlipped;
    isVisible_ = isVisible;
}
