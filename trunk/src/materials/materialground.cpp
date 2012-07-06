#include "materialground.h"

MaterialGround::MaterialGround(Texture *moss, Texture *earth, Texture *shatter, Texture *mossNormal, Texture *earthNormal, Texture *shatterNormal) : Material("rt_ground")
{
    this->moss = moss;
    this->earth = earth;
    this->shatter = shatter;
    this->mossNormal = mossNormal;
    this->earthNormal = earthNormal;
    this->shatterNormal = shatterNormal;
    size = (float)shatter->getWidth();
}

Shader* MaterialGround::bind()
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);

    shader->bind();
    shader->transmitUniform("tileSize", size);
    shader->transmitUniform("heightRange", heightRange);

    moss->bind();
    earth->bind();
    shatter->bind();
    mossNormal->bind();
    earthNormal->bind();
    shatterNormal->bind();
    shader->transmitUniform("texMoss", moss);
    shader->transmitUniform("texEarth", earth);
    shader->transmitUniform("texShatter", shatter);
    shader->transmitUniform("texNormalMoss", mossNormal);
    shader->transmitUniform("texNormalEarth", earthNormal);
    shader->transmitUniform("texNormalShatter", shatterNormal);

    return shader;
}

void MaterialGround::setHeightRange(float f)
{
    heightRange = f;
}
