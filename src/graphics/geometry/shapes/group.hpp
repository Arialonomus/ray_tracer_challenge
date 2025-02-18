#pragma once

#include "shape.hpp"

namespace gfx {
    class Group : public Shape
    {
    public:
        /* Constructors */

        // Default Constructor
        Group() = default;

        // Standard Constructors
        template<typename... ShapePtrs>
        explicit Group(const std::shared_ptr<Shape>& first_shape,
                       const ShapePtrs&... remaining_shapes)
                : m_children { first_shape, remaining_shapes...  }
        {}

        template<typename... ShapeRefs>
        explicit Group(const Shape& first_shape,
                       const ShapeRefs&... remaining_shapes)
        { addChildren(first_shape, remaining_shapes...); }

        // Copy Constructor
        Group(const Group&) = default;

        // Move Constructor
        Group(Group&&) = default;

        /* Destructor */

        ~Group() override = default;

        /* Assignment Operators */

        Group& operator=(const Group&) = default;
        Group& operator=(Group&&) = default;

        /* Accessors */

        [[nodiscard]] bool isEmpty() const
        { return m_children.empty(); }

        [[nodiscard]] unsigned int getNumChildren() const;

        /* Mutators */

        // Adds a single shape as a child to the group
        void addChild(const Shape& shape);
        void addChild(const std::shared_ptr<Shape>& shape);

        /* Object Operations */

        // Creates a clone of this sphere to be stored in an object list
        [[nodiscard]] std::shared_ptr<Shape> clone() const override
        { return std::make_shared<Group>(*this); }

    private:
        /* Data Members */
        
        std::vector<std::shared_ptr<Shape>> m_children{ };

        /* Shape Helper Method Overrides */

        [[nodiscard]] Vector4 calculateSurfaceNormal(const Vector4& transformed_point) const override;
        [[nodiscard]] std::vector<Intersection> calculateIntersections(const Ray& transformed_ray) const override;
        [[nodiscard]] bool areEquivalent(const Shape& other_shape) const override;

        /* Helper Methods */

        // Add multiple shapes passed in as references to the group
        template<typename... ShapeRefs>
        void addChildren(const Shape& first_object, const ShapeRefs&... remaining_objects) {
            this->addChild(first_object);
            addChildren(remaining_objects...);
        }
        void addChildren() {}    // Base case for recursion

        // Recursively calculate the number of children in a group
        [[nodiscard]] unsigned int getNumChildren(const Group& parent) const;
    };
}
