#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-copy-initialization"

#include "gtest/gtest.h"
#include "pattern.hpp"

#include "matrix3.hpp"
#include "transform.hpp"
#include "color.hpp"

#include "stripe_pattern.hpp"
#include "ring_pattern.hpp"
#include "checkered_pattern.hpp"

class TestPatternTex : public gfx::Pattern
{
public:
    TestPatternTex() = delete;
    TestPatternTex(const gfx::Texture& texture_a, const gfx::Texture& texture_b)
            : Pattern{ texture_a, texture_b }
    {}
    TestPatternTex(const gfx::Color& color_a, const gfx::Color& color_b)
            : Pattern{ color_a, color_b }
    {}
    TestPatternTex(const gfx::Matrix3& transform_matrix, const gfx::Texture& texture_a, const gfx::Texture& texture_b)
            : Pattern{ transform_matrix, texture_a, texture_b }
    {}
    TestPatternTex(const gfx::Matrix3& transform_matrix, const gfx::Color& color_a, const gfx::Color& color_b)
            : Pattern{ transform_matrix, color_a, color_b }
    {}
    
    ~TestPatternTex() override = default;

    [[nodiscard]] std::shared_ptr<Texture> clone() const override
    { return std::make_shared<TestPatternTex>(*this); }

private:
    [[nodiscard]] gfx::Color sampleTextureAt(const gfx::Vector3& transformed_uv) const override
    { return gfx::Color{ }; }

    [[nodiscard]] bool areEquivalent(const Texture& other_texture) const override
    {
        const TestPatternTex& other_test_pattern{ dynamic_cast<const TestPatternTex&>(other_texture) };
        return this->getTransform() == other_test_pattern.getTransform() &&
               this->getTextureA() == other_test_pattern.getTextureA() &&
               this->getTextureB() == other_test_pattern.getTextureB();
    }
};

// Tests the texture-only constructor for the abstract pattern class
TEST(GraphicsPatternTexture, TextureOnlyConstructor)
{
    const gfx::Matrix3 transform_expected{ };
    const gfx::StripePattern texture_a_expected{ gfx::create2DRotationMatrix(M_PI_4),
                                                    gfx::white(),
                                                    gfx::black() };
    const gfx::StripePattern texture_b_expected{ gfx::create2DRotationMatrix(M_PI_4),
                                                    gfx::cyan(),
                                                    gfx::magenta() };
    const TestPatternTex test_pattern{ texture_a_expected,
                                           texture_b_expected };

    ASSERT_EQ(test_pattern.getTransform(), transform_expected);
    ASSERT_EQ(test_pattern.getTextureA(), texture_a_expected);
    ASSERT_EQ(test_pattern.getTextureB(), texture_b_expected);
}

// Tests the color-only constructor for the abstract pattern class
TEST(GraphicsPatternTexture, ColorOnlyConstructor)
{
    const gfx::Matrix3 transform_expected{ };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const TestPatternTex test_pattern{ color_a_expected, color_b_expected };

    ASSERT_EQ(test_pattern.getTransform(), transform_expected);
    
    const gfx::Vector3 test_point{ gfx::create2DPoint(0, 0) };
    ASSERT_EQ(test_pattern.getTextureA().getTextureColorAt(test_point), color_a_expected);
    ASSERT_EQ(test_pattern.getTextureB().getTextureColorAt(test_point), color_b_expected);
}

