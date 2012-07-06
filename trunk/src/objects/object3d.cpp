#include "object3d.h"
#include "../math/quaternion.h"


Object3D::Object3D()
{
    matrix.identity();
    rotation.set(0,0,0);
    scale.set(1,1,1);
    position.set(0,0,0);
    needUpdate = false;
    visible = true;
}

void Object3D::setRotation(const Vector3 &rotation)
{
    this->rotation.set(rotation.x,rotation.y,rotation.z);
    this->needUpdate=true;
}

void Object3D::setPosition(const Vector3 &position)
{
    this->position.set(position.x,position.y,position.z);
    this->needUpdate=true;
}

void Object3D::setScale(const Vector3 &scale)
{
    this->scale.set(scale.x,scale.y,scale.z);
    this->needUpdate=true;
}

void Object3D::updateMatrix()
{
    this->matrix.identity();

    Quaternion q;
    q.setFromVector(this->rotation);
    this->matrix.setRotationMatrix(q);

    this->matrix.scale(this->scale);

    this->matrix.translate(this->position);

    this->needUpdate=false;
}


void Object3D::rotate(const Vector3 &xyz)
{
    this->rotation += xyz;
    this->needUpdate=true;
}

void Object3D::translate(const Vector3 &xyz)
{
    this->position += xyz;
    this->needUpdate=true;
}

void Object3D::rotateX(float s)
{
    this->rotation.x += s;
    this->needUpdate=true;
}

void Object3D::rotateY(float s)
{
     this->rotation.y += s;
    this->needUpdate=true;
}

void Object3D::rotateZ(float s)
{
    this->rotation.z += s;
    this->needUpdate=true;
}

void Object3D::translateX(float s)
{
     this->position.x += s;
     this->needUpdate=true;
}

void Object3D::translateY(float s)
{
    this->position.y += s;
    this->needUpdate=true;
}

void Object3D::translateZ(float s)
{
    this->position.z += s;
    this->needUpdate=true;
}

void Object3D::translateRel(float s, Vector3 axis)
{
    matrix.rotateAxis(axis);
    position += axis * s;
}

void Object3D::translateRelX(float s)
{
    translateRel(s, Vector3::X);
}

void Object3D::translateRelY(float s)
{
    translateRel(s, Vector3::Y);
}

void Object3D::translateRelZ(float s)
{
    translateRel(s, Vector3::Z);
}

Matrix4& Object3D::getMatrix()
{
    if(needUpdate) updateMatrix();
    return this->matrix;
}

Vector3& Object3D::getPosition()
{
    return position;
}
