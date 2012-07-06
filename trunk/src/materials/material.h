#ifndef MATERIAL_H
#define MATERIAL_H

#include "../render/shader.h"


/*!
 * Material
 * Un material correspond à un shader et contient une structure d'attributs pour stocker ses paramètres.
 * @abstract
 */
class Material
{
public:
    Material(QString shader);
    Material(Shader* shader);

    Shader* getShader();

    virtual Shader* bind(){return shader;}

protected:
    Shader* shader;
};

#endif // MATERIAL_H
