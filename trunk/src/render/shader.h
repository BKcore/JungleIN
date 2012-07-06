#ifndef SHADER_H
#define SHADER_H

#include <QString>
#include <QHash>
#include "../math/vector3.h"
#include "../math/matrix3.h"
#include "../math/matrix4.h"
#include "../core/texture.h"
#include "../core/texturecube.h"

/*!
 * Shader
 * Stock un glProgram (vertex+fragment).
 * Utiliser bind pour utiliser le shader lors du rendu.
 * Utiliser attribute(string) et uniform(string) pour accéder aux locations.
 */
class Shader
{
public:
    Shader(QString name);
    ~Shader();

    Shader& load(QString shader, QStringList attributes, QStringList uniforms);
    Shader& bind();
    Shader& setup();
    Shader& setupLocations(QStringList _attributes, QStringList _uniforms);

    QString& getName();

    unsigned int attribute(QString name);
    unsigned int uniform(QString name);

    bool hasAttribute(QString name);
    bool hasUniform(QString name);

    void transmitUniform(QString name, const Texture* tex);
    void transmitUniform(QString name, const TextureCube* tex);
    void transmitUniform(QString name, int i);
    void transmitUniform(QString name, float f);
    void transmitUniform(QString name, float f1, float f2);
    void transmitUniform(QString name, float f1, float f2, float f3);
    void transmitUniform(QString name, const Vector3 &vec3);
    void transmitUniform(QString name, const Matrix3 &mat3);
    void transmitUniform(QString name, const Matrix4 &mat4);
    void transmitUniform(QString name, bool b);

private:
    QString name;
    unsigned int uid;
    const char* vertex;
    const char* fragment;

    QHash<QString, unsigned int> attributes;
    QHash<QString, unsigned int> uniforms;
};

#endif // SHADER_H
