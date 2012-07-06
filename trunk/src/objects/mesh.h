#ifndef MESH_H
#define MESH_H

#include "object3d.h"
#include "../materials/material.h"
#include "../core/geometry.h"
#include "instance.h"
#include <QList>


/*!
 * Mesh extends Object3D
 * Un object 3D contenant une géométrie et un matérial.
 */
class Mesh : public Object3D
{
public:
    Mesh();
    Mesh(Geometry* geometry, Material* material);
    ~Mesh();

    void initVBO();
    void drawWithVBO();
    void debugDrawWithVBO();

    Geometry* getGeometry();
    Material* getMaterial();

    void castsShadows(bool active);
    bool castsShadows();

    Instance* newInstance();
    void removeInstance(int id);
    void clearInstances();
    Instance* getInstance(int id);
    QList<Instance*>& getInstances();
    float getScaleRdn();
    void setScaleRdn(float sRdn);
    float getHeightRdn();
    void setHeightRdn(float height);
    float getPourcentage();
    void setPourcentage(float pct);
    float getRangeScale();
    void setRangeScale(float range);

    void setInstanceType(unsigned int i);
    unsigned int getInstanceType();

    bool isInstance();

    static const unsigned int INSTANCE_NONE;
    static const unsigned int INSTANCE_PALM;
    static const unsigned int INSTANCE_HTREE;
    static const unsigned int INSTANCE_BTREE;
    static const unsigned int INSTANCE_GPALM;
    static const unsigned int INSTANCE_BUSH;
    static const unsigned int INSTANCE_ROCK;

protected :
    Geometry* geometry;
    Material* material;

    unsigned int vertices;
    unsigned int indices;
    unsigned int normals;
    unsigned int texcoords;

    bool hasNormals;
    bool hasTexCoords;

    bool castShadows;

    unsigned int locVertices;
    unsigned int locNormals;
    unsigned int locTexCoords;

    float scaleRdn;
    float rangeScale;
    float heightRdn;
    float pourcentage;
    unsigned int instanceType;

    QList<Instance*> instances;
};

#endif // MESH_H
