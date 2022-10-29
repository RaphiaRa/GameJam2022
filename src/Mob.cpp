#include "Mob.h"

#include "Assets.h"

#include <random>

Mob::Mob(double x, double y)
        : node_("mob"), tileSet_(Assets::get().getTexture("mob1"), 2, 1)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 100);
    int shift = dist(rng);
    animation_.addAnimation("idle", engine::Animation({ engine::AnimationFrame{ tileSet_.at(0, 0), std::chrono::milliseconds(150 + shift) },
                                                        engine::AnimationFrame{ tileSet_.at(1, 0), std::chrono::milliseconds(150 + shift) } }));
    node_.attach(&animation_);
    animation_.play("idle", true);
    node_.setPos({ x, y, 0.0 });
}

void Mob::update(std::chrono::nanoseconds delta)
{
    animation_.update(delta);
}

void Mob::attachTo(engine::SceneNode* node)
{
    node->attach(&node_);
}

void Mob::detachFrom(engine::SceneNode* node)
{
    node->detach(&node_);
}
