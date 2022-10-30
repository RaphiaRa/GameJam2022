#include "MainScene.h"

#include "Assets.h"

MainScene::MainScene()
        : node_("main_scene"), apNode_("ap_bar")
{
    world_.attachTo(&node_);
    ui_.attachTo(&node_);
}

void MainScene::update(std::chrono::nanoseconds delta)
{
    world_.update(delta);
    ui_.setAp(world_.getPlayerAp());
    ui_.setHp(world_.getPlayerHp());
    ui_.update(delta);
}

void MainScene::attachTo(engine::SceneNode* node)
{
    node->attach(&node_);
}
void MainScene::detachFrom(engine::SceneNode* node)
{
    node->detach(&node_);
}
