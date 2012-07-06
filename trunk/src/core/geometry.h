#ifndef GEOMETRY_H
#define GEOMETRY_H


/*!
 * Geometry
 * Structure de données permettant de stocker les tableaux de vertices, indices, etc.
 */
class Geometry
{
public:
    static const unsigned int TRIANGLES;
    static const unsigned int QUADS;
    static const unsigned int POINTS;

    Geometry(float* vertices, int* indices,int nbVertices, int nbIndices);

    float* getVertices();
    int* getIndices();
    float* getTexCoords();
    float* getNormals();

    int getVerticesCount();
    int getIndicesCount();
    int getTexCoordsCount();

    void setTexCoords(float* texCoords);
    void setNormals(float* normals);

    void setPrimitive(unsigned int glenum);
    unsigned int getPrimitive();

    bool hasNormals();
    bool hasTexCoords();


private:
    float* verticesTab;
    int* indicesTab;
    float* texCoordsTab;
    float* normalsTab;

    unsigned int primitive;

    int verticesCount;
    int indicesCount;
    int texCoordsCount;

    bool hNormals;
    bool hTexCoords;


};

#endif // GEOMETRY_H
