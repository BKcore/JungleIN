#ifndef MATERIALSHADOW_H
#define MATERIALSHADOW_H

#include "material.h"

class MaterialShadow : public Material
{
public:
    MaterialShadow();
    Shader* bind();
};

#endif // MATERIALSHADOW_H
