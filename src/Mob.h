#ifndef MOB_H
#define MOB_H

#include "GameEntity.h"

#include <engine/AnimatedSprite.h>
#include <engine/TileSet.h>

class Mob : public GameEntity {
  public:
    Mob(double x, double y);
    void update(std::chrono::nanoseconds delta) override;
    void attachTo(engine::SceneNode* node) override;
    void detachFrom(engine::SceneNode* node) override;

  private:
    engine::SceneNode node_;
    engine::TileSet tileSet_;
    engine::AnimatedSprite animation_;
};

#endif
