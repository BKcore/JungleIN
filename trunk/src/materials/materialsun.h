#ifndef METERIALSUN_H
#define METERIALSUN_H

#include "material.h"
#include "../core/texture.h"


class MaterialSun : public Material
{
public:
    MaterialSun(Texture* diffuse, Texture* alpha);
    Shader* bind();

protected:
    Texture* diffuse;
    Texture* alpha;
};

#endif // METERIALSUN_H
