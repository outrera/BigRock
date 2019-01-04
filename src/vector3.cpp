#include "vector3.h"

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