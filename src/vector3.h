#ifndef BIGROCK_VECTOR3_H
#define BIGROCK_VECTOR3_H

#ifndef BIGROCK_VEC3_TYPE
#define BIGROCK_VEC3_TYPE float
#endif

namespace bigrock
{
    struct Vector3
    {
        BIGROCK_VEC3_TYPE x, y, z;

        Vector3(BIGROCK_VEC3_TYPE x, BIGROCK_VEC3_TYPE y, BIGROCK_VEC3_TYPE z);
        Vector3();

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

        #ifdef _IOSTREAM_
        friend std::ostream &operator<<(std::ostream &out, const Vector3 &obj);
        #endif
    };
}

#endif