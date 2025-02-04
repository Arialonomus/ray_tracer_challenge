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
            utils::areEqual(m_shininess, rhs.getShininess()) &&
            utils::areEqual(m_reflectivity, rhs.getReflectivity()) &&
            utils::areEqual(m_transparency, rhs.getTransparency()) &&
            utils::areEqual(m_refractive_index, rhs.getRefractiveIndex());
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