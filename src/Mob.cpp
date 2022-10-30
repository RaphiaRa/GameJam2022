#include "Mob.h"

#include "Assets.h"

#include <random>

Mob::Mob(double x, double y, int score, engine::SceneNode& followPoint)
        : node_("mob"), tileSet_(Assets::get().getTexture("mob1"), 2, 1), solid_(32, 32), followPoint_(followPoint)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 100);
    std::uniform_int_distribution<std::mt19937::result_type> dist2(0, 30);
    int shift     = dist(rng);
    double shift2 = (double)dist2(rng);
    animation_.addAnimation("idle", engine::Animation({ engine::AnimationFrame{ tileSet_.at(0, 0), std::chrono::milliseconds(150 + shift) },
                                                        engine::AnimationFrame{ tileSet_.at(1, 0), std::chrono::milliseconds(150 + shift) } }));
    node_.attach(&animation_);
    node_.attach(&solid_);
    animation_.play("idle", true);
    node_.setPos({ x, y, 0.0 });
    node_.scale(engine::math::Vector<double, 2>{ 0.5, 0.5 });
    hp_ += score;
    speed_ += score / 15 + shift2 / 20.0;
    power_ += (int)((double)score / 20.0);
    double scale = 1.0 + ((double)(score) / 20.0);
    node_.scale(scale * engine::math::Vector<double, 2>{ 1.0, 1.0 });
}

void Mob::update(std::chrono::nanoseconds delta)
{
    animation_.update(delta);
    if (isActive_) {
        auto v        = followPoint_.absPos() - node_.absPos();
        double length = sqrt((engine::math::std_norm(v)));
        if (length > 1.0) {
            auto normalized  = v / sqrt((engine::math::std_norm(v)));
            double perSecond = 10000000.0 / (double)delta.count();
            if (abs(v[0]) > 100.0)
                normalized[1] = 0.0;
            node_.translate(perSecond * speed_ * normalized);
        }
    }
    if (isImmune) {
        immuneTime_ += delta;
        if (immuneTime_ > std::chrono::milliseconds(300)) {
            isImmune    = false;
            immuneTime_ = std::chrono::nanoseconds(0);
        }
    }
}

void Mob::attachTo(engine::SceneNode* node)
{
    node->attach(&node_);
    isActive_ = true;
}

void Mob::detachFrom(engine::SceneNode* node)
{
    node->detach(&node_);
    isActive_ = false;
}

void Mob::damage(int dmg)
{
    if (!isImmune) {
        hp_ -= dmg;
        isImmune = true;
    }
}
