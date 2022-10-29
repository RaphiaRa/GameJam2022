#ifndef ENGINE_SPRITE_ANIMATION_H
#define ENGINE_SPRITE_ANIMATION_H

#include "Sprite.h"

#include <chrono>
#include <map>
#include <vector>

namespace engine
{
struct AnimationFrame {
    TextureArea sprite;
    std::chrono::nanoseconds duration;
};

class Animation {
  public:
    Animation(std::vector<AnimationFrame> frames) : frames_(frames){};
    const std::vector<AnimationFrame>& frames() const noexcept { return frames_; }

  private:
    std::vector<AnimationFrame> frames_;
};

class AnimationPlayer {
  public:
    AnimationPlayer() = default;
    void play(Animation* animation, bool repeating = false) noexcept;
    void stop() noexcept { isPlaying_ = false; }
    void pause() noexcept { isPlaying_ = false; }
    bool isPlaying() const noexcept { return isPlaying_; }
    void update(std::chrono::nanoseconds delta) noexcept;
    const TextureArea& currentTextureArea() const noexcept;

  private:
    std::chrono::nanoseconds elapsed_ = std::chrono::nanoseconds(0);
    Animation* animation_             = nullptr;
    bool isPlaying_                   = false;
    bool isRepeating_                 = false;
    std::size_t currentFrame_         = 0;
    std::size_t startFrame_           = 0;
    std::size_t endFrame_             = 0;
};

class AnimatedSprite : public Renderable {
  public:
    AnimatedSprite(const TextureArea& defaultSprite);
    AnimatedSprite()          = default;
    virtual ~AnimatedSprite() = default;
    void copyTo(Renderer& renderer) const override;
    void stop();
    void play(std::string_view id, bool repeat = false);
    void addAnimation(std::string_view id, Animation animation);
    void update(std::chrono::nanoseconds delta);
    bool isPlaying() const;

  private:
    void notifyAttach() override;
    void notifyDetach() override;
    void update(const math::Vector<double, 3>& pos, const math::Vector<double, 2>& scale, double rot, bool isFlipped, bool isVisible) override;

    TextureArea defaultArea_;
    AnimationPlayer animationPlayer_;
    std::map<std::string, Animation> animation_;

    math::Vector<double, 3> pos_;
    math::Vector<double, 2> scale_;
    double rot_;
    bool isFlipped_;
    bool isVisible_;
};
} // namespace engine
#endif
