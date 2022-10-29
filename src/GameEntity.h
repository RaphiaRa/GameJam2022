#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <chrono>
#include <engine/SceneNode.h>

class GameEntity {
  public:
    virtual ~GameEntity()                                                       = default;
    virtual void update(std::chrono::nanoseconds delta) = 0;
    virtual void attachTo(engine::SceneNode* node)                              = 0;
    virtual void detachFrom(engine::SceneNode* node)                            = 0;
};

#endif
