#include "gradient_pattern.hpp"

#include <cmath>

namespace gfx {
    Color GradientPattern::samplePatternAt(const Vector4& pattern_point) const
    {
        return this->getColorA() + (this->getColorB() - this->getColorA()) * (pattern_point.x() - std::floor(pattern_point.x()));
    }

    bool GradientPattern::equal(const Pattern& other) const
    {
        const GradientPattern& other_stripe_pattern{ dynamic_cast<const GradientPattern&>(other) };
        return
                this->getTransform() == other_stripe_pattern.getTransform() &&
                this->getColorA() == other_stripe_pattern.getColorA() &&
                this->getColorB() == other_stripe_pattern.getColorB();
    }
}