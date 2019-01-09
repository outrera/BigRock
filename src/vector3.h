#ifndef BIGROCK_VECTOR3_H
#define BIGROCK_VECTOR3_H

#define BIGROCK_FLOAT_ENUM 0
#define BIGROCK_DOUBLE_ENUM 1
#define BIGROCK_LONG_DOUBLE_ENUM 2

#ifndef BIGROCK_VEC3_TYPE_ENUM
#define BIGROCK_VEC3_TYPE_ENUM BIGROCK_FLOAT_ENUM
#endif

#if BIGROCK_VEC3_TYPE_ENUM == BIGROCK_LONG_DOUBLE_ENUM
#define BIGROCK_VEC3_TYPE long double
#elif BIGROCK_VEC3_TYPE_ENUM == BIGROCK_DOUBLE_ENUM
#define BIGROCK_VEC3_TYPE double
#else
#define BIGROCK_VEC3_TYPE float
#endif

#include <iostream>

namespace bigrock
{
    struct Vector3
    {
        union
        {
            struct
            {
                BIGROCK_VEC3_TYPE x, y, z;
            };
            BIGROCK_VEC3_TYPE coords[3];
        };

        Vector3(BIGROCK_VEC3_TYPE x, BIGROCK_VEC3_TYPE y, BIGROCK_VEC3_TYPE z);
        Vector3();

        // Methods

        Vector3 normalized() const;

        BIGROCK_VEC3_TYPE distance_squared_to(const Vector3 &point) const; // Gets the distance to another point without performing a costly square root operation
        BIGROCK_VEC3_TYPE distance_to(const Vector3 &point) const; // Gets the distance to another point. Try to avoid this and use distance_squared_to when you can.

        BIGROCK_VEC3_TYPE length_squared() const;
        BIGROCK_VEC3_TYPE length() const;
        
        Vector3 pow(int exp) const; // Returns this vector to the power of exp
        BIGROCK_VEC3_TYPE dot(const Vector3 &other) const;

        // Vector3 Operators
        Vector3 operator+(const Vector3 &other) const;
        Vector3 operator-(const Vector3 &other) const;
        Vector3 operator*(const Vector3 &other) const;
        Vector3 operator/(const Vector3 &other) const;

        Vector3 &operator+=(const Vector3 &other);
        Vector3 &operator-=(const Vector3 &other);
        Vector3 &operator*=(const Vector3 &other);
        Vector3 &operator/=(const Vector3 &other);

        // BIGROCK_VEC3_TYPE Operators
        Vector3 operator*(const BIGROCK_VEC3_TYPE &other) const;
        Vector3 operator/(const BIGROCK_VEC3_TYPE &other) const;

        Vector3 &operator*=(const BIGROCK_VEC3_TYPE &other);
        Vector3 &operator/=(const BIGROCK_VEC3_TYPE &other);

        // Comparison operators
        bool operator==(const Vector3 &other) const;
        bool operator!=(const Vector3 &other) const;

        friend std::ostream &operator<<(std::ostream &out, const Vector3 &obj);
    };
}

#endif