#include "material.hpp"

#include "util_functions.hpp"

namespace gfx {
    // Equality Operator
    bool gfx::Material::operator==(const Material& rhs) const
    {
        return
            *m_texture == rhs.getTexture() &&
            utils::areEqual(m_ambient, rhs.getAmbient()) &&
            utils::areEqual(m_diffuse, rhs.getDiffuse()) &&
            utils::areEqual(m_specular, rhs.getSpecular()) &&
            utils::areEqual(m_shininess, rhs.getShininess()) &&
            utils::areEqual(m_reflectivity, rhs.getReflectivity()) &&
            utils::areEqual(m_transparency, rhs.getTransparency()) &&
            utils::areEqual(m_refractive_index, rhs.getRefractiveIndex());
    }

    // Glassy Material Factory Function
    Material createGlassyMaterial()
    {
        return Material{
            0.1,
            0.9,
            0.9,
            200,
            0,
            1,
            1.5
        };
    }
}