#include "vector3.h"
#include <cmath>
#include <limits>

const Vector3 Vector3::X = Vector3(1.0, 0.0, 0.0);
const Vector3 Vector3::Y = Vector3(0.0, 1.0, 0.0);
const Vector3 Vector3::Z = Vector3(0.0, 0.0, 1.0);
const Vector3 Vector3::ZERO = Vector3(0.0, 0.0, 0.0);

Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3& Vector3::set(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;

    return *this;
}

Vector3& Vector3::copy(const Vector3 &v)
{
    x = v.x;
    y = v.y;
    z = v.z;

    return *this;
}

float Vector3::length() const
{
    return std::sqrt(x*x + y*y + z*z);
}

float Vector3::distanceSq(const Vector3& v) const
{
    float dx = x - v.x,
            dy = y - v.y,
            dz = z - v.z;

    return dx*dx+dy*dy+dz*dz;
}

Vector3& Vector3::cross(const Vector3 &a, const Vector3 &b)
{
    x = a.y * b.z - a.z * b.y;
    y = a.z * b.x - a.x * b.z;
    z = a.x * b.y - a.y * b.x;

    return *this;
}

float Vector3::dot(const Vector3 &v)
{
    return x * v.x + y * v.y + z * v.z;
}

Vector3& Vector3::normalize()
{
    return divideScalar(length());
}

Vector3& Vector3::divideScalar(float s)
{
    if(s > std::numeric_limits<float>::epsilon())
    {
        x /= s;
        y /= s;
        z /= s;
    }
    else
    {
        x = 0;
        y = 0;
        z = 0;
    }

    return *this;
}

bool Vector3::isZero()
{
    return (x == 0.0f && y == 0.0f && z == 0.0f);
}

Vector3 Vector3::operator+(const Vector3 &v) const
{
    return Vector3(x+v.x, y+v.y, z+v.z);
}

void Vector3::operator+=(const Vector3 &v)
{
    x += v.x;
    y += v.y;
    z += v.z;
}

bool Vector3::operator==(const Vector3 &v) const
{
    return ((this->x == v.x) && (this->y == v.y) && (this->z == v.z));
}

Vector3 Vector3::operator-(const Vector3 &v) const
{
    return Vector3(x-v.x, y-v.y, z-v.z);
}

void Vector3::operator-=(const Vector3 &v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

Vector3 Vector3::operator*(const float s) const
{
    return Vector3(x*s, y*s, z*s);
}

void Vector3::operator *=(float s)
{
    x *= s;
    y *= s;
    z *= s;
}

QString Vector3::toString()
{
    return "Vector3("
            +QString::number(x)+", "
            +QString::number(y)+", "
            +QString::number(z)
            +")";
}
