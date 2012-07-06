#include "materialsun.h"

MaterialSun::MaterialSun(Texture *diffuse, Texture *alpha) : Material("rt_sun")
{
    this->diffuse = diffuse;
    this->alpha = alpha;
}

Shader* MaterialSun::bind()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shader->bind();

    diffuse->bind();
    shader->transmitUniform("texDiffuse", diffuse);

    alpha->bind();
    shader->transmitUniform("texAlpha", alpha);

    return shader;
}