// Tests the standard constructors for the two-tone pattern class
TEST(GraphicsPatternTexture, StandardConstructors)
{
    const gfx::Matrix3 transform_expected{ gfx::create2DTranslationMatrix(1, 3) };
    const gfx::StripePattern texture_a_expected{ gfx::create2DRotationMatrix(M_PI_4),
                                                    gfx::white(),
                                                    gfx::black() };
    const gfx::StripePattern texture_b_expected{ gfx::create2DRotationMatrix(M_PI_4),
                                                    gfx::cyan(),
                                                    gfx::magenta() };

    // Test the texture argument standard constructor
    const TestPatternTex test_pattern_textures{ transform_expected,
                                                texture_a_expected,
                                                texture_b_expected };

    ASSERT_EQ(test_pattern_textures.getTransform(), transform_expected);
    ASSERT_EQ(test_pattern_textures.getTextureA(), texture_a_expected);
    ASSERT_EQ(test_pattern_textures.getTextureB(), texture_b_expected);

    // Test the color argument standard constructor
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const TestPatternTex test_pattern_colors{ transform_expected,
                                              color_a_expected,
                                              color_b_expected };

    const gfx::Vector3 test_point{ gfx::create2DPoint(0, 0) };
    ASSERT_EQ(test_pattern_colors.getTransform(), transform_expected);
    ASSERT_EQ(test_pattern_colors.getTextureA().getTextureColorAt(test_point), color_a_expected);
    ASSERT_EQ(test_pattern_colors.getTextureB().getTextureColorAt(test_point), color_b_expected);
}

// Tests the copy constructor for the two-tone pattern class
TEST(GraphicsPatternTexture, CopyConstructor)
{
    const gfx::Matrix3 transform_expected{ gfx::create2DTranslationMatrix(1, 3) };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const TestPatternTex test_pattern_src{ transform_expected,
                                                   color_a_expected,
                                                   color_b_expected };
    const TestPatternTex test_pattern_cpy{ test_pattern_src };

    ASSERT_EQ(test_pattern_cpy.getTransform(), transform_expected);
}

/* Stripe Pattern Derived Class Tests */

// Tests the equality operator for stripe patterns
TEST(GraphicsPatternTexture, StripePatternEqualityOperator)
{
    const gfx::Matrix3 transform_expected{ gfx::create2DTranslationMatrix(1, 3) };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const gfx::StripePattern stripe_pattern_src{ transform_expected,
                                                 color_a_expected,
                                                 color_b_expected };
    const gfx::StripePattern stripe_pattern_cpy{ stripe_pattern_src };

    ASSERT_TRUE(stripe_pattern_src == stripe_pattern_cpy);
}

// Tests that the default stripe pattern returns the correct color in each dimension
TEST(GraphicsPatternTexture, StripePatternGetTextureColorAt)
{
    const gfx::StripePattern stripe_pattern{ gfx::white(), gfx::black() };

    // Test that a stripe pattern is constant in the v-dimension
    EXPECT_EQ(stripe_pattern.getTextureColorAt(gfx::create2DPoint(0, 0)), gfx::white());
    EXPECT_EQ(stripe_pattern.getTextureColorAt(gfx::create2DPoint(0, 1)), gfx::white());
    EXPECT_EQ(stripe_pattern.getTextureColorAt(gfx::create2DPoint(0, 2)), gfx::white());

    // Test that a stripe pattern alternates in the u-dimension
    EXPECT_EQ(stripe_pattern.getTextureColorAt(gfx::create2DPoint(0, 0)), gfx::white());
    EXPECT_EQ(stripe_pattern.getTextureColorAt(gfx::create2DPoint(0.9, 0)), gfx::white());
    EXPECT_EQ(stripe_pattern.getTextureColorAt(gfx::create2DPoint(1, 0)), gfx::black());
    EXPECT_EQ(stripe_pattern.getTextureColorAt(gfx::create2DPoint(-0.1, 0)), gfx::black());
    EXPECT_EQ(stripe_pattern.getTextureColorAt(gfx::create2DPoint(-1, 0)), gfx::black());
    ASSERT_EQ(stripe_pattern.getTextureColorAt(gfx::create2DPoint(-1.1, 0)), gfx::white());
}

/* Ring Pattern Derived Class Tests */

