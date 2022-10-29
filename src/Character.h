#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameEntity.h"

#include <engine/Input.h>
#include <engine/Sprite.h>
#include <engine/TileSet.h>

class Character : public GameEntity {
  public:
    struct Motion {
        int up    = 0;
        int down  = 0;
        int right = 0;
        int left  = 0;
    };
    Character();
    void update() override;
    void attachTo(engine::SceneNode* node) override;
    void detachFrom(engine::SceneNode* node) override;

    void handleInput(const engine::KeyEvent& ev);

  private:
    engine::TileSet tileSet_;
    engine::Sprite sprite_;
    engine::SceneNode node_;
    Motion motion_;
    int speed_;
    bool isFlipped_;
};

#endif
