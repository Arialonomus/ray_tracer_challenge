#include "ring_pattern.hpp"

#include <cmath>

namespace gfx {
    Color RingPattern::samplePatternAt(const Vector4& pattern_point) const
    {
        const double radius{ std::sqrt(std::pow(pattern_point.x(), 2) + std::pow(pattern_point.z(), 2)) };
        if (static_cast<int>(std::floor(radius)) % 2 == 0) {
            return this->getColorA();
        }

        return this->getColorB();
    }

    bool RingPattern::equal(const Pattern& other) const
    {
        const RingPattern& other_ring_pattern{ dynamic_cast<const RingPattern&>(other) };
        return
                this->getTransform() == other_ring_pattern.getTransform() &&
                this->getColorA() == other_ring_pattern.getColorA() &&
                this->getColorB() == other_ring_pattern.getColorB();
    }
}