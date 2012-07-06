#include "materialbasic.h"
#include <QDebug>

MaterialBasic::MaterialBasic(const Vector3 &_color) : Material("rt_basic")
{
    color.copy(_color);
    hDiffuse = false;
    hAlpha = false;
}

Shader* MaterialBasic::bind()
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);

    shader->bind();

    if(hDiffuse)
    {
        diffuse->bind();
        shader->transmitUniform("texDiffuse", diffuse);
    }

    if(hAlpha)
    {
        alpha->bind();
        shader->transmitUniform("texAlpha", alpha);
    }

    return shader;
}


void MaterialBasic::setColor(const Vector3 &_color)
{
    color.copy(_color);
}

Vector3& MaterialBasic::getColor()
{
    return color;
}

void MaterialBasic::setDiffuse(Texture* tex)
{
    diffuse = tex;
    hDiffuse = true;
}

void MaterialBasic::setAlpha(Texture* tex)
{
    alpha = tex;
    hAlpha = true;
}

bool MaterialBasic::hasAlpha()
{
    return hAlpha;
}

Texture* MaterialBasic::getAlpha()
{
    return alpha;
}
