#ifndef BIGROCK_RAY_H
#define BIGROCK_RAY_H

#include "vector3.h"

namespace bigrock
{
    struct Ray
    {
        protected:
        Vector3 direction; // Direction needs getter/setter to stay normalized

        public:
        Vector3 origin;
        BIGROCK_VEC3_TYPE length;

        Ray(const Vector3 &origin, const Vector3 &direction, const BIGROCK_VEC3_TYPE &length);
        Ray(const Vector3 &origin, const Vector3 &destination);

        inline Vector3 get_direction() const {return direction;}
        inline void set_direction(const Vector3 &direction) {this->direction = direction.normalized();}

        Vector3 get_point_on_ray(const BIGROCK_VEC3_TYPE t) const;
    };
}

#endif