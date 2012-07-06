#include "sun.h"

#include <cmath>

#define SUN_ANGLE_STEP 0.001
#define SUN_YAW_OFFSET M_PI/10.0
#define SUN_YAW_START -SUN_YAW_OFFSET
#define SUN_YAW_END M_PI+SUN_YAW_OFFSET

Sun::Sun(MaterialSun *mat) : Mesh()
{
    geometry = Geometries::quad(2.0);
    material = mat;
    light = new Light();
    lightDistance = 150.0;
    lightTargetOffset = 13;
    sunDistance = 6.0;
    yaw = M_PI/3.0;
    speed = 0.0;
}

void Sun::update(const Vector3 &positionCamera, const Vector3 &zCamera)
{
    yaw += SUN_ANGLE_STEP*speed;
    if(yaw > SUN_YAW_END) yaw = SUN_YAW_START;

    localPosition.set(std::cos(yaw), std::sin(yaw), -std::sin(yaw)/3.0);
    position.copy(positionCamera + localPosition*sunDistance);

    matrix.lookAt(position, positionCamera, Vector3::Y);

    Vector3 offsetCamera = positionCamera + zCamera*lightTargetOffset;
    light->setPosition(offsetCamera + localPosition*lightDistance);
    light->lookAt(offsetCamera);
}

void Sun::setSpeed(float s)
{
    speed = s;
}

Light* Sun::getLight()
{
    return light;
}
