#include "vector3.h"
#include <cmath>

namespace bigrock
{
    // Constructors
    Vector3::Vector3(BIGROCK_VEC3_TYPE x, BIGROCK_VEC3_TYPE y, BIGROCK_VEC3_TYPE z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3::Vector3()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    inline Vector3 Vector3::inverse() const
    {
        return Vector3(1.0 / x, 1.0 / y, 1.0 / z);
    }

    inline Vector3 Vector3::abs() const
    {
        return Vector3(fabs(x), fabs(y), fabs(z));
    }

    inline Vector3 &Vector3::operator+=(const Vector3 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    inline Vector3 Vector3::operator+(const Vector3 &other) const
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    inline Vector3 &Vector3::operator-=(const Vector3 &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    inline Vector3 Vector3::operator-(const Vector3 &other) const
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    inline Vector3 &Vector3::operator*=(const Vector3 &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    inline Vector3 Vector3::operator*(const Vector3 &other) const
    {
        return Vector3(x * other.x, y * other.y, z * other.z);
    }

    inline Vector3 &Vector3::operator/=(const Vector3 &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    inline Vector3 Vector3::operator/(const Vector3 &other) const
    {
        return Vector3(x / other.x, y / other.y, z / other.z);
    }

    // Comparison

    inline bool Vector3::operator==(const Vector3 &other) const
    {
        return (x == other.x && y == other.y && z == other.z);
    }

    inline bool Vector3::operator!=(const Vector3 &other) const
    {
        return (x != other.x || y != other.y || z != other.z);
    }

    // float/double operators

    inline Vector3 &Vector3::operator*=(const BIGROCK_VEC3_TYPE &other)
    {
        x *= other;
        y *= other;
        z *= other;
        return *this;
    }

    inline Vector3 Vector3::operator*(const BIGROCK_VEC3_TYPE &other) const
    {
        return Vector3(x * other, y * other, z * other);
    }

    inline Vector3 &Vector3::operator/=(const BIGROCK_VEC3_TYPE &other)
    {
        x /= other;
        y /= other;
        z /= other;
        return *this;
    }

    inline Vector3 Vector3::operator/(const BIGROCK_VEC3_TYPE &other) const
    {
        return Vector3(x / other, y / other, z / other);
    }

    // Other operators

    inline Vector3 Vector3::operator-() const
    {
        return Vector3(-x, -y, -z);
    }

    std::ostream &operator<<(std::ostream &out, const Vector3 data)
    {
        out << "(" << data.x << ", " << data.y << ", " << data.z << ")";
        return out;
    }
}