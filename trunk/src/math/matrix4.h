/**
 * @author Thibaut Despoulain
 */

#ifndef MATRIX4_H
#define MATRIX4_H

#include "vector3.h"
#include "quaternion.h"

class Matrix4
{
public:
    union
    {
        float data[4][4];
        float array[16];
    };

    Matrix4();
    Matrix4(const Matrix4 &mat);

    Matrix4& operator=(const Matrix4 &mat);

    Matrix4& set(float,float,float,float,
                 float,float,float,float,
                 float,float,float,float,
                 float,float,float,float);

    Matrix4& identity();
    Matrix4& zero();
    Matrix4& copy(const Matrix4 &mat);
    Matrix4& transpose();
    Matrix4& lookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &up);
    Matrix4& lookAt2(const Vector3 &eye, const Vector3 &target, const Vector3 &up);
    Matrix4& setPerspective(float fov, float ratio, float near, float far);
    Matrix4& setOrthogonal(float left, float right, float top, float bottom, float near, float far);
    Matrix4& setRotationMatrix(float angle, const Vector3 &xyz);
    Matrix4& setRotationMatrix(const Quaternion &q);

    Vector3& rotateAxis(Vector3 &axis);

    Matrix4& setPosition(const Vector3 &xyz);

    Matrix4& translate(const Vector3 &xyz);
    Matrix4& rotate(float angle, const Vector3 &xyz);
    Matrix4& scale(const Vector3 &xyz);

    void log();

    float determinant() const;
    Matrix4 inverse() const;

    Matrix4 operator*(const Matrix4 &mat) const;
    void operator*=(const Matrix4 &mat);

    Matrix4 operator*(const float scalar) const;
    void operator*=(const float scalar);
    Vector3 operator *(const Vector3 vec3) const;
};


#endif // MATRIX4_H
