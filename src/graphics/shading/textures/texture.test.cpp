#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-copy-initialization"

#include "gtest/gtest.h"
#include "texture.hpp"

#include "matrix3.hpp"
#include "color.hpp"
#include "vector3.hpp"
#include "transform.hpp"

class TestTexture : public gfx::Texture
{
public:
    TestTexture()
            : Texture{ }
    {}
    explicit TestTexture(const gfx::Matrix3& transform_matrix)
            : Texture{ transform_matrix }
    {}

    [[nodiscard]] std::shared_ptr<Texture> clone() const override
    { return std::make_shared<TestTexture>(*this); }

private:
    [[nodiscard]] gfx::Color sampleTextureAt(const gfx::Vector3& transformed_uv) const override
    { return gfx::Color{ transformed_uv.x(), transformed_uv.y(), 1 }; }

    [[nodiscard]] bool areEquivalent(const Texture& other_texture) const override
    {
        const TestTexture& other_test_texture{ dynamic_cast<const TestTexture&>(other_texture) };
        return this->getTransform() == other_test_texture.getTransform();
    }
};

// Tests the default constructor for the base texture class
TEST(GraphicsTexture, BaseClassDefaultConstructor)
{
    const TestTexture texture{ };
    const gfx::Matrix3 transform_expected{ };

    ASSERT_EQ(texture.getTransform(), transform_expected);
}

// Tests the standard constructor for the base texture class
TEST(GraphicsTexture, BaseClassStandardConstructor)
{
    const gfx::Matrix3 transform_expected{ gfx::create2DTranslationMatrix(1, 2) };
    const TestTexture texture{ transform_expected };

    ASSERT_EQ(texture.getTransform(), transform_expected);
}

// Tests the copy constructor for the base texture class
TEST(GraphicsTexture, BaseClassCopyConstructor)
{
    const gfx::Matrix3 transform_expected{ gfx::create2DTranslationMatrix(1, 2) };
    const TestTexture texture_src{ transform_expected };
    const TestTexture texture_cpy{ texture_src };

    ASSERT_EQ(texture_cpy.getTransform(), transform_expected);
}

#pragma clang diagnostic pop