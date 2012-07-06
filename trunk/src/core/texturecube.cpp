#include "texturecube.h"

#include <QDebug>

/*!
 * Pathes order : px, nx, py, ny, pz, nz
 */
TextureCube::TextureCube(QString texDir, QString ext, unsigned int _index, unsigned int _size)
{
    gluid = 0;
    glunit = Texture::unitFromIndex(_index);
    index = _index;
    size = _size;
    load(texDir);
}

TextureCube::~TextureCube()
{
    glDeleteTextures(1, &gluid);
    images.clear();
}

void TextureCube::load(QString texDir, QString ext)
{
    images.append(QGLWidget::convertToGLFormat(QImage(texDir+"px"+ext)));
    images.append(QGLWidget::convertToGLFormat(QImage(texDir+"nx"+ext)));
    images.append(QGLWidget::convertToGLFormat(QImage(texDir+"py"+ext)));
    images.append(QGLWidget::convertToGLFormat(QImage(texDir+"ny"+ext)));
    images.append(QGLWidget::convertToGLFormat(QImage(texDir+"pz"+ext)));
    images.append(QGLWidget::convertToGLFormat(QImage(texDir+"nz"+ext)));
}

void TextureCube::init()
{
    if(images.size() != 6)
    {
        qDebug()<<"Incomplete cube map textures.";
        return;
    }

    glActiveTexture(glunit);
    glEnable(GL_TEXTURE_CUBE_MAP);
    glGenTextures(1, &gluid);

    glBindTexture(GL_TEXTURE_CUBE_MAP, gluid);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, images.at(0).bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, images.at(1).bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, images.at(2).bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, images.at(3).bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, images.at(4).bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, images.at(5).bits());
}

void TextureCube::bind()
{
    glActiveTexture(glunit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, gluid);
}
