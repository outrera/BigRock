#ifndef BIGROCK_VECTOR3_H
#define BIGROCK_VECTOR3_H

namespace bigrock
{
    // Based on Godot's Vector3 class
    class Vector3
    {
        public:
        float x, y, z;

        Vector3(float x, float y, float z);
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

        // float operators
        Vector3 &operator*=(const float &other);
        Vector3 operator*(const float &other) const;
        Vector3 &operator/=(const float &other);
        Vector3 operator/(const float &other) const;

        // Other operators
        Vector3 operator-() const; // Negative operator
    };
}

#endif