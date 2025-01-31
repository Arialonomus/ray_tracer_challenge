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

    bool StripePattern::equal(const Pattern& other) const
    {
        const StripePattern& other_stripe_pattern{ static_cast<const StripePattern&>(other) };
        return
            this->getTransform() == other_stripe_pattern.getTransform() &&
            m_color_a == other_stripe_pattern.getColorA() &&
            m_color_b == other_stripe_pattern.getColorB();
    }
}