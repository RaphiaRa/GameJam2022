#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameEntity.h"

#include <engine/AnimatedSprite.h>
#include <engine/Input.h>
#include <engine/SolidRect.h>
#include <engine/Sprite.h>
#include <engine/TileSet.h>

class Attack : public GameEntity {
  public:
    Attack();
    void update(std::chrono::nanoseconds delta) override;
    void attachTo(engine::SceneNode* node) override;
    void detachFrom(engine::SceneNode* node) override;
    const engine::SolidRect& hitBox() const { return solid_; }
    bool isActive() const;
    void start();

  private:
    engine::SceneNode node_;
    engine::SceneNode boxNode_;
    engine::TileSet tileSet_;
    engine::AnimatedSprite animation_;
    engine::SolidRect solid_;
};

class Character : public GameEntity {
  public:
    struct Motion {
        int up    = 0;
        int down  = 0;
        int right = 0;
        int left  = 0;
    };
    Character();
    void update(std::chrono::nanoseconds delta) override;
    void attachTo(engine::SceneNode* node) override;
    void detachFrom(engine::SceneNode* node) override;

    void handleInput(const engine::KeyEvent& ev);

    engine::SceneNode& node() { return node_; }
    int speed() const { return speed_; }
    const engine::SolidRect& hitBox() const { return solid_; }
    const engine::SolidRect& attackHitBox() const { return attack_.hitBox(); }
    bool isAttacking() const { return attack_.isActive(); }
    void damage(int dmg);
    int power() const { return power_; }
    int hp() const { return hp_; }

  private:
    engine::TileSet tileSet_;
    engine::AnimatedSprite animatedSprite_;
    engine::SceneNode node_;
    Motion motion_;
    int speed_;
    bool isFlipped_;
    Attack attack_;
    engine::SolidRect solid_;
    bool qPushed_;
    int hp_                              = 100;
    int power_                           = 25;
    std::chrono::nanoseconds immuneTime_ = std::chrono::nanoseconds(0);
    bool isImmune_                       = false;
};

#endif
