#pragma once

#include <memory>

#include "matrix4.hpp"
#include "color.hpp"
#include "vector4.hpp"

namespace gfx {
    class Pattern
    {
    public:
        /* Constructors */

        // Default Constructor
        Pattern() = default;

        // Standard Constructor
        explicit Pattern(const Matrix4& transform_matrix)
                : m_transform{ transform_matrix }, m_transform_inverse{ transform_matrix.inverse() }
        {}

        /* Destructor */

        virtual ~Pattern() = default;

        /* Accessors */

        [[nodiscard]] const Matrix4& getTransform() const
        { return m_transform; }


        [[nodiscard]] const Matrix4& getTransformInverse() const
        { return m_transform_inverse; }

        // Returns the color for this pattern at a passed-in point
        [[nodiscard]] virtual Color samplePatternAt(const Vector4& pattern_point) const = 0;

        /* Mutators */

        void setTransform(const Matrix4& transform_matrix)
        {
            m_transform = transform_matrix;
            m_transform_inverse = transform_matrix.inverse();
        }

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Pattern& rhs) const
        { return typeid(*this) == typeid(rhs) && equal(rhs); }

        /* Object Operations */

        // Creates a copy of this pattern and returns a smart pointer to the new object
        [[nodiscard]] virtual std::unique_ptr<Pattern> clone() const = 0;

    private:
        /* Data Members */

        Matrix4 m_transform{ gfx::createIdentityMatrix() };
        Matrix4 m_transform_inverse{ gfx::createIdentityMatrix() };

        /* Helper Methods */

        // Derived-class implemented equality check
        [[nodiscard]] virtual bool equal(const Pattern& other) const = 0;
    };

    // A derived Pattern class to be used in test suites to test the abstract base class functionality
    class TestPattern : public gfx::Pattern
    {
    public:
        TestPattern()
                : Pattern{ }
        {}
        explicit TestPattern(const gfx::Matrix4& transform_matrix)
                : Pattern{ transform_matrix }
        {}

        [[nodiscard]] gfx::Color samplePatternAt(const gfx::Vector4& point) const override
        { return gfx::Color{ point.x(), point.y(), point.z() }; }

        [[nodiscard]] std::unique_ptr<Pattern> clone() const override
        { return std::make_unique<TestPattern>(*this); }

    private:
        [[nodiscard]] bool equal(const Pattern& other) const override
        { return this->getTransform() == other.getTransform(); }
    };
}
