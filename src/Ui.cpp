#include "Ui.h"

#include "Assets.h"

Ui::Ui()
        : node_("ui"),
          apBarNode_("ap_bar"),
          apBarTexture_(Assets::get().getTexture("ap_bar1"), engine::nullArea),
          apBarSprite_(&apBarTexture_),
          hpBarNode_("hp_bar"),
          hpBarTexture_(Assets::get().getTexture("hp_bar1"), engine::nullArea),
          hpBarSprite_(&hpBarTexture_),
          hp_(0),
          ap_(0)
{
    node_.attach(&apBarNode_);
    node_.attach(&hpBarNode_);
    node_.setPos({ 10, 10, 100 });
    apBarNode_.attach(&apBarSprite_);
    hpBarNode_.setPos({ 0, 25, 0 });
    hpBarNode_.attach(&hpBarSprite_);
}

void Ui::update(std::chrono::nanoseconds delta)
{
    double scale = ap_ / 50.0;
    apBarNode_.setScale({ scale, 1.0 });
    scale = hp_ / 100.0;
    hpBarNode_.setScale({ scale, 1.0 });
    (void)delta;
}

void Ui::attachTo(engine::SceneNode* node)
{
    node->attach(&node_);
}
void Ui::detachFrom(engine::SceneNode* node)
{
    node->detach(&node_);
}
