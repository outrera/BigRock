#include "vector3.h"
#include <math.h>
#include <limits>

namespace bigrock
{
    // Constructors

    Vector3::Vector3()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }

    Vector3::Vector3(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3::Vector3(const Vector3 &other)
    {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
    }

    // Operators

    #pragma region Operators

    // float operators
    Vector3 Vector3::operator*(const float &val) const
    {
        return Vector3(this->x * val, this->y * val, this->z * val);
    }

    Vector3 Vector3::operator/(const float &val) const
    {
        return Vector3(this->x / val, this->y / val, this->z / val);
    }

    Vector3 &Vector3::operator*=(const float &val)
    {
        this->x *= val;
        this->y *= val;
        this->z *= val;
        return *this;
    }

    Vector3 &Vector3::operator/=(const float &val)
    {
        this->x /= val;
        this->y /= val;
        this->z /= val;
        return *this;
    }

    // Vector3 operators
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
        return Vector3(this->x / other.x, this->y / other.y, this->z / other.z);
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

    bool Vector3::operator==(const Vector3 &other)
    {
        return this->x == other.x && this->y == other.y && this->z == other.z;
    }

    bool Vector3::operator!=(const Vector3 &other)
    {
        return this->x != other.x || this->y != other.y || this->z != other.z;
    }

    #pragma endregion

    float Vector3::distance_squared_to(const Vector3 &other) const
    {
        float xdelt, ydelt, zdelt;
        xdelt = (other.x - this->x);
        ydelt = (other.y - this->y);
        zdelt = (other.z - this->z);
        return (xdelt * xdelt) + (ydelt * ydelt) + (zdelt * zdelt);
    }

    float Vector3::distance_to(const Vector3 &other) const
    {
        return sqrtf(this->distance_squared_to(other));
    }

    float Vector3::length_squared() const
    {
        return (x * x) + (y * y) + (z * z);
    }

    float Vector3::length() const
    {
        return sqrtf(this->length_squared());
    }

    Vector3 Vector3::abs() const
    {
        return Vector3(fabsf(this->x), fabsf(this->y), fabsf(this->z));
    }

    Vector3 Vector3::normalized() const
    {
        return *this / this->length();
    }

    bool Vector3::is_normalized() const
    {
        return fabsf(1 - this->length_squared()) < std::numeric_limits<float>::epsilon(); // Approximately equal to 1
    }

    bool Vector3::is_approximately_equal(const Vector3 &other) const
    {
        float epsilon = std::numeric_limits<float>::epsilon(); // This is less accurate the further "this" and "other" get from (0,0,0)
        
        if(fabsf(other.x - this->x) >= epsilon)
            return false;
        if(fabsf(other.y - this->y) >= epsilon)
            return false;
        if(fabsf(other.z - this->z) >= epsilon)
            return false;

        return true;
    }
}