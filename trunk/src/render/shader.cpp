#include "shader.h"

#include "../helpers/utils.h"
#include <GL/glew.h>
#include <QDebug>
#include <QString>
#include <QMessageBox>

Shader::Shader(QString name)
{
    this->name = name;
    this->uid = -1;
    this->vertex = NULL;
    this->fragment = NULL;
}

Shader::~Shader()
{
    attributes.clear();
    uniforms.clear();
    delete [] vertex;
    delete [] fragment;
}

Shader& Shader::load(QString shaderPrefix, QStringList attributes, QStringList uniforms)
{;
    vertex = Utils::getFileContent(shaderPrefix+".vs");
    fragment = Utils::getFileContent(shaderPrefix+".fs");

    setup();
    setupLocations(attributes, uniforms);

    return *this;
}

Shader& Shader::setup()
{
    if (vertex == NULL || fragment == NULL)
    {
        QMessageBox::critical(Utils::WINDOW, "Error", "Unable to load shader '"+name+"'.");
        exit(-1);
    }

    int status, logSize;
    QByteArray log;
    unsigned int pProgram;

    pProgram = glCreateProgram();

    unsigned int vshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshader, 1, &vertex, NULL);
    glCompileShader(vshader);
    glGetShaderiv(vshader, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE)
    {
        glGetShaderiv(vshader, GL_INFO_LOG_LENGTH, &logSize);
        log.resize(logSize - 1);
        glGetShaderInfoLog(vshader, logSize, &logSize, log.data());
        QMessageBox::critical(Utils::WINDOW, "Error", "Unable to compile vertex shader of '"+name+"' :\n\n"+QString(log));
        exit(-1);
    }
    glAttachShader(pProgram, vshader);

    unsigned int fshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshader, 1, &fragment, NULL);
    glCompileShader(fshader);
    if(status != GL_TRUE)
    {
        glGetShaderiv(fshader, GL_INFO_LOG_LENGTH, &logSize);
        log.resize(logSize - 1);
        glGetShaderInfoLog(fshader, logSize, &logSize, log.data());
        QMessageBox::critical(Utils::WINDOW, "Error", "Unable to compile fragment shader of '"+name+"' :\n\n"+QString(log));
        exit(-1);
    }
    glAttachShader(pProgram, fshader);

    glLinkProgram(pProgram);
    glGetProgramiv(pProgram, GL_LINK_STATUS, &status);
    if(status != GL_TRUE)
    {
        glGetProgramiv(pProgram, GL_INFO_LOG_LENGTH, &logSize);
        log.resize(logSize - 1);
        glGetProgramInfoLog(pProgram, logSize, &logSize, log.data());
        QMessageBox::critical(Utils::WINDOW, "Error", "Unable to link program shader of '"+name+"' :\n\n"+QString(log));
        exit(-1);
    }

    uid = pProgram;

    return *this;
}

Shader& Shader::setupLocations(QStringList _attributes, QStringList _uniforms)
{
    bind();

    foreach(QString attribute, _attributes)
        attributes.insert(attribute, glGetAttribLocation(uid, attribute.toAscii()));

    foreach(QString uniform, _uniforms)
        uniforms.insert(uniform, glGetUniformLocation(uid, uniform.toAscii()));

    return *this;
}

Shader& Shader::bind()
{
    glUseProgram(uid);

    return *this;
}

QString& Shader::getName()
{
    return name;
}

unsigned int Shader::attribute(QString name)
{
    return attributes.value(name);
}

unsigned int Shader::uniform(QString name)
{
    return uniforms.value(name);
}

bool Shader::hasAttribute(QString name)
{
    return attributes.contains(name);
}

bool Shader::hasUniform(QString name)
{
    return uniforms.contains(name);
}

void Shader::transmitUniform(QString name, const Texture *tex)
{
    glUniform1i(uniforms.value(name, -1), tex->index);
}

void Shader::transmitUniform(QString name, const TextureCube *tex)
{
    glUniform1i(uniforms.value(name, -1), tex->index);
}

void Shader::transmitUniform(QString name, int i)
{
    glUniform1i(uniforms.value(name, -1), i);
}

void Shader::transmitUniform(QString name, float f)
{
    glUniform1f(uniforms.value(name, -1), f);
}

void Shader::transmitUniform(QString name, float f1, float f2)
{
    glUniform2f(uniforms.value(name, -1), f1, f2);
}

void Shader::transmitUniform(QString name, float f1, float f2, float f3)
{
    glUniform3f(uniforms.value(name, -1), f1, f2, f3);
}

void Shader::transmitUniform(QString name, const Vector3 &vec3)
{
    glUniform3f(uniforms.value(name, -1), vec3.x, vec3.y, vec3.z);
}

void Shader::transmitUniform(QString name, const Matrix3 &mat3)
{
    glUniformMatrix3fv(uniforms.value(name, -1), 1, GL_TRUE, mat3.array);
}

void Shader::transmitUniform(QString name, const Matrix4 &mat4)
{
    glUniformMatrix4fv(uniforms.value(name, -1), 1, GL_TRUE, mat4.array);
}

void Shader::transmitUniform(QString name, bool b)
{
    glUniform1i(uniforms.value(name, -1), b?1:0);
}
