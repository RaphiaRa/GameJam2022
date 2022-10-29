#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H

#include "Clickable.h"

#include <functional>
#include <map>
#include <string>

namespace engine
{
enum class KeyEventType {
    down,
    up,
};

enum class Key {
    q,
    w,
    e,
    r,
    a,
    s,
    d,
    f,
    esc
};

struct KeyEvent {
    KeyEventType type;
    Key key;
};

class Input {
  public:
    /** bind
     *@brief Bind a callback function to a SDL_MouseButtonEvent
     *@param id: Id of the binding
     *@param callback: Callback which is called if a SDL_MouseButtonEvent occurs
     **/
    void bind(const std::string& id, std::function<void(const ClickEvent&)> callback);

    /** bind
     *@brief Bind a clickable object that implements its own bind callback methods
     *@param id: Id of the binding
     *@param callback: Callback which is called if a MouseClick occurs
     **/
    void bind(const std::string& id, Clickable& clickable);

    /** bind
     *@brief Bind a callback function to a SDL_KeyboardEvent
     *@param id: Id of the binding
     *@param callback: Callback which is called if a SDL_KeyboardEvent occurs
     **/
    void bind(const std::string& id, std::function<void(const KeyEvent& keyEvent)> callback);

    /** remove
     *@brief Removes the binding with this id
     *@param id: Id of the binding
     *@param callback: Callback which is called if a SDL_MouseButtonEvent occurs
     **/
    void remove(const std::string& id);

    /** update
     *@brief Polls events and calls the appropiate callbacks
     **/
    void update();

  private:
    std::map<std::string, std::function<void(const ClickEvent&)>> clickHandlers_;
    std::map<std::string, std::function<void(const KeyEvent&)>> keyHandlers_;
};
} // namespace engine

#endif
