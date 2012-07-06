#include "matrix3.h"

Matrix3::Matrix3()
{
    identity();
}

Matrix3& Matrix3::getInverse(const Matrix4& m)
{
    // ( based on http://code.google.com/p/webgl-mjs/ )

    float a11 =   m.array[10] * m.array[5] - m.array[6] * m.array[9];
    float a21 = - m.array[10] * m.array[1] + m.array[2] * m.array[9];
    float a31 =   m.array[6] * m.array[1] - m.array[2] * m.array[5];
    float a12 = - m.array[10] * m.array[4] + m.array[6] * m.array[8];
    float a22 =   m.array[10] * m.array[0] - m.array[2] * m.array[8];
    float a32 = - m.array[6] * m.array[0] + m.array[2] * m.array[4];
    float a13 =   m.array[9] * m.array[4] - m.array[5] * m.array[8];
    float a23 = - m.array[9] * m.array[0] + m.array[1] * m.array[8];
    float a33 =   m.array[5] * m.array[0] - m.array[1] * m.array[4];

    float det = m.array[0] * a11 + m.array[1] * a12 + m.array[2] * a13;

    if (det == 0.0)
    {
        return identity();
    }

    float idet = 1.0 / det;

    array[0] = idet * a11; array[1] = idet * a21; array[2] = idet * a31;
    array[3] = idet * a12; array[4] = idet * a22; array[5] = idet * a32;
    array[6] = idet * a13; array[7] = idet * a23; array[8] = idet * a33;

    return *this;
}


Matrix3& Matrix3::transpose()
{
    float tmp;

    tmp = array[1]; array[1] = array[3]; array[3] = tmp;
    tmp = array[2]; array[2] = array[6]; array[6] = tmp;
    tmp = array[5]; array[5] = array[7]; array[7] = tmp;

    return *this;
}

Matrix3& Matrix3::identity()
{
    array[0] = 1; array[1] = 0; array[2] = 0;
    array[3] = 0; array[4] = 1; array[5] = 0;
    array[6] = 0; array[7] = 0; array[8] = 1;

    return *this;
}
