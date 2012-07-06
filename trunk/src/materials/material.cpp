#include "material.h"
#include "../render/shaderlibrary.h"

Material::Material(QString shader)
{
    this->shader = ShaderLibrary::getShader(shader);

}

Material::Material(Shader* shader)
{
    this->shader = shader;
}

Shader* Material::getShader()
{
    return this->shader;
}
