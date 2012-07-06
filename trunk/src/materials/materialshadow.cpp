#include "materialshadow.h"

MaterialShadow::MaterialShadow() : Material("rt_shadow")
{
}

Shader* MaterialShadow::bind()
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);

    shader->bind();

    return shader;
}
