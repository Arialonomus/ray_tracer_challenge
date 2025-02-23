#include "composite_surface.hpp"

#include <algorithm>

#include "intersection.hpp"

namespace gfx {
    // Object Inserter (from object ref)
    void CompositeSurface::addChild(const Object& object)
    {
        auto cloned_object_ptr{ object.clone() };
        cloned_object_ptr->setParent(this);
        m_children.push_back(cloned_object_ptr);
        m_bounds.mergeWithBox(cloned_object_ptr->getLocalSpaceBounds());
    }

    // Copy Assignment Operator
    CompositeSurface& CompositeSurface::operator=(const CompositeSurface& rhs)
    {
        this->setTransform(rhs.getTransform());
        m_children = rhs.m_children;
        this->setParentForAllChildren(this);
        m_bounds = rhs.m_bounds;
        m_material = rhs.m_material;

        return *this;
    }

    // Move Assignment Operator
    CompositeSurface& CompositeSurface::operator=(CompositeSurface&& rhs) noexcept
    {
        this->setTransform(rhs.getTransform());
        m_children = std::move(rhs.m_children);
        this->setParentForAllChildren(this);
        m_bounds = rhs.m_bounds;
        m_material = std::move(rhs.m_material);

        return *this;
    }

    // Object Inserter (from pointer)
    void CompositeSurface::addChild(const std::shared_ptr<Object>& object_ptr)
    {
        object_ptr->setParent(this);
        m_children.push_back(object_ptr);
        m_bounds.mergeWithBox(object_ptr->getLocalSpaceBounds());
    }

    // Intersections with Child Object(s) in a Composite Surface
    std::vector<Intersection> CompositeSurface::calculateIntersections(const Ray& transformed_ray) const
    {
        // Check if ray intersects bounding box
        std::vector<Intersection> intersections{ };
        if (!m_bounds.isIntersectedBy(transformed_ray))
            return intersections;

        // Aggregate intersections across all children
        for (const auto& object_ptr : m_children) {
            intersections.append_range(object_ptr->getObjectIntersections(transformed_ray));
        }

        std::sort(intersections.begin(), intersections.end());
        return intersections;
    }

    // Composite Surface Object Equivalency Check
    bool CompositeSurface::areEquivalent(const Object& other_object) const
    {
        const CompositeSurface& other_group{ dynamic_cast<const CompositeSurface&>(other_object) };

        // Ensure the number of children in the next layer match for each object
        const size_t num_children{ this->m_children.size() };
        if (num_children != other_group.m_children.size())
            return false;

        // Compare each child object in tree
        for (int i = 0; i < num_children; ++i) {
            if (*this->m_children[i] != *other_group.m_children[i])
                return false;
        }
        return true;
    }

    // Parent Setter Helper Method
    void CompositeSurface::setParentForAllChildren(CompositeSurface* const parent_ptr) const
    {
        for (const auto& child_ptr : m_children) {
            child_ptr->setParent(parent_ptr);
        }
    }

    // Composite Surface Bounding Volume Calculator
    BoundingBox CompositeSurface::calculateBounds() const
    {
        BoundingBox new_enclosing_volume{ };

        for (const auto& child_ptr : m_children) {
            new_enclosing_volume.mergeWithBox(child_ptr->getLocalSpaceBounds());
        }
        return new_enclosing_volume;
    }
}