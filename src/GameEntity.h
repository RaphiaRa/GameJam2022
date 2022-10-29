#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <engine/SceneNode.h>

class GameEntity {
  public:
    virtual ~GameEntity()                            = default;
    virtual void update()                            = 0;
    virtual void attachTo(engine::SceneNode* node)   = 0;
    virtual void detachFrom(engine::SceneNode* node) = 0;
};

#endif
