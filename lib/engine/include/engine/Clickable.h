#ifndef ENGINE_CLICKABLE_H
#define ENGINE_CLICKABLE_H

namespace engine
{
enum class ClickEventType {
    up,
    down,
};

enum class MouseButton {
    left,
    right,
};

struct ClickEvent {
    ClickEventType type;
    MouseButton button;
};

class Clickable {
  public:
    virtual void handle(const ClickEvent& click) = 0;
};
} // namespace engine

#endif
