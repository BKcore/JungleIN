#ifndef INSTANCE_H
#define INSTANCE_H

#include "object3d.h"

class Mesh;

class Instance : public Object3D
{
public:
    Instance(Mesh* mesh, int id = 0);

    int getId();
    Mesh* getMesh();

private:
    int id;
    Mesh* mesh;
};

#endif // INSTANCE_H
