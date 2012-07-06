#ifndef CAMERA_H
#define CAMERA_H

#include "object3d.h"


/*!
 * Camera extends Object3D
 * Une camera est un objet3D disposant en plus d'une matrice de projection.
 */
class Camera : public Object3D
{
public:
    Camera();

    void lookAt(const Vector3 &_target);
    void setPerspective(float fov, float ratio, float near, float far);

    Matrix4 &getProjection();

    void update(double groundY, double delta = 1.0);
    void reset();

    void setTarget(const Vector3& _target);
    Vector3 getTarget();

    void setMouse(int x, int y);
    void setLookAccel(int x, int y);

    void setLeftKey(bool);
    void setRightKey(bool);
    void setUpKey(bool);
    void setDownKey(bool);
    void setPositionY(float y);

    void stopMouseEffect();

    void activeLook(bool);

    float getYaw();

private :
    Matrix4 projection;

    Vector3 target;

    bool look;

    bool leftKey;
    bool rightKey;
    bool upKey;
    bool downKey;

    float mouseXold;
    float mouseYold;
    float mouseX;
    float mouseY;
    float accelX;
    float accelY;

    float lookSpeed;
    float moveSpeed;
    float yaw, pitch;
    float height;
};

#endif // CAMERA_H
