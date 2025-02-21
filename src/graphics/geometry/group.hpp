#pragma once

#include "object.hpp"

namespace gfx {
    class Group : public Object
    {
    public:
        /* Constructors */

        // Default Constructor
        Group() = default;

        // Transform-Only Constructor
        explicit Group(const Matrix4& transform_matrix)
                : Object(transform_matrix), m_children{ }
        {}

        // Object List Constructors
        template<typename... ObjectPtrs>
        explicit Group(const std::shared_ptr<Object>& first_object_ptr,
                       const ObjectPtrs&... remaining_object_ptrs)
                : Object(), m_children { first_object_ptr, remaining_object_ptrs...  }
        { this->setParentForAllChildren(this); }

        template<typename... ObjectRefs>
        explicit Group(const Object& first_object_ref,
                       const ObjectRefs&... remaining_object_refs)
                : Object(), m_children{ }
        { addChildren(first_object_ref, remaining_object_refs...); }

        // Standard Constructors
        template<typename... ObjectPtrs>
        explicit Group(const Matrix4& transform_matrix,
                       const std::shared_ptr<Object>& first_object_ptr,
                       const ObjectPtrs&... remaining_object_ptrs)
                : Object(transform_matrix), m_children { first_object_ptr, remaining_object_ptrs...  }
        { this->setParentForAllChildren(this); }

        template<typename... ObjectRefs>
        explicit Group(const Matrix4& transform_matrix,
                       const Object& first_object_ref,
                       const ObjectRefs&... remaining_object_refs)
                       : Object(transform_matrix), m_children { }
        { addChildren(first_object_ref, remaining_object_refs...); }

        // Copy Constructor
        Group(const Group& src)
                : Object(src.getTransform()), m_children { src.m_children }
        { this->setParentForAllChildren(this); }

        // Move Constructor
        Group(Group&&) = default;

        /* Destructor */

        ~Group() override
        {
            // Unlink the child from the group before object destruction
            this->setParentForAllChildren(nullptr);
        }

        /* Assignment Operators */

        Group& operator=(const Group& rhs)
        {
            this->setTransform(rhs.getTransform());
            m_children = rhs.m_children;
            this->setParentForAllChildren(this);

            return *this;
        }
        Group& operator=(Group&&) = default;

        /* Accessors */

        [[nodiscard]] bool isEmpty() const
        { return m_children.empty(); }

        // Primarily for testing purposes, will perform object slicing if is not cast to the proper derived class
        [[nodiscard]] const Object& getChildAt(const size_t index) const
        { return *m_children.at(index); }

        [[nodiscard]] BoundingBox getBounds() const override
        { return m_bounds; }

        /* Mutators */

        // Adds a single object as a child to the group
        void addChild(const Object& object);
        void addChild(const std::shared_ptr<Object>& object_ptr);

        /* Object Operations */

        // Creates a clone of this group to be stored in an object list
        [[nodiscard]] std::shared_ptr<Object> clone() const override
        { return std::make_shared<Group>(*this); }

    private:
        /* Data Members */
        
        std::vector<std::shared_ptr<Object>> m_children{ };
        BoundingBox m_bounds{ };

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
        void setParentForAllChildren(Group* const parent_ptr) const
        {
            for (const auto& child_ptr : m_children) {
                child_ptr->setParent(parent_ptr);
            }
        }
    };
}
