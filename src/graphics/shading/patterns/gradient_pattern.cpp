#include "gradient_pattern.hpp"

#include <cmath>

namespace gfx {
    Color GradientPattern::samplePatternAt(const Vector4& pattern_point) const
    {
        return m_color_a + (m_color_b - m_color_a) * (pattern_point.x() - std::floor(pattern_point.x()));
    }

    bool GradientPattern::equal(const Pattern& other) const
    {
        const GradientPattern& other_stripe_pattern{ dynamic_cast<const GradientPattern&>(other) };
        return
                this->getTransform() == other_stripe_pattern.getTransform() &&
                m_color_a == other_stripe_pattern.getColorA() &&
                m_color_b == other_stripe_pattern.getColorB();
    }
}