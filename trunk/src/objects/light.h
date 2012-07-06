#ifndef LIGHT_H
#define LIGHT_H

#include "../math/vector3.h"
#include "../math/matrix4.h"
#include <QString>

/*!
 * Light
 * Une lumière définie par une position et un vecteur d'orientation
 */
class Light
{
public:
    Light(Vector3 position = Vector3(0,1,0),Vector3 direction = Vector3(0,-1,0), Vector3 intensity = Vector3(1,1,1));

    void setDirection(const Vector3 &direction);
    Vector3& getDirection();
    void lookAt(const Vector3 &target);

    Vector3& getIntensity();
    void setIntensity(const Vector3 &intensity);

    Vector3& getPosition();
    void setPosition(const Vector3 &position);

    Matrix4& getProjMatrix();
    Matrix4& getProjMatrixCascade();
    Matrix4& getViewMatrix();
    Matrix4& getTextureProjMatrix(const Matrix4& modelMatrix);
    Matrix4& getTextureProjMatrixCascade(const Matrix4& modelMatrix);

    void resize(float ratio);
    void setSize(float s);

private:
    Vector3 intensity;
    Vector3 position;
    Vector3 direction;

    float size, sizeCascade;

    Matrix4 viewMatrix;
    Matrix4 projMatrix;
    Matrix4 biasMatrix;
    Matrix4 textureProjMatrix;
    Matrix4 projMatrixCascade;
    Matrix4 textureProjMatrixCascade;


};

#endif // LIGHT_H
