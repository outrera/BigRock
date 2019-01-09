#include "vector3.h"

#include <math.h>
#include <iostream>

#if BIGROCK_VEC3_TYPE_ENUM == BIGROCK_LONG_DOUBLE_ENUM
#define _sqrt sqrtl
#define _pow powl
#elif BIGROCK_VEC3_TYPE_ENUM == BIGROCK_DOUBLE_ENUM
#define _sqrt sqrt
#define _pow pow
#else
#define _sqrt sqrtf
#define _pow powf
#endif

namespace bigrock
{
    Vector3::Vector3(BIGROCK_VEC3_TYPE x, BIGROCK_VEC3_TYPE y, BIGROCK_VEC3_TYPE z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3::Vector3()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }

    #pragma region Methods

    Vector3 Vector3::normalized() const
    {
        return (*this) / this->length();
    }

    BIGROCK_VEC3_TYPE Vector3::distance_squared_to(const Vector3 &point) const
    {
        BIGROCK_VEC3_TYPE x, y, z;
        x = (point.x - this->x);
        y = (point.y - this->y);
        z = (point.z - this->z);
        return (x * x) + (y * y) + (z * z);
    }

    BIGROCK_VEC3_TYPE Vector3::distance_to(const Vector3 &point) const
    {
        return _sqrt(this->distance_squared_to(point));
    }

    BIGROCK_VEC3_TYPE Vector3::length_squared() const
    {
        return (this->x * this->x) + (this->y * this->y) + (this->z + this->z);
    }

    BIGROCK_VEC3_TYPE Vector3::length() const
    {
        return _sqrt(this->length_squared());
    }

    Vector3 Vector3::pow(int exp) const
    {
        return Vector3(_pow(this->x, exp), _pow(this->y, exp), _pow(this->z, exp));
    }

    #pragma endregion

    #pragma region Vector3 Operators
    Vector3 Vector3::operator+(const Vector3 &other) const
    {
        return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
    }
    Vector3 Vector3::operator-(const Vector3 &other) const
    {
        return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
    }
    Vector3 Vector3::operator*(const Vector3 &other) const
    {
        return Vector3(this->x * other.x, this->y * other.y, this->z * other.z);
    }
    Vector3 Vector3::operator/(const Vector3 &other) const
    {
        return Vector3(this->x / other.x, this->y / other.y, this->z / other.x);
    }

    Vector3 &Vector3::operator+=(const Vector3 &other)
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }
    Vector3 &Vector3::operator-=(const Vector3 &other)
    {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        return *this;
    }
    Vector3 &Vector3::operator*=(const Vector3 &other)
    {
        this->x *= other.x;
        this->y *= other.y;
        this->z *= other.z;
        return *this;
    }
    Vector3 &Vector3::operator/=(const Vector3 &other)
    {
        this->x /= other.x;
        this->y /= other.y;
        this->z /= other.z;
        return *this;
    }
    #pragma endregion // Vector3 Operators

    #pragma region BIGROCK_VEC3_TYPE Operators

    Vector3 Vector3::operator*(const BIGROCK_VEC3_TYPE &other) const
    {
        return Vector3(this->x * other, this->y * other, this->z * other);
    }
    Vector3 Vector3::operator/(const BIGROCK_VEC3_TYPE &other) const
    {
        return Vector3(this->x / other, this->y / other, this->z / other);
    }

    Vector3 &Vector3::operator*=(const BIGROCK_VEC3_TYPE &other)
    {
        this->x *= other;
        this->y *= other;
        this->z *= other;
        return *this;
    }
    Vector3 &Vector3::operator/=(const BIGROCK_VEC3_TYPE &other)
    {
        this->x *= other;
        this->y *= other;
        this->z *= other;
        return *this;
    }

    #pragma endregion // BIGROCK_VEC3_TYPE Operators

    std::ostream &operator<<(std::ostream &out, const Vector3 &obj)
    {
        out << "(" << obj.x << ", " << obj.y << ", " << obj.z << ")";
        return out;
    }

    bool Vector3::operator==(const Vector3 &other) const
    {
        return (this->x == other.x && this->y == other.y && this->z == other.z);
    }

    bool Vector3::operator!=(const Vector3 &other) const
    {
        return (this->x != other.x || this->y != other.y || this->z != other.z);
    }
}