

#include "matrix4.h"
#include <QDebug>
#include <cmath>
#include <limits>

Matrix4::Matrix4()
{
    identity();
}

Matrix4::Matrix4(const Matrix4 &mat)
{
    set(mat.array[0], mat.array[1], mat.array[2], mat.array[3],
        mat.array[4], mat.array[5], mat.array[6], mat.array[7],
        mat.array[8], mat.array[9], mat.array[10], mat.array[11],
        mat.array[12], mat.array[13], mat.array[14], mat.array[15]);
}

Matrix4& Matrix4::operator=(const Matrix4 &mat)
{
    set(mat.array[0], mat.array[1], mat.array[2], mat.array[3],
        mat.array[4], mat.array[5], mat.array[6], mat.array[7],
        mat.array[8], mat.array[9], mat.array[10], mat.array[11],
        mat.array[12], mat.array[13], mat.array[14], mat.array[15]);

    return *this;
}

Matrix4& Matrix4::set(float n11, float n12, float n13, float n14,
                      float n21, float n22, float n23, float n24,
                      float n31, float n32, float n33, float n34,
                      float n41, float n42, float n43, float n44 )
{

    array[0] = n11; array[1] = n12; array[2] = n13; array[3] = n14;
    array[4] = n21; array[5] = n22; array[6] = n23; array[7] = n24;
    array[8] = n31; array[9] = n32; array[10] = n33; array[11] = n34;
    array[12] = n41; array[13] = n42; array[14] = n43; array[15] = n44;

    return *this;
}

Matrix4& Matrix4::copy(const Matrix4 &mat)
{
    set(mat.array[0], mat.array[1], mat.array[2], mat.array[3],
        mat.array[4], mat.array[5], mat.array[6], mat.array[7],
        mat.array[8], mat.array[9], mat.array[10], mat.array[11],
        mat.array[12], mat.array[13], mat.array[14], mat.array[15]);

    return *this;
}

Matrix4& Matrix4::lookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &up)
{
    Vector3 x, y, z;

    z = (target - eye).normalize();
    if(z.isZero()) z.z = 0.1;

    x.cross(z, up).normalize();
    y.cross(x, z).normalize();

    identity();

    data[0][0] = x.x;
    data[1][0] = x.y;
    data[2][0] = x.z;

    data[0][1] = y.x;
    data[1][1] = y.y;
    data[2][1] = y.z;

    data[0][2] = -z.x;
    data[1][2] = -z.y;
    data[2][2] = -z.z;

    setPosition(eye);

    return *this;
}

Matrix4& Matrix4::lookAt2(const Vector3 &eye, const Vector3 &target, const Vector3 &up)
{
    Vector3 x, y, z;

    z = (target - eye).normalize();
    if(z.isZero()) z.z = 0.1;

    x.cross(z, up).normalize();
    y.cross(x, z).normalize();

    identity();

    data[0][0] = x.x;
    data[1][0] = y.x;
    data[2][0] = -z.x;

    data[0][1] = x.y;
    data[1][1] = y.y;
    data[2][1] = -z.y;

    data[0][2] = x.z;
    data[1][2] = y.z;
    data[2][2] = -z.z;

    data[0][3] = -x.dot(eye);
    data[1][3] = -y.dot(eye);
    data[2][3] = z.dot(eye);


    return *this;
}

Matrix4& Matrix4::setPerspective(float fov, float ratio, float near, float far)
{
    float thetaY = 0.5f * (M_PI * fov / 180.0f);
    float tanThetaY = std::tan(thetaY);
    float tanThetaX = tanThetaY * ratio;
    float halfW   =  tanThetaX * near;
    float halfH   =  tanThetaY * near;
    float left    = -halfW;
    float right   =  halfW;
    float bottom  = -halfH;
    float top     =  halfH;
    float iWidth  = 1.0f / (right - left);
    float iHeight = 1.0f / (top - bottom);
    float iDepth  = 1.0f / (far - near);

    data[0][0] = 2.0f * near * iWidth;  data[0][1] = 0.0f;                   data[0][2] =  (right + left) * iWidth;  data[0][3] =  0.0f;
    data[1][0] = 0.0f;                  data[1][1] = 2.0f * near * iHeight;  data[1][2] =  (top + bottom) * iHeight; data[1][3] =  0.0f;
    data[2][0] = 0.0f;                  data[2][1] = 0.0f;                   data[2][2] = -(far + near) * iDepth;    data[2][3] = -2.0f * (far * near) * iDepth;
    data[3][0] = 0.0f;                  data[3][1] = 0.0f;                   data[3][2] = -1.0f;                     data[3][3] =  0.0f;

    return *this;
}

