#include <cmath>
#include <engine/Sprite.h>

using engine::Sprite;
Sprite::Sprite(const TextureArea* texArea)
        : texArea_(texArea), pos_{ 0, 0, 0 }, scale_{ 0, 0 }, rot_(0.0), isFlipped_(false), isVisible_(false)
{
}

void Sprite::update(const math::Vector<double, 3>& pos, const math::Vector<double, 2>& scale, double rot, bool isFlipped, bool isVisible)
{
    pos_       = pos;
    scale_     = scale;
    rot_       = rot;
    isFlipped_ = isFlipped;
    isVisible_ = isVisible;
}

void Sprite::notifyAttach()
{
    isVisible_ = true;
}
void Sprite::notifyDetach()
{
    isVisible_ = false;
}
void Sprite::copyTo(Renderer& renderer) const
{
    if (!isVisible_)
        return;
    Area area((int)std::floor(pos_[0]), (int)std::floor(pos_[1]), (int)std::ceil(scale_[0] * texArea_->width()), (int)std::ceil(scale_[1] * texArea_->height()));
    texArea_->copyTo(renderer, area, rot_, isFlipped_);
}
