#include "Character.h"

#include "Assets.h"
#include "Input.h"

Attack::Attack()
        : node_("attack"), tileSet_(Assets::get().getTexture("attack1"), 2, 1)
{
    animation_.addAnimation("attack", engine::Animation({ engine::AnimationFrame{ tileSet_.at(0, 0), std::chrono::milliseconds(50) },
                                                          engine::AnimationFrame{ tileSet_.at(1, 0), std::chrono::milliseconds(100) } }));
    node_.attach(&animation_);
    node_.setPos({ -20.0, -20.0, 0 });
}

void Attack::update(std::chrono::nanoseconds delta)
{
    animation_.update(delta);
}

void Attack::attachTo(engine::SceneNode* node)
{
    node->attach(&node_);
}

void Attack::detachFrom(engine::SceneNode* node)
{
    node->detach(&node_);
}

void Attack::start()
{
    if (!animation_.isPlaying())
        animation_.play("attack");
}

Character::Character()
        : tileSet_(Assets::get().getTexture("char1"), 2, 1),
          animatedSprite_(tileSet_.at(1, 0)),
          node_("character"),
          motion_{ 0, 0 },
          speed_(5)
{
    animatedSprite_.addAnimation("run", engine::Animation({ engine::AnimationFrame{ tileSet_.at(1, 0), std::chrono::milliseconds(100) },
                                                            engine::AnimationFrame{ tileSet_.at(0, 0), std::chrono::milliseconds(150) } }));

    node_.attach(&animatedSprite_);
    attack_.attachTo(&node_);
}

void Character::update(std::chrono::nanoseconds delta)
{
    engine::math::Vector<double, 3> t{ 0, 0, 0 };
    if (motion_.down)
        t[1] += speed_;
    if (motion_.up)
        t[1] -= speed_;
    if (motion_.right)
        t[0] += speed_;
    if (motion_.left)
        t[0] -= speed_;
    if (t[0] > 0)
        isFlipped_ = true;
    else if (t[0] < 0)
        isFlipped_ = false;
    node_.translate(t);
    if ((t[0] != 0 || t[1] != 0) && !animatedSprite_.isPlaying()) {
        animatedSprite_.play("run", true);
    } else if (t[0] == 0 && t[1] == 0 && animatedSprite_.isPlaying()) {
        animatedSprite_.stop();
    }
    node_.setIsFlipped(isFlipped_);
    animatedSprite_.update(delta);
    attack_.update(delta);
}

void Character::attachTo(engine::SceneNode* node)
{
    inputHandler().bind("character", [this](const engine::KeyEvent& ev) { this->handleInput(ev); });
    node->attach(&node_);
}

void Character::detachFrom(engine::SceneNode* node)
{
    inputHandler().remove("character");
    node->detach(&node_);
}

void Character::handleInput(const engine::KeyEvent& ev)
{

    if (ev.type == engine::KeyEventType::down) {
        if (ev.key == engine::Key::w)
            motion_.up = 1;
        if (ev.key == engine::Key::s)
            motion_.down = 1;
        if (ev.key == engine::Key::a)
            motion_.left = 1;
        if (ev.key == engine::Key::d)
            motion_.right = 1;
        if (ev.key == engine::Key::q)
            attack_.start();
    } else if (ev.type == engine::KeyEventType::up) {
        animatedSprite_.stop();
        if (ev.key == engine::Key::w)
            motion_.up = 0;
        if (ev.key == engine::Key::s)
            motion_.down = 0;
        if (ev.key == engine::Key::a)
            motion_.left = 0;
        if (ev.key == engine::Key::d)
            motion_.right = 0;
    }
}

const engine::math::Vector<double, 3>& Character::absPos() const
{
    return node_.absPos();
}
