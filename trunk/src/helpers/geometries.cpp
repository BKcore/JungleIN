#include "geometries.h"
#include <GL/glew.h>
#include <QDebug>

Geometry* Geometries::cube(float size)
{
    float vertices[] = {
      -size,  size,  size,
      -size, -size,  size,
       size, -size,  size,
       size,  size,  size,
      -size,  size, -size,
      -size, -size, -size,
       size, -size, -size,
       size,  size, -size,
    };

     int indices[] = {
        0, 1, 2, 3,
        3, 2, 6, 7,
        7, 6, 5, 4,
        4, 5, 1, 0,
        0, 3, 7, 4,
        1, 2, 6, 5,
    };

    Geometry* g = new Geometry(vertices, indices, 24, 24);
    g->setPrimitive(GL_QUADS);

    return g;
}


Geometry* Geometries::quad(float size)
{
    float vertices[] = {
      -size,  size,  0.0,
      -size, -size,  0.0,
       size, -size,  0.0,
       size,  size,  0.0
    };

    float texcoords[] = {
        0.0, 1.0,
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0
    };

    int indices[] = {0, 1, 2, 3};

    Geometry* g = new Geometry(vertices, indices, 12, 4);
    g->setTexCoords(texcoords);
    g->setPrimitive(GL_QUADS);

    return g;
}


Geometry* Geometries::point()
{
    float tab_vertices[] = {0, 0, 0};
    int tab_indices[] = {0};

    Geometry* g = new Geometry(tab_vertices, tab_indices, 3, 1);

    return g;

}

