#pragma once

#include <array>
#include <limits>

#include "vector4.hpp"

namespace gfx {
    class BoundingBox
    {
    public:
        /* Constructors */

        // Default Constructor
        BoundingBox() = default;

        // Float List Constructor
        BoundingBox(const double min_x, const double min_y, const double min_z,
               const double max_x, const double max_y, const double max_z)
                : m_min_extents{ min_x, min_y, min_z }, m_max_extents{ max_x, max_y, max_z }
        {}

        // Extent Coordinates Constructor
        BoundingBox(const Vector4& min_extent_point, const Vector4& max_extent_point)
                : m_min_extents{ min_extent_point.x(), min_extent_point.y(), min_extent_point.z() },
                  m_max_extents{ max_extent_point.x(), max_extent_point.y(), max_extent_point.z() }
        {}

        // Copy Constructor
        BoundingBox(const BoundingBox&) = default;

        /* Destructor */

        ~BoundingBox() = default;

        /* Accessors */

        [[nodiscard]] double getMinX() const
        { return m_min_extents[0]; }

        [[nodiscard]] double getMinY() const
        { return m_min_extents[1]; }

        [[nodiscard]] double getMinZ() const
        { return m_min_extents[2]; }

        [[nodiscard]] double getMaxX() const
        { return m_max_extents[0]; }

        [[nodiscard]] double getMaxY() const
        { return m_max_extents[1]; }

        [[nodiscard]] double getMaxZ() const
        { return m_max_extents[2]; }

        // Returns the point at which the 3 minimum extent bounding planes intersect
        [[nodiscard]] Vector4 getMinExtentPoint() const
        { return Vector4{ m_min_extents[0], m_min_extents[1], m_min_extents[2], 1 }; }

        // Returns the point at which the 3 maximum extent bounding planes intersect
        [[nodiscard]] Vector4 getMaxExtentPoint() const
        { return Vector4{ m_max_extents[0], m_max_extents[1], m_max_extents[2], 1 }; }

        /* Mutators */

        void setMinX(const double min_x)
        { m_min_extents[0] = min_x; }

        void setMinY(const double min_y)
        { m_min_extents[1] = min_y; }

        void setMinZ(const double min_z)
        { m_min_extents[2] = min_z; }

        void setMaxX(const double max_x)
        { m_max_extents[0] = max_x; }

        void setMaxY(const double max_y)
        { m_max_extents[1] = max_y; }

        void setMaxZ(const double max_z)
        { m_max_extents[2] = max_z; }

        void setMinExtent(const double min_x, const double min_y, const double min_z)
        {
            m_min_extents[0] = min_x;
            m_min_extents[1] = min_y;
            m_min_extents[2] = min_z;
        }

        void setMinExtent(const Vector4& coordinate)
        {
            m_min_extents[0] = coordinate.x();
            m_min_extents[1] = coordinate.y();
            m_min_extents[2] = coordinate.z();
        }

        void setMaxExtent(const double max_x, const double max_y, const double max_z)
        {
            m_max_extents[0] = max_x;
            m_max_extents[1] = max_y;
            m_max_extents[2] = max_z;
        }

        void setMaxExtent(const Vector4& coordinate)
        {
            m_max_extents[0] = coordinate.x();
            m_max_extents[1] = coordinate.y();
            m_max_extents[2] = coordinate.z();
        }

        // Adds a point to the bounding box, adjusting the extents if necessary
        void addPoint(const Vector4& point);

        // Merges another bounding box with this box, resizing this box to contain both boxes
        void mergeWithBox(const BoundingBox& target_box);

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const BoundingBox& rhs) const
        { return m_min_extents == rhs.m_min_extents && m_max_extents == rhs.m_max_extents; }

        /* Bounds Checking Operations */

        // Returns true if a point is contained within the extents of the bounding box
        [[nodiscard]] bool containsPoint(const Vector4& point) const;

    private:
        /* Data Members */

        std::array<double, 3> m_min_extents{ std::numeric_limits<double>::infinity(),
                                             std::numeric_limits<double>::infinity(),
                                             std::numeric_limits<double>::infinity() };
        std::array<double, 3> m_max_extents{ -std::numeric_limits<double>::infinity(),
                                             -std::numeric_limits<double>::infinity(),
                                             -std::numeric_limits<double>::infinity() };
    };
}
