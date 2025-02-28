#include "material.hpp"

#include "util_functions.hpp"

namespace gfx {
    // Material Properties Equality Operator
    bool MaterialProperties::operator==(const MaterialProperties& rhs) const
    {
        return
                utils::areEqual(ambient, rhs.ambient) &&
                utils::areEqual(ambient, rhs.ambient) &&
                utils::areEqual(specular, rhs.specular) &&
                utils::areEqual(shininess, rhs.shininess) &&
                utils::areEqual(reflectivity, rhs.reflectivity) &&
                utils::areEqual(transparency, rhs.transparency) &&
                utils::areEqual(refractive_index, rhs.refractive_index);
    }

    // Equality Operator
    bool gfx::Material::operator==(const Material& rhs) const
    {
        return
            *m_texture == rhs.getTexture() &&
            m_properties == rhs.getProperties();
    }

    // Glassy Material Factory Function
    Material createGlassyMaterial()
    {
        return Material{ MaterialProperties
                                 { .transparency = 1,
                                   .refractive_index = 1.5 }
        };
    }

}