#ifndef MATERIALSKYBOX_H
#define MATERIALSKYBOX_H

#include "material.h"
#include "../core/texturecube.h"

class MaterialSkyBox : public Material
{
public:
    MaterialSkyBox(TextureCube* textureCube);

    Shader* bind();

private:
    TextureCube* cubemap;
};

#endif // MATERIALSKYBOX_H
