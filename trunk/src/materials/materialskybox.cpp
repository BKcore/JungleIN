#include "materialskybox.h"
#include <QDebug>

MaterialSkyBox::MaterialSkyBox(TextureCube *textureCube) : Material("rt_skybox")
{
    cubemap = textureCube;
    cubemap->init();
}

Shader* MaterialSkyBox::bind()
{
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    shader->bind();
    cubemap->bind();
    shader->transmitUniform("texCube", cubemap);

    return shader;
}
