#ifndef MOB_H
#define MOB_H

#include "GameEntity.h"

#include <engine/AnimatedSprite.h>
#include <engine/SolidRect.h>
#include <engine/TileSet.h>

class Mob : public GameEntity {
  public:
    Mob(double x, double y, int score, engine::SceneNode& followPoint);
    void update(std::chrono::nanoseconds delta) override;
    void attachTo(engine::SceneNode* node) override;
    void detachFrom(engine::SceneNode* node) override;
    const engine::SolidRect& hitBox() const { return solid_; }
    int power() const { return power_; }
    void damage(int dmg);
    int hp() const { return hp_; }
    engine::SceneNode& node() { return node_; }
    bool isActive() const { return isActive_; }
    double speed() const { return speed_; }

  private:
    engine::SceneNode node_;
    engine::TileSet tileSet_;
    engine::AnimatedSprite animation_;
    engine::SolidRect solid_;
    engine::SceneNode& followPoint_;
    double speed_                        = 1.5;
    int power_                           = 3;
    int hp_                              = 40;
    bool isActive_                       = false;
    std::chrono::nanoseconds immuneTime_ = std::chrono::nanoseconds(0);
    bool isImmune                        = false;
    int xmshift_                         = 0;
    int ymshift_                         = 0;
};

#endif
