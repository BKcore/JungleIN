#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "../objects/mesh.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringList>

class ObjLoader
{
public:

    static Mesh* loadObj(QString fileName);


};

#endif // OBJLOADER_H
