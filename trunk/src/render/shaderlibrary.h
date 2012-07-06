#ifndef SHADERLIBRARY_H
#define SHADERLIBRARY_H

#include <QHash>
#include "shader.h"

/*!
 * ShaderLibrary
 * Sert à stocker les pointeurs sur les différent shaders.
 * Utiliser ShaderLibrary::addShader pour charger un nouveau shader.
 * @static
 */
class ShaderLibrary
{
public:
    static Shader* getShader(QString name);
    static Shader* addShader(QString name, QString shaderPrefix, QStringList attributes, QStringList uniforms);
    static void clear();

private:
    static QHash<QString, Shader*> shaders;
};

#endif // SHADERLIBRARY_H
