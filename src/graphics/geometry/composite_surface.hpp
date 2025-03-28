#pragma once

#include "object.hpp"

#include "material.hpp"

namespace gfx {
    class CompositeSurface : public Object
    {
    public:
        /* Constructors */

        // Default Constructor
        CompositeSurface() = default;

        // Transform-Only Constructor
        explicit CompositeSurface(const Matrix4& transform_matrix)
                : Object(transform_matrix), m_children{ }, m_material{ std::nullopt }, m_bounds{ }
        {}

        // Object List Constructors
        template<typename... ObjectPtrs>
        explicit CompositeSurface(const std::shared_ptr<Object>& first_object_ptr,
                                  const ObjectPtrs&... remaining_object_ptrs)
                : Object(),
                  m_children { first_object_ptr, remaining_object_ptrs... },
                  m_material{ std::nullopt },
                  m_bounds(this->calculateBounds())
        {
            this->setParentForAllChildren(this);
        }

        template<typename... ObjectRefs>
        explicit CompositeSurface(const Object& first_object_ref,
                                  const ObjectRefs&... remaining_object_refs)
                : Object(), m_children{ }, m_material{ std::nullopt }, m_bounds{ }
        {
            addChildren(first_object_ref, remaining_object_refs...);
            m_bounds = this->calculateBounds();
        }

        // Standard Constructors
        template<typename... ObjectPtrs>
        explicit CompositeSurface(const Matrix4& transform_matrix,
                                  const std::shared_ptr<Object>& first_object_ptr,
                                  const ObjectPtrs&... remaining_object_ptrs)
                : Object(transform_matrix),
                  m_children { first_object_ptr, remaining_object_ptrs...  },
                  m_bounds{ this->calculateBounds() }
        { this->setParentForAllChildren(this); }

        template<typename... ObjectRefs>
        explicit CompositeSurface(const Matrix4& transform_matrix,
                                  const Object& first_object_ref,
                                  const ObjectRefs&... remaining_object_refs)
                       : Object(transform_matrix), m_children { }, m_bounds{ }
        {
            addChildren(first_object_ref, remaining_object_refs...);
            m_bounds = this->calculateBounds();
        }

        // Copy Constructor
        CompositeSurface(const CompositeSurface& src)
                : Object(src.getTransform()),
                  m_children { src.m_children },
                  m_material{ src.m_material },
                  m_bounds{ src.m_bounds }
        { this->setParentForAllChildren(this); }

        // Move Constructor
        CompositeSurface(CompositeSurface&& src) noexcept
                : Object(src.getTransform()),
                  m_children { std::move(src.m_children) },
                  m_material{ std::move(src.m_material) },
                  m_bounds{ src.m_bounds }
        { this->setParentForAllChildren(this); }

        /* Destructor */

        ~CompositeSurface() override
        {
            // Unlink the child from the group before object destruction
            this->setParentForAllChildren(nullptr);
        }

        /* Assignment Operators */

        CompositeSurface& operator=(const CompositeSurface& rhs);
        CompositeSurface& operator=(CompositeSurface&& rhs) noexcept;

        /* Accessors */

        [[nodiscard]] bool isEmpty() const
        { return m_children.empty(); }

        // Primarily for testing purposes, will perform object slicing if is not cast to the proper derived class
        [[nodiscard]] const Object& getChildAt(const size_t index) const
        { return *m_children.at(index); }

        [[nodiscard]] bool hasMaterial() const
        { return (this->hasParent() && this->getParent()->hasMaterial()) || m_material.has_value(); }

        [[nodiscard]] const Material& getMaterial() const
        { return (this->hasParent() && this->getParent()->hasMaterial()) ? this->getParent()->getMaterial() : m_material.value(); }

        [[nodiscard]] BoundingBox getBounds() const override
        { return m_bounds; }

        /* Mutators */

        // Adds a single object as a child to the group
        void addChild(const Object& object);
        void addChild(const std::shared_ptr<Object>& object_ptr);

        // Add a material to apply to all child objects in this composite surface
        void addMaterial(const Material& material)
        { m_material = material; }

        // Allows child objects to be drawn with their own material
        void removeMaterial()
        { m_material = std::nullopt; }

        /* Object Operations */

        // Creates a clone of this group to be stored in an object list
        [[nodiscard]] std::shared_ptr<Object> clone() const override
        { return std::make_shared<CompositeSurface>(*this); }

    private:
        /* Data Members */
        
        std::vector<std::shared_ptr<Object>> m_children{ };
        BoundingBox m_bounds{ };
        std::optional<Material> m_material{ std::nullopt };

        /* Object Helper Method Overrides */

        [[nodiscard]] std::vector<Intersection> calculateIntersections(const Ray& transformed_ray) const override;
        [[nodiscard]] bool areEquivalent(const Object& other_object) const override;

        /* Helper Methods */

        // Add multiple objects passed in as references to the group
        template<typename... ObjectRefs>
        void addChildren(const Object& first_object_ref, const ObjectRefs&... remaining_object_refs) {
            this->addChild(first_object_ref);
            addChildren(remaining_object_refs...);
        }
        void addChildren() {}    // Base case for recursion

        // Sets the parent pointer for all children in the group
        void setParentForAllChildren(CompositeSurface* parent_ptr) const;

        // Calculates the extents of a bounding box enclosing the bounding boxes of each child
        [[nodiscard]] BoundingBox calculateBounds() const;
    };
}
