#ifndef ROOM_H
#define ROOM_H

#include "GameEntity.h"

#include <engine/TileMap.h>
#include <engine/TileSet.h>

class Room : public GameEntity {
  public:
    Room();
    void update() override;
    void attachTo(engine::SceneNode* node) override;
    void detachFrom(engine::SceneNode* node) override;

  private:
    engine::SceneNode node_;
    engine::TileSet tileSet_;
    engine::TileMap tileMap_;
};

#endif
