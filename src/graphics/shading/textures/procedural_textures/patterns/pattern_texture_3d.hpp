#pragma once

#include "texture_3d.hpp"
#include "color_texture.hpp"

namespace gfx {
    class PatternTexture3D : public Texture3D
    {
    public:
        /* Constructors */

        // Default Constructor
        PatternTexture3D() = delete;

        // Texture-Only Constructor
        PatternTexture3D(const Texture& texture_a, const Texture& texture_b)
                : Texture3D{ },
                  m_texture_a{ texture_a.clone() },
                  m_texture_b{ texture_b.clone() }
        {}

        // Color-Only Constructor
        PatternTexture3D(const Color& color_a, const Color& color_b)
                : Texture3D{ },
                  m_texture_a{ ColorTexture{ color_a }.clone() },
                  m_texture_b{ ColorTexture{ color_b }.clone() }
        {}

        // Standard Constructor (Textures)
        PatternTexture3D(const Matrix4& transform_matrix, const Texture& texture_a, const Texture& texture_b)
                : Texture3D{ transform_matrix },
                  m_texture_a{ texture_a.clone() },
                  m_texture_b{ texture_b.clone() }
        {}

        // Standard Constructor (Colors)
        PatternTexture3D(const Matrix4& transform_matrix, const Color& color_a, const Color& color_b)
                : Texture3D{ transform_matrix },
                  m_texture_a{ ColorTexture{ color_a }.clone() },
                  m_texture_b{ ColorTexture{ color_b }.clone() }
        {}

        /* Destructor */

        ~PatternTexture3D() override = default;

        /* Accessors */

        [[nodiscard]] const Texture& getTextureA() const
        { return *m_texture_a; }

        [[nodiscard]] const Texture& getTextureB() const
        { return *m_texture_b; }

    private:
        /* Data Members */

        std::shared_ptr<Texture> m_texture_a{ };
        std::shared_ptr<Texture> m_texture_b{ };
    };
}

// Concrete pattern implementation used in some test suites to test base class features
class TestPattern3D : public gfx::PatternTexture3D
{
public:
    TestPattern3D()
            : PatternTexture3D{ gfx::white(), gfx::black() }
    {}
    TestPattern3D(const gfx::Texture& texture_a, const gfx::Texture& texture_b)
            : PatternTexture3D{ texture_a, texture_b }
    {}
    TestPattern3D(const gfx::Color& color_a, const gfx::Color& color_b)
            : PatternTexture3D{ color_a, color_b }
    {}
    TestPattern3D(const gfx::Matrix4& transform_matrix, const gfx::Texture& texture_a, const gfx::Texture& texture_b)
            : PatternTexture3D{ transform_matrix, texture_a, texture_b }
    {}
    TestPattern3D(const gfx::Matrix4& transform_matrix, const gfx::Color& color_a, const gfx::Color& color_b)
            : PatternTexture3D{ transform_matrix, color_a, color_b }
    {}

    ~TestPattern3D() override = default;

    [[nodiscard]] std::shared_ptr<Texture> clone() const override
    { return std::make_shared<TestPattern3D>(*this); }

private:
    [[nodiscard]] gfx::Color sample3DTextureAt(const gfx::Vector4& transformed_point,
                                               const gfx::TextureMap& mapping) const override
    { return { transformed_point.x(), transformed_point.y(), transformed_point.z() }; }

    [[nodiscard]] bool areEquivalent(const Texture& other_texture) const override
    {
        const TestPattern3D& other_test_pattern{ dynamic_cast<const TestPattern3D&>(other_texture) };
        return this->getTransform() == other_test_pattern.getTransform() &&
               this->getTextureA() == other_test_pattern.getTextureA() &&
               this->getTextureB() == other_test_pattern.getTextureB();
    }
};