#include "geometry.h"
#include "QDebug"

#include <GL/glew.h>

const unsigned int Geometry::TRIANGLES = GL_TRIANGLES;
const unsigned int Geometry::QUADS = GL_QUADS;
const unsigned int Geometry::POINTS = GL_POINTS;

Geometry::Geometry(float* vertices, int* indices,int nbVertices, int nbIndices): verticesTab(0), indicesTab(0),texCoordsTab(0), normalsTab(0)
{
    verticesTab = new float[nbVertices];
    indicesTab = new int[nbIndices];

    memcpy(verticesTab, vertices, nbVertices * sizeof(float));
    memcpy(indicesTab, indices, nbIndices * sizeof(int));

    this->verticesCount = nbVertices;
    this->indicesCount = nbIndices;

    hNormals = false;
    hTexCoords = false;

    primitive = Geometry::TRIANGLES;
}

float* Geometry::getVertices()
{
    return verticesTab;
}

int* Geometry::getIndices()
{
    return indicesTab;
}

float* Geometry::getTexCoords()
{
    return texCoordsTab;
}

 float* Geometry::getNormals()
 {
     return normalsTab;
 }

int Geometry::getVerticesCount()
{
    return verticesCount;
}

int Geometry::getIndicesCount()
{
    return indicesCount;
}

int Geometry::getTexCoordsCount()
{
    return texCoordsCount;
}

void Geometry::setTexCoords(float* texCoords)
{
    texCoordsCount = this->verticesCount/3 *2;
    texCoordsTab = new float[texCoordsCount];
    memcpy(texCoordsTab, texCoords, texCoordsCount * sizeof(float));
    hTexCoords = true;
}

void Geometry::setNormals(float* normals)
{
    normalsTab = new float[verticesCount];
    memcpy(normalsTab, normals, verticesCount * sizeof(float));
    hNormals = true;
}

bool Geometry::hasNormals()
{
    return hNormals;
}

bool Geometry::hasTexCoords()
{
    return hTexCoords;
}

void Geometry::setPrimitive(unsigned int glenum)
{
    primitive = glenum;
}

unsigned int Geometry::getPrimitive()
{
    return primitive;
}
