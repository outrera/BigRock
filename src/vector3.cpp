#include "vector3.h"
#include <math.h>

namespace bigrock
{
    float Vector3::distance_squared_to(const Vector3 &other) const
    {
        float xdelt, ydelt, zdelt;
        xdelt = (other.x - this->x);
        ydelt = (other.y - this->y);
        zdelt = (other.z - this->z);
        return (xdelt * xdelt) + (ydelt * ydelt) + (zdelt * zdelt);
    }

    float Vector3::distance_to(const Vector3 &other) const
    {
        return sqrtf(this->distance_squared_to(other));
    }

    float Vector3::length_squared() const
    {
        return (x * x) + (y * y) + (z * z);
    }

    float Vector3::length() const
    {
        return sqrtf(this->length_squared());
    }
}