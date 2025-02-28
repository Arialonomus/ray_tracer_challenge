#pragma once

#include "procedural_texture.hpp"
#include "color_texture.hpp"

namespace gfx {
    class Pattern : public ProceduralTexture
    {
    public:
        /* Constructors */

        // Default Constructor
        Pattern() = delete;

        // Texture-Only Constructor
        Pattern(const Texture& texture_a, const Texture& texture_b)
                : ProceduralTexture{ },
                  m_texture_a{ texture_a.clone() },
                  m_texture_b{ texture_b.clone() }
        {}

        // Color-Only Constructor
        Pattern(const Color& color_a, const Color& color_b)
                : ProceduralTexture{ },
                  m_texture_a{ ColorTexture{ color_a }.clone() },
                  m_texture_b{ ColorTexture{ color_b }.clone() }
        {}

        // Standard Constructor (Textures)
        Pattern(const Matrix4& transform_matrix, const Texture& texture_a, const Texture& texture_b)
                : ProceduralTexture{ transform_matrix },
                  m_texture_a{ texture_a.clone() },
                  m_texture_b{ texture_b.clone() }
        {}

        // Standard Constructor (Colors)
        Pattern(const Matrix4& transform_matrix, const Color& color_a, const Color& color_b)
                : ProceduralTexture{ transform_matrix },
                  m_texture_a{ ColorTexture{ color_a }.clone() },
                  m_texture_b{ ColorTexture{ color_b }.clone() }
        {}

        /* Destructor */

        ~Pattern() override = default;

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
class TestPatternTex : public gfx::Pattern
{
public:
    TestPatternTex()
            : Pattern{ gfx::white(), gfx::black() }
    {}
    TestPatternTex(const gfx::Texture& texture_a, const gfx::Texture& texture_b)
            : Pattern{ texture_a, texture_b }
    {}
    TestPatternTex(const gfx::Color& color_a, const gfx::Color& color_b)
            : Pattern{ color_a, color_b }
    {}
    TestPatternTex(const gfx::Matrix4& transform_matrix, const gfx::Texture& texture_a, const gfx::Texture& texture_b)
            : Pattern{ transform_matrix, texture_a, texture_b }
    {}
    TestPatternTex(const gfx::Matrix4& transform_matrix, const gfx::Color& color_a, const gfx::Color& color_b)
            : Pattern{ transform_matrix, color_a, color_b }
    {}

    ~TestPatternTex() override = default;

    [[nodiscard]] std::shared_ptr<Texture> clone() const override
    { return std::make_shared<TestPatternTex>(*this); }

private:
    [[nodiscard]] gfx::Color sample3DTextureAt(const gfx::Vector4& transformed_point,
                                               const gfx::TextureMap& mapping) const override
    { return { transformed_point.x(), transformed_point.y(), transformed_point.z() }; }

    [[nodiscard]] bool areEquivalent(const Texture& other_texture) const override
    {
        const TestPatternTex& other_test_pattern{ dynamic_cast<const TestPatternTex&>(other_texture) };
        return this->getTransform() == other_test_pattern.getTransform() &&
               this->getTextureA() == other_test_pattern.getTextureA() &&
               this->getTextureB() == other_test_pattern.getTextureB();
    }
};