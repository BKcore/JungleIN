#ifndef VECTOR3_H
#define VECTOR3_H

#include <GL/glew.h>
#include <QString>

class Vector3
{
public:
    static const Vector3 X;
    static const Vector3 Y;
    static const Vector3 Z;
    static const Vector3 ZERO;

    float x, y, z;

    Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

    Vector3& set(float, float y, float z);
    Vector3& copy(const Vector3 &v);

    float length() const;
    float distanceSq(const Vector3& v) const;
    Vector3& cross(const Vector3 &a, const Vector3 &b);
    float dot(const Vector3 &v);
    Vector3& normalize();
    Vector3& divideScalar(float s);

    bool isZero();

    Vector3 operator+(const Vector3 &v) const;
    void operator+=(const Vector3 &v);
    bool operator==(const Vector3 &v) const;
    Vector3 operator-(const Vector3 &v) const;
    void operator-=(const Vector3 &v);
    Vector3 operator*(const float s) const;
    void operator*=(const float s);

    QString toString();
};

#endif // VECTOR3_H
