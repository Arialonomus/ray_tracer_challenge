#include "bounding_box.hpp"

#include "util_functions.hpp"
#include "intersection.hpp"

namespace gfx {
    void BoundingBox::addPoint(const Vector4& point)
    {
        // X-Values
        if (utils::isLess(point.x(), m_min_extents[0]))
            m_min_extents[0] = point.x();
        if (utils::isGreater(point.x(), m_max_extents[0]))
            m_max_extents[0] = point.x();

        // Y-Values
        if (utils::isLess(point.y(), m_min_extents[1]))
            m_min_extents[1] = point.y();
        if (utils::isGreater(point.y(), m_max_extents[1]))
            m_max_extents[1] = point.y();

        // Z-Values
        if (utils::isLess(point.z(), m_min_extents[2]))
            m_min_extents[2] = point.z();
        if (utils::isGreater(point.z(), m_max_extents[2]))
            m_max_extents[2] = point.z();
    }

    void BoundingBox::mergeWithBox(const BoundingBox& target_box)
    {
        this->addPoint(target_box.getMinExtentPoint());
        this->addPoint(target_box.getMaxExtentPoint());
    }

    bool BoundingBox::containsPoint(const Vector4& point) const
    {
        return
                utils::isLessOrEqual(point.x(), m_max_extents[0]) &&
                utils::isGreaterOrEqual(point.x(), m_min_extents[0]) &&
                utils::isLessOrEqual(point.y(), m_max_extents[1]) &&
                utils::isGreaterOrEqual(point.y(), m_min_extents[1]) &&
                utils::isLessOrEqual(point.z(), m_max_extents[2]) &&
                utils::isGreaterOrEqual(point.z(), m_min_extents[2]);
    }

    bool BoundingBox::containsBox(const BoundingBox& box) const
    {
        return this->containsPoint(box.getMinExtentPoint()) && this->containsPoint(box.getMaxExtentPoint());
    }


    bool BoundingBox::isIntersectedBy(const Ray& ray) const
    {
        const auto [ t_min, t_max ] { calculateBoxIntersectionTs(ray,
                                                                 this->getMinExtentPoint(),
                                                                 this->getMaxExtentPoint()) };

        return utils::isLessOrEqual(t_min, t_max);
    }

    BoundingBox BoundingBox::transform(const Matrix4& transform_matrix) const
    {
        std::array<Vector4, 8> bounding_volume_vertices {
            this->getMinExtentPoint(),
            createPoint(this->getMinX(), this->getMinY(), this->getMaxZ()),
            createPoint(this->getMinX(), this->getMaxY(), this->getMinZ()),
            createPoint(this->getMinX(), this->getMaxY(), this->getMaxZ()),
            createPoint(this->getMaxX(), this->getMinY(), this->getMinZ()),
            createPoint(this->getMaxX(), this->getMinY(), this->getMaxZ()),
            createPoint(this->getMaxX(), this->getMaxY(), this->getMinZ()),
            this->getMaxExtentPoint()
        };

        BoundingBox new_enclosing_volume{ };

        for (const auto vertex : bounding_volume_vertices) {
            new_enclosing_volume.addPoint(transform_matrix * vertex);
        }

        return new_enclosing_volume;
    }
}