#ifndef BIGROCK_VECTOR3_H
#define BIGROCK_VECTOR3_H

namespace bigrock
{
    struct Vector3
    {
        float x, y, z;

        // Constructors

        Vector3();
        Vector3(float x, float y, float z);
        Vector3(const Vector3 &other);

        #pragma region Operators

        // float operators
        Vector3 operator*(const float &val) const;
        Vector3 operator/(const float &val) const;

        Vector3 &operator*=(const float &val);
        Vector3 &operator/=(const float &val);

        // Vector3 operators
        Vector3 operator+(const Vector3 &other) const;
        Vector3 operator-(const Vector3 &other) const;
        Vector3 operator*(const Vector3 &other) const;
        Vector3 operator/(const Vector3 &other) const;

        Vector3 &operator+=(const Vector3 &other);
        Vector3 &operator-=(const Vector3 &other);
        Vector3 &operator*=(const Vector3 &other);
        Vector3 &operator/=(const Vector3 &other);

        bool operator==(const Vector3 &other);
        bool operator!=(const Vector3 &other);

        #pragma endregion

        #pragma region Methods

        float distance_squared_to(const Vector3 &other) const; // Gets the distance to another Vector3 without a costly square root calculation
        float distance_to(const Vector3 &other) const; // Gets the distance between two points. Use this if you NEED precise distance.

        float length_squared() const; // Gets the squared length of the vector (avoids a square root calculation)
        float length() const;

        Vector3 abs() const; // Returns the absolute form of this vector
        Vector3 normalized() const; // Sets the vector's length to 1

        bool is_normalized() const; // Checks if the length squared is equal to 1
        bool is_approximately_equal(const Vector3 &other) const; // Checks if two Vector3s are within floating-point error range

        #pragma endregion
    };
}

#endif