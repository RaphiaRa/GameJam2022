#include <cmath>
#include <engine/AnimatedSprite.h>

using engine::AnimatedSprite;
using engine::AnimationPlayer;

void AnimationPlayer::play(Animation* animation, bool repeating) noexcept
{
    animation_    = animation;
    isRepeating_  = repeating;
    startFrame_   = 0;
    currentFrame_ = startFrame_;
    endFrame_     = animation_->frames().size();
    isPlaying_    = true;
    elapsed_      = std::chrono::nanoseconds(0);
}

void AnimationPlayer::update(std::chrono::nanoseconds delta) noexcept
{
    elapsed_ += delta;
    if (isPlaying_) {
        if (elapsed_ > animation_->frames().at(currentFrame_).duration) {
            ++currentFrame_;
            if (currentFrame_ == endFrame_) {
                if (isRepeating_)
                    currentFrame_ = startFrame_;
                else
                    isPlaying_ = false;
            }
            elapsed_ = std::chrono::nanoseconds(0);
        }
    }
}

const engine::TextureArea& AnimationPlayer::currentTextureArea() const noexcept
{
    return animation_->frames().at(currentFrame_).sprite;
}

AnimatedSprite::AnimatedSprite(const TextureArea& area)
        : defaultArea_(area)
{
}

void AnimatedSprite::update(std::chrono::nanoseconds delta)
{
    animationPlayer_.update(delta);
}

void AnimatedSprite::copyTo(Renderer& renderer) const
{
    if (animationPlayer_.isPlaying()) {
        const TextureArea* texArea = &animationPlayer_.currentTextureArea();
        Area area((int)std::floor(pos_[0]), (int)std::floor(pos_[1]), (int)std::ceil(scale_[0] * texArea->width()), (int)std::ceil(scale_[1] * texArea->height()));
        texArea->copyTo(renderer, area, rot_, isFlipped_);
    } else {
        if (!defaultArea_)
            return;
        const TextureArea* texArea = &defaultArea_;
        Area area((int)std::floor(pos_[0]), (int)std::floor(pos_[1]), (int)std::ceil(scale_[0] * texArea->width()), (int)std::ceil(scale_[1] * texArea->height()));
        texArea->copyTo(renderer, area, rot_, isFlipped_);
    }
}

void AnimatedSprite::stop()
{
    animationPlayer_.stop();
}

void AnimatedSprite::play(std::string_view id, bool repeat)
{
    animationPlayer_.play(&animation_.at(std::string(id)), repeat);
}

void AnimatedSprite::addAnimation(std::string_view id, Animation animation)
{
    animation_.emplace(id, std::move(animation));
}

void AnimatedSprite::notifyAttach()
{
}

void AnimatedSprite::notifyDetach()
{
}

void AnimatedSprite::update(const math::Vector<double, 3>& pos, const math::Vector<double, 2>& scale, double rot, bool isFlipped, bool isVisible)
{
    pos_       = pos;
    scale_     = scale;
    rot_       = rot;
    isFlipped_ = isFlipped;
    isVisible_ = isVisible;
}

bool AnimatedSprite::isPlaying() const
{
    return animationPlayer_.isPlaying();
}
