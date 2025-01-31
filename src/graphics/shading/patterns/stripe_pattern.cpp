#include "stripe_pattern.hpp"

#include <cmath>

namespace gfx {
    Color StripePattern::getSurfaceColorAt(const Vector4& point) const
    {
        if (static_cast<int>(std::floor(point.x())) % 2 == 0) {
            return m_color_a;
        }

        return m_color_b;
    }
}