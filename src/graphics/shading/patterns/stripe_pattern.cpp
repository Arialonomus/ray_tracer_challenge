#include "stripe_pattern.hpp"

#include <cmath>

namespace gfx {
    Color StripePattern::samplePatternAt(const Vector4& pattern_point) const
    {
        if (static_cast<int>(std::floor(pattern_point.x())) % 2 == 0) {
            return this->getColorA();
        }

        return this->getColorB();
    }

    bool StripePattern::equal(const Pattern& other) const
    {
        const StripePattern& other_stripe_pattern{ dynamic_cast<const StripePattern&>(other) };
        return
            this->getTransform() == other_stripe_pattern.getTransform() &&
            this->getColorA() == other_stripe_pattern.getColorA() &&
            this->getColorB() == other_stripe_pattern.getColorB();
    }
}