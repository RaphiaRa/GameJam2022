#ifndef ENGINE_MOVABLE_H
#define ENGINE_MOVABLE_H
#include "Math.h"
namespace engine
{
class Movable {
  public:
    virtual ~Movable() = default;

    virtual void setPos(const math::Vector<double, 3>& pos)     = 0;
    virtual void translate(const math::Vector<double, 3>& v)    = 0;
    virtual void setScale(const math::Vector<double, 2>& scale) = 0;
    virtual void scale(const math::Vector<double, 2>& scale)    = 0;
    virtual void setRot(double rot)                             = 0;
    virtual void rotate(double rot)                             = 0;
    virtual void setIsFlipped(bool isFlipped)                   = 0;
    virtual void flip()                                         = 0;
    virtual void setIsVisible(bool isVisible)                   = 0;
};
} // namespace engine

#endif
