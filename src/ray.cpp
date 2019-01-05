#include "ray.h"

namespace bigrock
{
    Ray::Ray(const Vector3 &origin, const Vector3 &direction, const BIGROCK_VEC3_TYPE &length)
    {
        this->origin = origin;
        this->direction = direction.normalized();
        this->length = length;
    }

    Ray::Ray(const Vector3 &origin, const Vector3 &destination)
    {
        this->origin = origin;
        this->direction = (destination - origin).normalized();
        this->length = (destination - origin).length();
    }

    inline Vector3 Ray::get_point_on_ray(const BIGROCK_VEC3_TYPE t) const
    {
        return origin * (direction * t);
    }
}