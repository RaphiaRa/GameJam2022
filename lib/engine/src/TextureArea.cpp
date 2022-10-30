#include <engine/TextureArea.h>

using engine::TextureArea;
TextureArea::TextureArea(const Texture* texture, Area area)
        : texture_(texture), area_(area)
{
}

void TextureArea::copyTo(Renderer& renderer, const Area& dest, double rot, bool isFlipped) const
{
    if (texture_ == NULL)
        return;
    renderer.render(*texture_, area_, dest, rot, isFlipped);
}

int TextureArea::width() const noexcept
{
    if (area_.width == 0)
        return texture_->width();
    return area_.width;
}

int TextureArea::height() const noexcept
{
    if (area_.height == 0)
        return texture_->height();
    return area_.height;
}
