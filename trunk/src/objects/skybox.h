#ifndef SKYBOX_H
#define SKYBOX_H

#include "mesh.h"
#include "../materials/materialskybox.h"

class SkyBox : public Mesh
{
public:
    SkyBox(MaterialSkyBox* mat);
};

#endif // SKYBOX_H
