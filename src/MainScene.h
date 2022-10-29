#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

#include "GameEntity.h"
#include "World.h"

class MainScene final : public GameEntity {
  public:
    MainScene();
    void update(std::chrono::nanoseconds delta) override;
    void attachTo(engine::SceneNode* node) override;
    void detachFrom(engine::SceneNode* node) override;

  private:
    engine::SceneNode node_;
    World world_;
};

#endif
