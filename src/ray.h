#ifndef BIGROCK_RAY_H
#define BIGROCK_RAY_H

#include "vector3.h"

namespace bigrock
{
    class Ray
    {
        Vector3 direction;

        public:
        Vector3 origin;

        inline Vector3 get_direction() const {return direction;}
        inline void set_direction(const Vector3 &direction)
        {
            if(direction.is_normalized())
                this->direction = direction;
            else
                this->direction = direction.normalized();
        }

        inline Vector3 get_point_on_ray(float t) const
        {
            return origin + (direction * t);
        }

        Vector3 get_closest_point(const Vector3 &target) const;
    };
}

#endif