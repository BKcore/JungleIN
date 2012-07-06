#ifndef MATERIALBASIC_H
#define MATERIALBASIC_H

#include "material.h"

class MaterialBasic : public Material
{
public:
    MaterialBasic(const Vector3 &_color = Vector3());

    void setColor(const Vector3 &_color);
    Vector3& getColor();

    void setDiffuse(Texture* tex);
    void setAlpha(Texture* tex);

    bool hasAlpha();

    Texture* getAlpha();

    Shader* bind();

protected:
    Vector3 color;
    Texture* diffuse;
    Texture* alpha;
    bool hDiffuse;
    bool hAlpha;
};

#endif // MATERIALBASIC_H
