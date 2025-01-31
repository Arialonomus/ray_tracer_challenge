#include "checkered_pattern.hpp"

#include <cmath>

namespace gfx {
    Color CheckeredPattern::samplePatternAt(const Vector4& pattern_point) const
    {
        if (static_cast<int>(
                std::floor(pattern_point.x()) +
                std::floor(pattern_point.y()) +
                std::floor(pattern_point.z())
                ) % 2 == 0) {
            return this->getColorA();
        }

        return this->getColorB();
    }

    bool CheckeredPattern::equal(const Pattern& other) const
    {
        const CheckeredPattern& other_checkered_pattern{ dynamic_cast<const CheckeredPattern&>(other) };
        return
                this->getTransform() == other_checkered_pattern.getTransform() &&
                this->getColorA() == other_checkered_pattern.getColorA() &&
                this->getColorB() == other_checkered_pattern.getColorB();
    }
}