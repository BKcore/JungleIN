#ifndef SUN_H
#define SUN_H

#include "mesh.h"
#include "light.h"
#include "../materials/materialsun.h"
#include "../helpers/geometries.h"
#include "../math/vector3.h"

class Sun : public Mesh
{

public:
    Sun(MaterialSun* mat);

    void update(const Vector3 &positionCamera, const Vector3 &zCamera);

    void setSpeed(float s);
    Light* getLight();

private:
    Light* light;
    float lightDistance;
    float lightTargetOffset;
    float sunDistance;
    Vector3 localPosition;
    float yaw;
    float speed;
};

#endif // SUN_H
