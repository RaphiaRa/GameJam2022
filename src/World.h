#ifndef WORLD_H
#define WORLD_H

#include "Character.h"
#include "Mob.h"
#include "Room.h"

#include <chrono>

class World : public GameEntity {
  public:
    World();
    void update(std::chrono::nanoseconds delta) override;
    void attachTo(engine::SceneNode* node) override;
    void detachFrom(engine::SceneNode* node) override;
    int getPlayerAp() const { return character_.stamina(); }
    int getPlayerHp() const { return character_.hp(); }

  private:
    engine::SceneNode node_;
    Character character_;
    Room room_;
    std::list<std::unique_ptr<Mob>> mobs_;
    std::chrono::nanoseconds sinceLastWave_;
    bool haveWave_;
    int score_;
};

#endif
