#include "World.h"

#include <random>

World::World()
        : node_("world")
{
    character_.attachTo(&node_);
    room_.attachTo(&node_);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(3, 10);
    int count = (int)dist(rng);
    for (int k = 0; k < count; ++k) {
        int xshift = dist(rng);
        int yshift = dist(rng);
        auto mob   = std::make_unique<Mob>(300 + 10 * xshift, 50 * k + yshift);
        mob->attachTo(&node_);
        mobs_.push_back(std::move(mob));
    }
}

void World::update(std::chrono::nanoseconds delta)
{
    engine::math::Vector<double, 3> correction{ 0, 0, 0 };
    int speed = character_.speed();
    if (character_.absPos()[0] < 200)
        correction[0] = speed;
    else if (character_.absPos()[0] > 500)
        correction[0] = -speed;
    if (character_.absPos()[1] < 100)
        correction[1] = speed;
    else if (character_.absPos()[1] > 350)
        correction[1] = -speed;
    node_.translate(correction);
    character_.update(delta);
    for (auto& mob : mobs_) {
        mob->update(delta);
    }
}

void World::attachTo(engine::SceneNode* node)
{
    node->attach(&node_);
}

void World::detachFrom(engine::SceneNode* node)
{
    node->detach(&node_);
}
