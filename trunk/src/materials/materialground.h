#ifndef MATERIALGROUND_H
#define MATERIALGROUND_H

#include "material.h"

class MaterialGround : public Material
{
public:
    MaterialGround(Texture* moss, Texture* earth, Texture* shatter, Texture* mossNormal, Texture* earthNormal, Texture* shatterNormal);

    Shader* bind();

    void setHeightRange(float f);

protected:
    float size;
    float heightRange;

    Texture* moss;
    Texture* earth;
    Texture* shatter;
    Texture* mossNormal;
    Texture* earthNormal;
    Texture* shatterNormal;
};

#endif // MATERIALGROUND_H
