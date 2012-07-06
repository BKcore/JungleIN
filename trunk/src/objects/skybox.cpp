#include "skybox.h"
#include "../helpers/geometries.h"
#include <QDebug>
SkyBox::SkyBox(MaterialSkyBox* mat) : Mesh()
{
    geometry = Geometries::cube();
    material = mat;
}
