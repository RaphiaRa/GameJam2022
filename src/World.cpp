#include "World.h"

World::World()
        : node_("world")
{
    character_.attachTo(&node_);
    room_.attachTo(&node_);
}

void World::update()
{
    character_.update();
}

void World::attachTo(engine::SceneNode* node)
{
    node->attach(&node_);
}

void World::detachFrom(engine::SceneNode* node)
{
    node->detach(&node_);
}
