#ifndef PATH_H
#define PATH_H

#include <QString>
#include "QImage"

class Ground;

class Path
{
public:
    Path(QString file);
    bool validate(double x, double z);

private :
    int width, height;
    QImage image;
};

#endif // PATH_H
