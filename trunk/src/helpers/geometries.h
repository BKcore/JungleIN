#ifndef GEOMETRIES_H
#define GEOMETRIES_H

#include "../core/geometry.h"

class Geometries
{
public:
    static Geometry* cube(float size = 1.0);
    static Geometry* quad(float size);
    static Geometry* point();
};

#endif // GEOMETRIES_H
