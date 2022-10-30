#ifndef ENGINE_SOLID_H
#define ENGINE_SOLID_H

#include "SceneObject.h"

namespace engine
{
class SolidRect : public SceneObject {
  public:
    SolidRect(double width, double height);
    void update(const math::Vector<double, 3>& pos, const math::Vector<double, 2>& scale, double rot, bool isFlipped, bool isVisible) override;
    virtual bool check(const SolidRect&, math::Vector<double, 2>& rebound) const;

  private:
    double width_;
    double height_;

    bool isVisible_;
    math::Vector<double, 2> pos_;
    math::Vector<double, 2> a_;
    math::Vector<double, 2> b_;
};
} // namespace engine

#endif
