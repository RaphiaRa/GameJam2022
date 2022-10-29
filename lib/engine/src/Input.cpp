#include <SDL.h>
#include <engine/Input.h>

using engine::ClickEventType;
using engine::Input;
using engine::Key;
using engine::KeyEvent;
using engine::KeyEventType;
using engine::MouseButton;

static std::map<int, KeyEventType> keyEventTypeMap = {
    { SDL_KEYDOWN, KeyEventType::down },
    { SDL_KEYUP, KeyEventType::up },
};

static std::map<int, Key> keyMap = {
    { SDLK_q, Key::q },
    { SDLK_w, Key::w },
    { SDLK_e, Key::e },
    { SDLK_r, Key::r },
    { SDLK_a, Key::a },
    { SDLK_s, Key::s },
    { SDLK_d, Key::d },
    { SDLK_f, Key::f },
    { SDLK_ESCAPE, Key::esc },
};

static std::map<int, ClickEventType> clickEventTypeMap = {
    { SDL_MOUSEBUTTONDOWN, ClickEventType::down },
    { SDL_MOUSEBUTTONUP, ClickEventType::up },
};

static std::map<int, MouseButton> mouseButtonMap = {
    { SDL_BUTTON_LEFT, MouseButton::left },
    { SDL_BUTTON_RIGHT, MouseButton::right },
};

void Input::bind(const std::string& id, std::function<void(const ClickEvent&)> callback)
{
    clickHandlers_.emplace(id, callback);
}

void Input::bind(const std::string& id, Clickable& clickable)
{
    clickHandlers_.emplace(id, [&clickable](const ClickEvent& click) { clickable.handle(click); });
}

void Input::bind(const std::string& id, std::function<void(const KeyEvent& keyEvent)> callback)
{
    keyHandlers_.emplace(id, callback);
}

void Input::remove(const std::string& id)
{
    keyHandlers_.erase(id);
    clickHandlers_.erase(id);
}

void Input::update()
{
    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_KEYUP) {
            KeyEvent event;
            event.type = keyEventTypeMap[sdlEvent.type];
            event.key  = keyMap[sdlEvent.key.keysym.sym];
            for (auto& tuple : keyHandlers_) {
                tuple.second(event);
            }
        } else if (sdlEvent.type == SDL_MOUSEBUTTONUP || sdlEvent.type == SDL_MOUSEBUTTONDOWN) {
            ClickEvent event;
            event.type   = clickEventTypeMap[sdlEvent.type];
            event.button = mouseButtonMap[sdlEvent.button.button];
            for (auto& tuple : clickHandlers_) {
                tuple.second(event);
            }
        }
    }
}