Matrix4& Matrix4::setOrthogonal(float left, float right, float top, float bottom, float near, float far)
{
    float x, y, z, w, h, p;

    w = right - left;
    h = top - bottom;
    p = far - near;

    x = ( right + left ) / w;
    y = ( top + bottom ) / h;
    z = ( far + near ) / p;

    data[0][0] = 2 / w; data[0][1] = 0;     data[0][2] = 0;      data[0][3] = -x;
    data[1][0] = 0;     data[1][1] = 2 / h; data[1][2] = 0;      data[1][3] = -y;
    data[2][0] = 0;     data[2][1] = 0;     data[2][2] = -2 / p; data[2][3] = -z;
    data[3][0] = 0;     data[3][1] = 0;     data[3][2] = 0;      data[3][3] = 1;

    return *this;
}

Matrix4& Matrix4::setRotationMatrix(float angle, const Vector3 &xyz)
{
    float x = xyz.x, y = xyz.y, z = xyz.z;

    float rAngle = M_PI * angle / 180.0f;
    float c = std::cos(rAngle);
    float s = std::sin(rAngle);

    float len = xyz.length();
    if(len > std::numeric_limits<float>::epsilon())
    {
        x /= len;
        y /= len;
        z /= len;
    }

    data[0][0] = x * x * (1.0f - c) + c;     data[0][1] = x * y * (1.0f - c) - z * s; data[0][2] = x * z * (1.0f - c) + y * s; //data[0][3] = 0.0f;
    data[1][0] = y * x * (1.0f - c) + z * s; data[1][1] = y * y * (1.0f - c) + c;     data[1][2] = y * z * (1.0f - c) - x * s; //data[1][3] = 0.0f;
    data[2][0] = z * x * (1.0f - c) - y * s; data[2][1] = y * z * (1.0f - c) + x * s; data[2][2] = z * z * (1.0f - c) + c;     //data[2][3] = 0.0f;
    //data[3][0] = 0.0f;                       data[3][1] = 0.0f;                       data[3][2] = 0.0f;                       data[3][3] = 1.0f;

    return *this;
}

Matrix4& Matrix4::setRotationMatrix(const Quaternion &q)
{
    float x = q.x,
          y = q.y,
          z = q.z,
          w = q.w,

        x2 = x + x,     y2 = y + y,     z2 = z + z,
        xx = x * x2,    xy = x * y2,    xz = x * z2,
        yy = y * y2,    yz = y * z2,    zz = z * z2,
        wx = w * x2,    wy = w * y2,    wz = w * z2;

    data[0][0] = 1 - ( yy + zz );
    data[0][1] = xy - wz;
    data[0][2] = xz + wy;

    data[1][0] = xy + wz;
    data[1][1] = 1 - ( xx + zz );
    data[1][2] = yz - wx;

    data[2][0] = xz - wy;
    data[2][1] = yz + wx;
    data[2][2] = 1 - ( xx + yy );

    return *this;
}

Vector3& Matrix4::rotateAxis(Vector3 &axis)
{

    float vx = axis.x, vy = axis.y, vz = axis.z;

    /*axis.x = vx * data[0][0] + vy * data[1][0] + vz * data[2][0];
    axis.y = vx * data[0][1] + vy * data[1][1] + vz * data[2][1];
    axis.z = vx * data[0][2] + vy * data[1][2] + vz * data[2][2];
    */
    axis.x = vx * data[0][0] + vy * data[0][1] + vz * data[0][2];
    axis.y = vx * data[1][0] + vy * data[1][1] + vz * data[1][2];
    axis.z = vx * data[2][0] + vy * data[2][1] + vz * data[2][2];

    axis.normalize();

    return axis;

}

Matrix4& Matrix4::transpose()
{
    float tmp;

    tmp = data[1][0]; data[1][0] = data[0][1]; data[0][1] = tmp;
    tmp = data[2][0]; data[2][0] = data[0][2]; data[0][2] = tmp;
    tmp = data[2][1]; data[2][1] = data[1][2]; data[1][2] = tmp;

    tmp = data[3][0]; data[3][0] = data[0][3]; data[0][3] = tmp;
    tmp = data[3][1]; data[3][1] = data[1][3]; data[1][3] = tmp;
    tmp = data[3][2]; data[3][2] = data[2][3]; data[2][3] = tmp;

    return *this;
}

Matrix4& Matrix4::setPosition(const Vector3 &xyz)
{
    data[0][3] = xyz.x;
    data[1][3] = xyz.y;
    data[2][3] = xyz.z;

    return *this;
}

