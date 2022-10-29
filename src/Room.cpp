#include "Room.h"

#include "Assets.h"

#include <engine/TileSet.h>

Room::Room()
        : node_(), tileSet_(Assets::get().getTexture("floor1"), 1, 1), tileMap_(16, 8, 64, 64)
{
    for (int x = 0; x < 16; ++x) {
        for (int y = 0; y < 8; ++y) {
            tileMap_.setCell(x, y, &tileSet_.at(0, 0));
        }
    }
    node_.attach(&tileMap_);
    node_.setPos({ 0, 0, -1 });
}

void Room::update(std::chrono::nanoseconds delta)
{
}

void Room::attachTo(engine::SceneNode* node)
{
    node->attach(&node_);
}

void Room::detachFrom(engine::SceneNode* node)
{
    node->attach(&node_);
}
