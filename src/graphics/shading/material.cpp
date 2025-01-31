#include "material.hpp"

#include "util_functions.hpp"

namespace gfx {
    // Equality Operator
    bool gfx::Material::operator==(const Material& rhs) const
    {
        return
            m_color == rhs.getColor() &&
            ((!m_pattern && !rhs.hasPattern()) || (m_pattern && rhs.hasPattern() && *m_pattern == rhs.getPattern())) &&
            utils::areEqual(m_ambient, rhs.getAmbient()) &&
            utils::areEqual(m_diffuse, rhs.getDiffuse()) &&
            utils::areEqual(m_specular, rhs.getSpecular()) &&
            utils::areEqual(m_shininess, rhs.getShininess());
    }

    // Pattern Mutator
    void Material::setPattern(const Pattern& pattern)
    {
        if (m_pattern) {
            *m_pattern = pattern;
        } else {
            m_pattern = pattern.clone();
        }
    }
}