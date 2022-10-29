#ifndef ENGINE_SCENEMANAGER_H
#define ENGINE_SCENEMANAGER_H
#include "SceneNode.h"

#include <memory>

namespace engine
{
class SceneManager {
  public:
    SceneManager();
    SceneNode& root();

  private:
    SceneNode root_;
};
} // namespace engine
#endif
