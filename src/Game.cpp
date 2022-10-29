#include "Game.h"

#include "Assets.h"
#include "Input.h"

#include <engine/Renderer.h>

Game::Game(const Config& config)
        : config_(config), sceneManager_(), isRunning_(false)
{
    inputHandler().bind("exit", [this](const engine::KeyEvent& ev) {
        if (ev.type == engine::KeyEventType::down && ev.key == engine::Key::esc)
            this->isRunning_ = false; });
}

void Game::run()
{

    auto renderer = engine::Renderer::create(engine::Renderer::Backend::sdl, { 0, 0, 800, 600 }, config_.title);
    Assets::init(*renderer, config_.assets);

    MainScene mainScene;
    mainScene.attachTo(&sceneManager_.root());

    engine::RenderableList renderableList;
    isRunning_ = true;
    while (isRunning_) {
        renderableList.clear();
        sceneManager_.root().collectRenderables(renderableList);
        inputHandler().update();
        mainScene.update();
        sceneManager_.root().update();
        renderer->clear();
        for (auto& pair : renderableList) {
            const engine::Renderable* renderable = reinterpret_cast<const engine::Renderable*>(pair.second);
            renderable->copyTo(*renderer);
        }
        renderer->update();
    }
}
