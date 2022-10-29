#include "MainScene.h"

MainScene::MainScene()
        : node_("main_scene")
{
    world_.attachTo(&node_);
}

void MainScene::update()
{
    world_.update();
}

void MainScene::attachTo(engine::SceneNode* node)
{
    node->attach(&node_);
}
void MainScene::detachFrom(engine::SceneNode* node)
{
    node->detach(&node_);
}
