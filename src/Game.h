#ifndef GAME_H
#define GAME_H

#include "MainScene.h"

#include <engine/SceneManager.h>
#include <string>

class Game {
  public:
    struct Config {
        std::string assets;
        std::string title;
    };
    Game(const Config& config);
    void run();

  private:
    Config config_;
    engine::SceneManager sceneManager_;
    bool isRunning_;
};

#endif
