#include "Character.h"

#include "Assets.h"
#include "Input.h"

Character::Character()
        : tileSet_(Assets::get().getTexture("char1"), 2, 1),
          sprite_(&tileSet_.at(1, 0)),
          node_("character"),
          motion_{ 0, 0 },
          speed_(5)
{
    node_.attach(&sprite_);
}

void Character::update()
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
    node_.setIsFlipped(isFlipped_);
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
    } else if (ev.type == engine::KeyEventType::up) {
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
