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
    std::uniform_int_distribution<std::mt19937::result_type> dist3(0, 80);
    int shift     = dist(rng);
    double shift2 = (double)dist2(rng);
    xmshift_      = dist3(rng);
    ymshift_      = dist3(rng);
    animation_.addAnimation("idle", engine::Animation({ engine::AnimationFrame{ tileSet_.at(0, 0), std::chrono::milliseconds(150 + shift) },
                                                        engine::AnimationFrame{ tileSet_.at(1, 0), std::chrono::milliseconds(150 + shift) } }));
    node_.attach(&animation_);
    node_.attach(&solid_);
    animation_.play("idle", true);
    node_.setPos({ x, y, 0.0 });
    node_.scale(engine::math::Vector<double, 2>{ 0.5, 0.5 });
    hp_ += (1.5 * (double)score);
    speed_ += score / 30 + shift2 / 30.0;
    power_ += (int)((double)score / 25.0);
    double scale = 1.0 + ((double)(score) / 35.0);
    node_.scale(scale * engine::math::Vector<double, 2>{ 1.0, 1.0 });
}

template<typename T>
int sgn(T val)
{
    return (T(0) < val) - (val < T(0));
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

            if (abs(v[0]) > 80.0 + (double)xmshift_ && abs(v[0]) > abs(v[1])) {
                normalized[0] += sgn(normalized[0]) * abs(normalized[1]);
                normalized[1] = 0.0;
            }
            if (abs(v[1]) > 80.0 + (double)xmshift_ && abs(v[1]) > abs(v[0])) {
                normalized[1] += sgn(normalized[1]) * abs(normalized[0]);
                normalized[0] = 0.0;
            }
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
