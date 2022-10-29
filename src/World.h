#ifndef WORLD_H
#define WORLD_H

#include "Character.h"
#include "Room.h"

class World : public GameEntity {
  public:
    World();
    void update() override;
    void attachTo(engine::SceneNode* node) override;
    void detachFrom(engine::SceneNode* node) override;

  private:
    engine::SceneNode node_;
    Character character_;
    Room room_;
};

#endif
