#include <engine/SolidRect.h>

using engine::SolidRect;

SolidRect::SolidRect(double width, double height)
        : width_(width), height_(height)
{
}

void SolidRect::update(const math::Vector<double, 3>& pos, const math::Vector<double, 2>& scale, double rot, bool isFlipped, bool isVisible)
{
    isVisible_ = isVisible;
    pos_[0]    = pos[0];
    pos_[1]    = pos[1];
    a_[0]      = (pos[0] - scale[0] * width_ / 2.0);
    a_[1]      = (pos[1] + scale[1] * height_ / 2.0);
    b_[0]      = (pos[0] + scale[0] * width_ / 2.0);
    b_[1]      = (pos[1] - scale[1] * height_ / 2.0);
}

bool SolidRect::check(const SolidRect& rh, math::Vector<double, 2>& rebound) const
{
    if (a_[0] < rh.b_[0] && b_[0] > rh.a_[0] && a_[1] > rh.b_[1] && b_[1] < rh.a_[1]) {
        auto v   = rh.pos_ - pos_;
        auto len = sqrt((math::std_norm(v)));
        if (len < std::numeric_limits<double>::epsilon()) {
            rebound[0] = 1.0;
            rebound[0] = 0.0;
            return true;
        }
        auto normalized = v / sqrt((math::std_norm(v)));
        rebound         = -1 * normalized;
        return true;
    }
    return false;
}
