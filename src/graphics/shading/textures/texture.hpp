#pragma once

#include <memory>

#include "color.hpp"
#include "vector4.hpp"
#include "texture_map.hpp"

namespace gfx {
    class Texture
    {
    public:
        /* Constructors */

        // Default Constructor
        Texture() = default;

        /* Destructor */

        virtual ~Texture() = default;

        /* Accessors */

        // Maps the object point to texture space and samples the texture at that coordinate
        [[nodiscard]] virtual Color getTextureColorAt(const Vector4& object_point,
                                                      const TextureMap& mapping) const = 0;

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Texture& rhs) const
        { return typeid(*this) == typeid(rhs) && areEquivalent(rhs); }

        /* Object Operations */

        // Creates a copy of this texture and returns a smart pointer to the new object
        [[nodiscard]] virtual std::shared_ptr<Texture> clone() const = 0;

    private:
        /* Helper Methods */

        // Derived-class implemented equality check
        [[nodiscard]] virtual bool areEquivalent(const Texture& other_texture) const = 0;
    };
}
