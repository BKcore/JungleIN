#include "instance.h"

#include "mesh.h"

Instance::Instance(Mesh* mesh, int id) : Object3D()
{
    this->id = id;
    this->mesh = mesh;
}

int Instance::getId()
{
    return id;
}

Mesh* Instance::getMesh()
{
    return mesh;
}
