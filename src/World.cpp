#include "World.h"

#include <iostream>
#include <random>

World::World()
        : node_("world"), haveWave_(false), score_(0)
{
    character_.attachTo(&node_);
    room_.attachTo(&node_);
    sinceLastWave_ = std::chrono::nanoseconds(0);
}

void World::update(std::chrono::nanoseconds delta)
{
    engine::math::Vector<double, 3> correction{ 0, 0, 0 };
    engine::math::Vector<double, 3> charCorrection{ 0, 0, 0 };
    int speed = character_.speed();
    if (character_.node().absPos()[0] < 200)
        correction[0] = speed;
    else if (character_.node().absPos()[0] > 500)
        correction[0] = -speed;
    if (character_.node().absPos()[1] < 100)
        correction[1] = speed;
    else if (character_.node().absPos()[1] > 350)
        correction[1] = -speed;
    if (character_.node().pos()[0] < 0)
        charCorrection[0] = speed;
    else if (character_.node().pos()[0] > 15 * 64)
        charCorrection[0] = -speed;
    if (character_.node().pos()[1] < 0)
        charCorrection[1] = speed;
    else if (character_.node().pos()[1] > 7 * 64)
        charCorrection[1] = -speed;

    character_.update(delta);

    auto iter = mobs_.begin();
    while (iter != mobs_.end()) {
        auto& mob = *iter;
        mob->update(delta);
        if (mob->hp() > 0) {
            engine::math::Vector<double, 2UL> rebound;
            if (character_.hitBox().check(mob->hitBox(), rebound)) {
                charCorrection[0] += 10 * rebound[0];
                charCorrection[1] += 10 * rebound[1];
                character_.damage(mob->power());
            }
            if (character_.isAttacking() && character_.attackHitBox().check(mob->hitBox(), rebound)) {
                engine::math::Vector<double, 3> mobCorrection = {};
                mobCorrection[0] += -5 * rebound[0];
                mobCorrection[1] += -5 * rebound[1];
                mob->node().translate(mobCorrection);
                mob->damage(character_.power());
            }
            ++iter;
        } else {
            mob->detachFrom(&node_);
            iter = mobs_.erase(iter);
            score_ += 1;
        }
    }
    if (haveWave_) {
        if (mobs_.empty()) {
            sinceLastWave_ = std::chrono::nanoseconds(0);
            haveWave_      = false;
        }
    }

    // mob colissions
    for (auto& moba : mobs_) {
        for (auto& mobb : mobs_) {
            engine::math::Vector<double, 2UL> rebound;
            if (moba->hitBox().check(mobb->hitBox(), rebound)) {
                engine::math::Vector<double, 3> mobCorrection = {};

                mobCorrection[0] = moba->speed() * rebound[0];
                mobCorrection[1] = moba->speed() * rebound[1];
                moba->node().translate(mobCorrection);
            }
        }
    }

    node_.translate(correction);
    character_.node().translate(charCorrection);

    // spawn new wave
    if (!haveWave_) {
        sinceLastWave_ += delta;
        if (sinceLastWave_ >= std::chrono::seconds(2)) {
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist(8, 25 + score_ / 3);
            int count = (int)dist(rng);
            for (int k = 0; k < count; ++k) {
                int xshift = dist(rng);
                int yshift = dist(rng);
                auto mob   = std::make_unique<Mob>(1200 + 10 * xshift, 50 * k + yshift, score_, character_.node());
                mob->attachTo(&node_);
                mobs_.push_back(std::move(mob));
            }
            haveWave_ = true;
        }
    }

    // are we done yet?
    if (character_.hp() <= 0) {
        std::cout << "You Lost" << std::endl;
        std::cout << "Your score: " << score_ << std::endl;
        exit(1);
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
