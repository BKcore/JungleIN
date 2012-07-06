#ifndef MATRIX3_H
#define MATRIX3_H

#include "matrix4.h"

class Matrix3
{
public:
    union
    {
        float data[4][4];
        float array[16];
    };

    Matrix3();
    Matrix3& getInverse(const Matrix4& m);
    Matrix3& transpose();
    Matrix3& identity();
};

#endif // MATRIX3_H
