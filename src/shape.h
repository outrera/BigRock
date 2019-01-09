#ifndef BIGROCK_SHAPE_H
#define BIGROCK_SHAPE_H

#include "vector3.h"

namespace bigrock
{
    struct Shape
    {
        Vector3 position; // The position of the CENTER of this shape

        // Returns true if point is inside this shape
        virtual bool point_intersects(const Vector3 &point) const = 0;
        // Returns the bounding box size of this shape
        virtual Vector3 get_bounds() const = 0;
        // Returns the bottom-left corner of the bounding box
        virtual Vector3 get_bottom_left() const = 0;
        // Returns the point on this shape closest to the target
        virtual Vector3 get_closest_point(const Vector3 &target) const = 0;

        // Tests if this shape interacts with the other shape
        bool interacts_with_shape(const Shape &other) const;
    };

    struct Sphere : public Shape
    {
        Sphere() {position = Vector3(0,0,0); radius = 0.5;}
        Sphere(BIGROCK_VEC3_TYPE radius) {this->position = Vector3(0,0,0); this->radius = radius;}
        Sphere(Vector3 position, BIGROCK_VEC3_TYPE radius) {this->position = position; this->radius = radius;}

        BIGROCK_VEC3_TYPE radius;

        inline bool point_intersects(const Vector3 &point) const
        {
            return position.distance_squared_to(point) <= (radius * radius);
        }

        inline Vector3 get_bounds() const
        {
            return Vector3(radius * 2, radius * 2, radius * 2);
        }

        inline Vector3 get_bottom_left() const
        {
            return position - Vector3(radius, radius, radius);
        }
        
        inline Vector3 get_closest_point(const Vector3 &other) const
        {
            return position + ((other - position).normalized() * radius);
        }
    };

    struct Rectangle : public Shape
    {
        Rectangle() {position = Vector3(0,0,0), size = Vector3(1,1,1);}
        Rectangle(Vector3 size) {this->position = Vector3(0,0,0); this->size = size;}
        Rectangle(Vector3 position, Vector3 size) {this->position = position; this->size = size;}

        Vector3 size;

        bool point_intersects(const Vector3 &point) const;

        inline Vector3 get_bounds() const
        {
            return size;
        }

        inline Vector3 get_bottom_left() const
        {
            return position - (size / 2);
        }
        
        Vector3 get_closest_point(const Vector3 &target) const;
    };
}

#endif