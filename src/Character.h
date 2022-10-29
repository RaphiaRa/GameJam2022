#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameEntity.h"

#include <engine/AnimatedSprite.h>
#include <engine/Input.h>
#include <engine/Sprite.h>
#include <engine/TileSet.h>

class Attack : public GameEntity {
  public:
    Attack();
    void update(std::chrono::nanoseconds delta) override;
    void attachTo(engine::SceneNode* node) override;
    void detachFrom(engine::SceneNode* node) override;
    void start();

  private:
    engine::SceneNode node_;
    engine::TileSet tileSet_;
    engine::AnimatedSprite animation_;
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

    const engine::math::Vector<double, 3>& absPos() const;
    engine::SceneNode& node() { return node_; }
    int speed() const { return speed_; }

  private:
    engine::TileSet tileSet_;
    engine::AnimatedSprite animatedSprite_;
    engine::SceneNode node_;
    Motion motion_;
    int speed_;
    bool isFlipped_;
    Attack attack_;
};

#endif
