#ifndef QUATERNION_H
#define QUATERNION_H

#include "vector3.h"

class Quaternion
{
public:
    float x, y ,z, w;

    Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);

    Quaternion& set(float, float, float, float);
    Quaternion& copy(const Quaternion &q);

    Quaternion& setFromVector(const Vector3 &v);
    Quaternion& setFromAngle(float angle, const Vector3 &axis);

    float length();
    Quaternion& divideScalar(float s);
    Quaternion& normalize();
};

#endif // QUATERNION_H
