#ifndef BIGROCK_VECTOR3_H
#define BIGROCK_VECTOR3_H

#include <iostream>

#ifndef BIGROCK_VEC3_TYPE // Define this as whatever decimal type you want to use
#define BIGROCK_VEC3_TYPE float
#endif

namespace bigrock
{
    // Based on Godot's Vector3 class
    class Vector3
    {
        public:
        BIGROCK_VEC3_TYPE x, y, z;

        Vector3(BIGROCK_VEC3_TYPE x, BIGROCK_VEC3_TYPE y, BIGROCK_VEC3_TYPE z);
        Vector3();

        Vector3 inverse() const;
        Vector3 abs() const;
        
        // Vector3 operators
        Vector3 &operator+=(const Vector3 &other);
        Vector3 operator+(const Vector3 &other) const;
        Vector3 &operator-=(const Vector3 &other);
        Vector3 operator-(const Vector3 &other) const;
        Vector3 &operator*=(const Vector3 &other);
        Vector3 operator*(const Vector3 &other) const;
        Vector3 &operator/=(const Vector3 &other);
        Vector3 operator/(const Vector3 &other) const;

        bool operator==(const Vector3 &other) const;
        bool operator!=(const Vector3 &other) const;

        // BIGROCK_VEC3_TYPE operators
        Vector3 &operator*=(const BIGROCK_VEC3_TYPE &other);
        Vector3 operator*(const BIGROCK_VEC3_TYPE &other) const;
        Vector3 &operator/=(const BIGROCK_VEC3_TYPE &other);
        Vector3 operator/(const BIGROCK_VEC3_TYPE &other) const;

        // Other operators
        Vector3 operator-() const; // Negative operator
        friend std::ostream &operator<<(std::ostream &out, const Vector3 data);
    };
}

#endif