#ifndef BIGROCK_VECTOR3_H
#define BIGROCK_VECTOR3_H

namespace bigrock
{
    struct Vector3
    {
        float x, y, z;

        // Constructors

        Vector3()
        {
            this->x = 0;
            this->y = 0;
            this->z = 0;
        }

        Vector3(float x, float y, float z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        Vector3(const Vector3 &other)
        {
            this->x = other.x;
            this->y = other.y;
            this->z = other.z;
        }

        #pragma region Operators

        // float operators
        inline Vector3 operator*(const float &val) const
        {
            return Vector3(this->x * val, this->y * val, this->z * val);
        }

        inline Vector3 operator/(const float &val) const
        {
            return Vector3(this->x / val, this->y / val, this->z / val);
        }

        inline Vector3 &operator*=(const float &val)
        {
            this->x *= val;
            this->y *= val;
            this->z *= val;
            return *this;
        }

        inline Vector3 &operator/=(const float &val)
        {
            this->x /= val;
            this->y /= val;
            this->z /= val;
            return *this;
        }

        // Vector3 operators
        inline Vector3 operator+(const Vector3 &other) const
        {
            return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
        }

        inline Vector3 operator-(const Vector3 &other) const
        {
            return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
        }

        inline Vector3 operator*(const Vector3 &other) const
        {
            return Vector3(this->x * other.x, this->y * other.y, this->z * other.z);
        }

        inline Vector3 operator/(const Vector3 &other) const
        {
            return Vector3(this->x / other.x, this->y / other.y, this->z / other.z);
        }

        inline Vector3 &operator+=(const Vector3 &other)
        {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            return *this;
        }

        inline Vector3 &operator-=(const Vector3 &other)
        {
            this->x -= other.x;
            this->y -= other.y;
            this->z -= other.z;
            return *this;
        }

        inline Vector3 &operator*=(const Vector3 &other)
        {
            this->x *= other.x;
            this->y *= other.y;
            this->z *= other.z;
            return *this;
        }

        inline Vector3 &operator/=(const Vector3 &other)
        {
            this->x /= other.x;
            this->y /= other.y;
            this->z /= other.z;
            return *this;
        }

        #pragma endregion

        #pragma region Methods

        Vector3 abs() const;

        float distance_squared_to(const Vector3 &other) const; // Gets the distance to another Vector3 without a costly square root calculation
        float distance_to(const Vector3 &other) const; // Gets the distance between two points. Use this if you NEED precise distance.

        float length_squared() const;
        float length() const;

        #pragma endregion
    };
}

#endif