Matrix4& Matrix4::translate(const Vector3 &xyz)
{

    /*data[0][3] = data[0][0] * xyz.x + data[0][1] * xyz.y + data[0][2] * xyz.z + data[0][3];
    data[1][3] = data[1][0] * xyz.x + data[1][1] * xyz.y + data[1][2] * xyz.z + data[1][3];
    data[2][3] = data[2][0] * xyz.x + data[2][1] * xyz.y + data[2][2] * xyz.z + data[2][3];
    data[3][3] = data[3][0] * xyz.x + data[3][1] * xyz.y + data[3][2] * xyz.z + data[3][3];*/

    data[0][3] += xyz.x;
    data[1][3] += xyz.y;
    data[2][3] += xyz.z;

    return *this;
}

Matrix4& Matrix4::scale(const Vector3 &xyz)
{
    data[0][0] *= xyz.x; data[0][1] *= xyz.x; data[0][2] *= xyz.x; data[0][3] *= xyz.x;
    data[1][0] *= xyz.y; data[1][1] *= xyz.y; data[1][2] *= xyz.y; data[1][3] *= xyz.y;
    data[2][0] *= xyz.z; data[2][1] *= xyz.z; data[2][2] *= xyz.z; data[2][3] *= xyz.z;

    return *this;
}

Matrix4& Matrix4::rotate(float angle, const Vector3 &xyz)
{
    *this *= Matrix4().setRotationMatrix(angle, xyz);

    return *this;
}

float Matrix4::determinant() const
{
    float m0= data[0][0], m1  = data[1][0], m2  = data[2][0], m3  = data[3][0],
         m4 = data[0][1], m5  = data[1][1], m6  = data[2][1], m7  = data[3][1],
         m8 = data[0][2], m9  = data[1][2], m10 = data[2][2], m11 = data[3][2],
        m12 = data[0][3], m13 = data[1][3], m14 = data[2][3], m15 = data[3][3];

    return (
        m12 * m9 * m6 * m3  - m8 * m13 * m6 * m3    - m12 * m5 * m10 * m3   + m4 * m13 * m10 * m3   +
        m8 * m5 * m14 * m3  - m4 * m9 * m14 * m3    - m12 * m9 * m2 * m7    + m8 * m13 * m2 * m7    +
        m12 * m1 * m10 * m7 - m0 * m13 * m10 * m7   - m8 * m1 * m14 * m7    + m0 * m9 * m14 * m7    +
        m12 * m5 * m2 * m11 - m4 * m13 * m2 * m11   - m12 * m1 * m6 * m11   + m0 * m13 * m6 * m11   +
        m4 * m1 * m14 * m11 - m0 * m5 * m14 * m11   - m8 * m5 * m2 * m15    + m4 * m9 * m2 * m15    +
        m8 * m1 * m6 * m15  - m0 * m9 * m6 * m15    - m4 * m1 * m10 * m15   + m0 * m5 * m10 * m15
    );
}

Matrix4 Matrix4::inverse() const
{
    Matrix4 t;

    float m0= data[0][0], m1  = data[1][0], m2  = data[2][0], m3  = data[3][0],
         m4 = data[0][1], m5  = data[1][1], m6  = data[2][1], m7  = data[3][1],
         m8 = data[0][2], m9  = data[1][2], m10 = data[2][2], m11 = data[3][2],
        m12 = data[0][3], m13 = data[1][3], m14 = data[2][3], m15 = data[3][3];

    t.data[0][0] = (m9*m14*m7    -m13*m10*m7     +m13*m6*m11     -m5*m14*m11     -m9*m6*m15      +m5*m10*m15);
    t.data[1][0] = (m13*m10*m3   -m9*m14*m3      -m13*m2*m11     +m1*m14*m11     +m9*m2*m15      -m1*m10*m15);
    t.data[2][0] = (m5*m14*m3    -m13*m6*m3      +m13*m2*m7      -m1*m14*m7      -m5*m2*m15      +m1*m6*m15);
    t.data[3][0] = (m9*m6*m3     -m5*m10*m3      -m9*m2*m7       +m1*m10*m7      +m5*m2*m11      -m1*m6*m11);

    t.data[0][1] = (m12*m10*m7   -m8*m14*m7      -m12*m6*m11     +m4*m14*m11     +m8*m6*m15      -m4*m10*m15);
    t.data[1][1] = (m8*m14*m3    -m12*m10*m3     +m12*m2*m11     -m0*m14*m11     -m8*m2*m15      +m0*m10*m15);
    t.data[2][1] = (m12*m6*m3    -m4*m14*m3      -m12*m2*m7      +m0*m14*m7      +m4*m2*m15      -m0*m6*m15);
    t.data[3][1] = (m4*m10*m3    -m8*m6*m3       +m8*m2*m7       -m0*m10*m7      -m4*m2*m11      +m0*m6*m11);

    t.data[0][2] = (m8*m13*m7    -m12*m9*m7      +m12*m5*m11     -m4*m13*m11     -m8*m5*m15      +m4*m9*m15);
    t.data[1][2] = (m12*m9*m3    -m8*m13*m3      -m12*m1*m11     +m0*m13*m11     +m8*m1*m15      -m0*m9*m15);
    t.data[2][2] = (m4*m13*m3    -m12*m5*m3      +m12*m1*m7      -m0*m13*m7      -m4*m1*m15      +m0*m5*m15);
    t.data[3][2] = (m8*m5*m3     -m4*m9*m3       -m8*m1*m7       +m0*m9*m7       +m4*m1*m11      -m0*m5*m11);

    t.data[0][3] = (m12*m9*m6    -m8*m13*m6      -m12*m5*m10     +m4*m13*m10     +m8*m5*m14      -m4*m9*m14);
    t.data[1][3] = (m8*m13*m2    -m12*m9*m2      +m12*m1*m10     -m0*m13*m10     -m8*m1*m14      +m0*m9*m14);
    t.data[2][3] = (m12*m5*m2    -m4*m13*m2      -m12*m1*m6      +m0*m13*m6      +m4*m1*m14      -m0*m5*m14);
    t.data[3][3] = (m4*m9*m2     -m8*m5*m2       +m8*m1*m6       -m0*m9*m6       -m4*m1*m10      +m0*m5*m10);

    float d = determinant();

    if(d == 0.0f)
    {
        return t.zero();
    }

    float s = 1.0 / d;
    t *= s;

    return t;
}

