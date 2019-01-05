#include "shape.h"
#include <math.h>

#if BIGROCK_VEC3_TYPE == float
#define _sqrt sqrtf
#define _pow powf
#elif BIGROCK_VEC3_TYPE == long double
#define _sqrt sqrtl
#define _pow powl
#else
#define _sqrt sqrt
#define _pow pow
#endif

namespace bigrock
{
    #pragma region shape

    bool Shape::interacts_with_shape(const Shape &other) const
    {
        Vector3 closest = this->get_closest_point(other.position);
        return other.point_intersects(closest);
    }

    #pragma endregion

    #pragma region Sphere

    bool Sphere::point_intersects(const Vector3 &point) const
    {
        BIGROCK_VEC3_TYPE distance_sqr = position.distance_squared_to(point);
        return distance_sqr <= (radius * radius);
    }

    inline Vector3 Sphere::get_bounds() const
    {
        return Vector3(radius * 2, radius * 2, radius * 2);
    }

    inline Vector3 Sphere::get_bottom_left() const
    {
        return position - Vector3(radius, radius, radius);
    }

    Vector3 Sphere::get_closest_point(const Vector3 &other) const
    {
        return position + ((other - position).normalized() * radius);
    }

    #pragma endregion

    #pragma region Rectangle

    bool Rectangle::point_intersects(const Vector3 &point) const
    {
        Vector3 bounds = position + size;
        return point.x >= position.x && point.y >= position.y && point.z >= position.z && point.x <= bounds.x && point.y <= bounds.y && point.z <= bounds.z;
    }

    inline Vector3 Rectangle::get_bounds() const
    {
        return size;
    }

    inline Vector3 Rectangle::get_bottom_left() const
    {
        return position - (size / 2);
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