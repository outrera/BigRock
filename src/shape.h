#ifndef BIGROCK_SHAPE_H
#define BIGROCK_SHAPE_H

#include "vector3.h"
#include "ray.h"

namespace bigrock
{
    // Represents convex shapes
    // P.S. I am not implementing concave shapes
    struct Shape
    {
        Vector3 position;

        virtual bool contains_point(const Vector3 &point) const;
        virtual Vector3 get_closest_point(const Vector3 &target) const;
        virtual bool intersects_shape(const Shape &other) const;

        bool intersects_ray(const Ray &ray, float max_length) const
        {
            Vector3 closest = ray.get_closest_point(position);

            if(ray.origin.distance_squared_to(closest) > (max_length * max_length)) // Out of range
                return false;
            else
                return this->contains_point(closest);
        }
    };

    struct Sphere : Shape
    {
        float radius;

        inline bool contains_point(const Vector3 &point) const
        {
            return position.distance_squared_to(point) <= (radius * radius);
        }

        Vector3 get_closest_point(const Vector3 &target) const;
    };
}

#endif