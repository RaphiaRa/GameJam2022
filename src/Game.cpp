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

static bool compareSceneObject(const engine::RenderableEntry& lh, const engine::RenderableEntry& rh) { return (lh.first < rh.first); }
void Game::run()
{

    auto renderer = engine::Renderer::create(engine::Renderer::Backend::sdl, { 0, 0, 800, 600 }, config_.title);
    Assets::init(*renderer, config_.assets);

    MainScene mainScene;
    mainScene.attachTo(&sceneManager_.root());

    engine::RenderableList renderableList;
    isRunning_ = true;
    auto tp1   = std::chrono::steady_clock::now();

    std::chrono::nanoseconds elapsed = std::chrono::nanoseconds(0);
    std::chrono::nanoseconds clock   = std::chrono::seconds(1 / 60);
    while (isRunning_) {
        renderableList.clear();
        sceneManager_.root().collectRenderables(renderableList);
        inputHandler().update();
        auto tp2   = std::chrono::steady_clock::now();
        auto delta = tp2 - tp1;
        tp1        = tp2;
        elapsed += delta;
        if (elapsed > clock) {
            mainScene.update(delta);
            sceneManager_.root().update();
            renderer->clear();
            std::sort(renderableList.begin(), renderableList.end());
            for (auto& pair : renderableList) {
                const engine::Renderable* renderable = reinterpret_cast<const engine::Renderable*>(pair.second);
                renderable->copyTo(*renderer);
            }
            renderer->update();
            elapsed = std::chrono::milliseconds(0);
        }
    }
}
