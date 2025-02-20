#include "group.hpp"

#include "intersection.hpp"

namespace gfx {
    // Object Inserter (from object ref)
    void Group::addChild(const Object& object)
    {
        auto cloned_object_ptr{ object.clone() };
        cloned_object_ptr->setParent(this);
        m_children.push_back(cloned_object_ptr);
    }

    // Object Inserter (from pointer)
    void Group::addChild(const std::shared_ptr<Object>& object_ptr)
    {
        object_ptr->setParent(this);
        m_children.push_back(object_ptr);
    }

    // Caller Method for Recursion
    unsigned int Group::getNumChildren() const
    {
        return getNumChildren(*this);
    }

    // Recursive Children Counter Method
    unsigned int Group::getNumChildren(const Group& parent) const
    {
        // Base Case
        if (parent.isEmpty()) {
            return 0;
        }

        // Recursive Case, Count Children
        unsigned int num_children{ 0 };
        for (const auto& child_ptr : m_children) {
            const auto child_group_ptr{ std::dynamic_pointer_cast<Group>(child_ptr) };
            if (child_group_ptr) {
                num_children += 1 + getNumChildren(*child_group_ptr);
            }
        }

        return num_children;
    }

    // Surface Normal for a Child Object in a Group
    Vector4 Group::calculateSurfaceNormal(const Vector4& transformed_point) const
    {
        return Vector4{ };
    }

    // Intersections with Child Object(s) in a Group
    std::vector<Intersection> Group::calculateIntersections(const Ray& transformed_ray) const
    {
        return std::vector<Intersection>{ };
    }

    // Group Object Equivalency Check
    bool Group::areEquivalent(const Object& other_object) const
    {
        const Group& other_group{ dynamic_cast<const Group&>(other_object) };

        // Ensure the number of children in the next layer match for each object
        const size_t num_children{ this->m_children.size() };
        if (num_children != other_group.m_children.size()) {
            return false;
        }

        // Compare each child object in tree
        for (int i = 0; i < num_children; ++i) {
            if (*this->m_children[i] != *other_group.m_children[i]) {
                return false;
            }
        }

        return true;
    }
}