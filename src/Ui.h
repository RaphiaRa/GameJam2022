#ifndef UI_H
#define UI_H

#include "GameEntity.h"
#include "World.h"

#include <engine/Sprite.h>

class Ui final : public GameEntity {
  public:
    Ui();
    void update(std::chrono::nanoseconds delta) override;
    void attachTo(engine::SceneNode* node) override;
    void detachFrom(engine::SceneNode* node) override;
    void setAp(int ap) { ap_ = ap; }
    void setHp(int hp) { hp_ = hp; }

  private:
    engine::SceneNode node_;
    engine::SceneNode apBarNode_;
    engine::TextureArea apBarTexture_;
    engine::Sprite apBarSprite_;
    engine::SceneNode hpBarNode_;
    engine::TextureArea hpBarTexture_;
    engine::Sprite hpBarSprite_;
    int hp_;
    int ap_;
};

#endif
