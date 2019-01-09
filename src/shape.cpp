#include "shape.h"
#include <math.h>

#if BIGROCK_VEC3_TYPE_ENUM == BIGROCK_LONG_DOUBLE_ENUM
#define _sqrt sqrtl
#define _pow powl
#elif BIGROCK_VEC3_TYPE_ENUM == BIGROCK_DOUBLE_ENUM
#define _sqrt sqrt
#define _pow pow
#else
#define _sqrt sqrtf
#define _pow powf
#endif

namespace bigrock
{
    #pragma region Shape

    bool Shape::interacts_with_shape(const Shape &other) const
    {
        Vector3 closest = this->get_closest_point(other.position);
        return other.point_intersects(closest);
    }

    #pragma endregion

    #pragma region Rectangle

    bool Rectangle::point_intersects(const Vector3 &point) const
    {
        Vector3 bounds = position + size;
        return point.x >= position.x && point.y >= position.y && point.z >= position.z && point.x <= bounds.x && point.y <= bounds.y && point.z <= bounds.z;
    }

    Vector3 Rectangle::get_closest_point(const Vector3 &other) const
    {
        Vector3 point;
        Vector3 bottom_left = this->get_bottom_left();
        Vector3 bounds = this->get_bounds();
        Vector3 top_right = bottom_left + bounds;
        for(int i = 0; i < 3; i++)
        {
            if(other.coords[i] <= bottom_left.coords[i])
                point.coords[i] = bottom_left.coords[i];
            else if(other.coords[i] >= top_right.coords[i])
                point.coords[i] = top_right.coords[i];
            else
            {
                point.coords[i] = other.coords[i];
            }
        }
        return point;
    }

    #pragma endregion
}