#include <engine/SceneManager.h>

using engine::SceneManager;
using engine::SceneNode;

SceneManager::SceneManager() : root_("Root") {}

SceneNode& SceneManager::root()
{
    return root_;
}
