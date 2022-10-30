#ifndef ENGINE_TILE_MAP_H
#define ENGINE_TILE_MAP_H
#include "Renderable.h"
#include "TextureArea.h"

#include <vector>

namespace engine
{
class TileMap : public Renderable {
  public:
    virtual ~TileMap() = default;
    TileMap(int width, int height, int cellWidth, int cellHeight);
    void setCell(int x, int y, const TextureArea* area);
    void copyTo(Renderer& renderer) const override;

  private:
    void update(const math::Vector<double, 3>& pos, const math::Vector<double, 2>& scale, double rot, bool isFlipped, bool isVisible) override;

    int width_;
    int height_;
    int cellWidth_;
    int cellHeight_;
    std::vector<const engine::TextureArea*> areas_;
    math::Vector<double, 3> pos_;
    math::Vector<double, 2> scale_;
    double rot_;
    bool isFlipped_;
    bool isVisible_;
};
} // namespace engine
#endif