Matrix4 Matrix4::operator*(const Matrix4 &mat) const
{
    Matrix4 result;

    for(int idx = 0; idx < 4; idx++)
    {
        for(int idy = 0; idy < 4; idy++)
        {
            result.data[idy][idx] = 0.0f;
            for(int idz = 0; idz < 4; idz++)
            {
                result.data[idy][idx] += data[idy][idz] * mat.data[idz][idx];
            }
        }
    }
    return result;
}

void Matrix4::operator*=(const Matrix4 &mat)
{
    copy(mat * *this);
}

Matrix4 Matrix4::operator*(const float scalar) const
{
    Matrix4 result;

    for(int idx = 0; idx < 4; idx++)
    {
        for(int idy = 0; idy < 4; idy++)
        {
            result.data[idx][idy] = data[idx][idy] * scalar;
        }
    }
    return result;
}

void Matrix4::operator*=(const float scalar)
{
    for(int idx = 0; idx < 4; idx++)
    {
        for(int idy = 0; idy < 4; idy++)
        {
            data[idx][idy] *= scalar;
        }
    }
}

Matrix4& Matrix4::identity()
{
    data[0][0] = 1.0f; data[0][1] = 0.0f; data[0][2] = 0.0f; data[0][3] = 0.0f;
    data[1][0] = 0.0f; data[1][1] = 1.0f; data[1][2] = 0.0f; data[1][3] = 0.0f;
    data[2][0] = 0.0f; data[2][1] = 0.0f; data[2][2] = 1.0f; data[2][3] = 0.0f;
    data[3][0] = 0.0f; data[3][1] = 0.0f; data[3][2] = 0.0f; data[3][3] = 1.0f;

    return *this;
}

Matrix4& Matrix4::zero()
{
    data[0][0] = 0.0f; data[0][1] = 0.0f; data[0][2] = 0.0f; data[0][3] = 0.0f;
    data[1][0] = 0.0f; data[1][1] = 0.0f; data[1][2] = 0.0f; data[1][3] = 0.0f;
    data[2][0] = 0.0f; data[2][1] = 0.0f; data[2][2] = 0.0f; data[2][3] = 0.0f;
    data[3][0] = 0.0f; data[3][1] = 0.0f; data[3][2] = 0.0f; data[3][3] = 0.0f;

    return *this;
}

void Matrix4::log()
{
    for(int idx = 0; idx < 4; idx++)
    {
        for(int idy = 0; idy < 4; idy++)
        {
            qDebug() << data[idx][idy] << "\t";
        }
        qDebug() << "--\n";
    }
}

Vector3 Matrix4::operator *(const Vector3 vec3) const
{
    return Vector3(data[0][0] * vec3.x + data[0][1] * vec3.y + data[0][2] * vec3.z + data[0][3],
                   data[1][0] * vec3.x + data[1][1] * vec3.y + data[1][2] * vec3.z + data[1][3],
                   data[2][0] * vec3.x + data[2][1] * vec3.y + data[2][2] * vec3.z + data[2][3]);
}