// Tests the equality operator for ring patterns
TEST(GraphicsPatternTexture, RingPatternEqualityOperator)
{
    const gfx::Matrix3 transform_expected{ gfx::create2DTranslationMatrix(1, 3) };
    const gfx::StripePattern texture_a_expected{ gfx::create2DRotationMatrix(M_PI_4),
                                                    gfx::white(),
                                                    gfx::black() };
    const gfx::StripePattern texture_b_expected{ gfx::create2DRotationMatrix(M_PI_4),
                                                    gfx::cyan(),
                                                    gfx::magenta() };
    const gfx::RingPattern ring_pattern_src{ transform_expected,
                                             texture_a_expected,
                                             texture_b_expected };
    const gfx::RingPattern ring_pattern_cpy{ ring_pattern_src };

    ASSERT_TRUE(ring_pattern_src == ring_pattern_cpy);
}

// Tests that the default ring pattern returns the correct color when sampled
TEST(GraphicsPatternTexture, RingPatternGetTextureColorAt)
{
    const gfx::RingPattern ring_pattern{ gfx::white(), gfx::black() };

    const gfx::Color color_a_actual{ ring_pattern.getTextureColorAt(gfx::create2DPoint(0, 0)) };
    EXPECT_EQ(color_a_actual, gfx::white());

    const gfx::Color color_b_actual{ ring_pattern.getTextureColorAt(gfx::create2DPoint(1, 0)) };
    EXPECT_EQ(color_b_actual, gfx::black());

    const gfx::Color color_c_actual{ ring_pattern.getTextureColorAt(gfx::create2DPoint(0, 1)) };
    EXPECT_EQ(color_c_actual, gfx::black());

    const gfx::Color color_d_actual{ ring_pattern.getTextureColorAt(gfx::create2DPoint(0.708, 0.708)) };
    EXPECT_EQ(color_d_actual, gfx::black());
}

/* Checkered Pattern Derived Class Tests */

// Tests the equality operator for ring patterns
TEST(GraphicsPatternTexture, CheckeredPatternEqualityOperator)
{
    const gfx::Matrix3 transform_expected{ gfx::create2DTranslationMatrix(1, 3) };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const gfx::CheckeredPattern checkered_pattern_src{ transform_expected,
                                                       color_a_expected,
                                                       color_b_expected };
    const gfx::CheckeredPattern checkered_pattern_cpy{ checkered_pattern_src };

    ASSERT_TRUE(checkered_pattern_src == checkered_pattern_cpy);
}

// Tests that the checkered ring pattern repeats in each dimension
TEST(GraphicsPatternTexture, CheckeredPatternGetTextureColorAt)
{
    const gfx::CheckeredPattern checkered_pattern{ gfx::white(), gfx::black() };

    // Test that checkers repeat in the u-dimension
    const gfx::Color color_x_a_actual{ checkered_pattern.getTextureColorAt(gfx::create2DPoint(0, 0)) };
    EXPECT_EQ(color_x_a_actual, gfx::white());
    const gfx::Color color_x_b_actual{ checkered_pattern.getTextureColorAt(gfx::create2DPoint(0.99, 0)) };
    EXPECT_EQ(color_x_b_actual, gfx::white());
    const gfx::Color color_x_c_actual{ checkered_pattern.getTextureColorAt(gfx::create2DPoint(1.01, 0)) };
    EXPECT_EQ(color_x_c_actual, gfx::black());

    // Test that checkers repeat in the v-dimension
    const gfx::Color color_z_a_actual{ checkered_pattern.getTextureColorAt(gfx::create2DPoint(0, 0)) };
    EXPECT_EQ(color_z_a_actual, gfx::white());
    const gfx::Color color_z_b_actual{ checkered_pattern.getTextureColorAt(gfx::create2DPoint(0, 0.99)) };
    EXPECT_EQ(color_z_b_actual, gfx::white());
    const gfx::Color color_z_c_actual{ checkered_pattern.getTextureColorAt(gfx::create2DPoint(0, 1.01)) };
    EXPECT_EQ(color_z_c_actual, gfx::black());
}

#pragma clang diagnostic pop