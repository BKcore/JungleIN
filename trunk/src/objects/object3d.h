#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "../math/matrix4.h"
#include "../math/vector3.h"


/*!
 * Object3D
 * Représente un object 3D disposant d'une Matrix4 de transformation, et donc des Vector3 de position/rotation/scale.
 * @abstract
 */
class Object3D
{
public:

    Object3D();

    void setRotation(const Vector3&);
    void setPosition(const Vector3&);
    void setScale(const Vector3&);
    void updateMatrix();

    void rotate(const Vector3&);
    void rotateX(float);
    void rotateY(float);
    void rotateZ(float);
    void translate(const Vector3&);
    void translateX(float);
    void translateY(float);
    void translateZ(float);
    void translateRel(float, Vector3);
    void translateRelX(float);
    void translateRelY(float);
    void translateRelZ(float);

    Matrix4& getMatrix();
    Vector3& getPosition();


protected :
    Matrix4 matrix;
    Vector3 rotation;
    Vector3 position;
    Vector3 scale;

    bool needUpdate;
    bool visible;
};

#endif // OBJECT3D_H
