#include "Game.h"

#include <chrono>
#include <iostream>
#include <lyra/lyra.hpp>

static std::string assets;
auto cli = lyra::cli()
           | lyra::opt(assets, "assets")
                   ["-a"]["--assets"]("Path to the assets directory");

int main(int argc, char** argv)
{
    auto result = cli.parse({ argc, argv });
    if (!result) {
        std::cerr << "Error in command line: " << result.message() << std::endl;
        return -1;
    }
    Game::Config config;
    config.assets = assets;
    config.title  = "Test";
    
    Game game(config);
    game.run();
}
