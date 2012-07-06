#include "texture.h"

const unsigned int Texture::LINEAR = GL_LINEAR;
const unsigned int Texture::NEAREST = GL_NEAREST;
const unsigned int Texture::MIPMAP = GL_LINEAR_MIPMAP_LINEAR;

Texture::Texture()
{
    height = 0;
    width = 0;
    hasImage = false;
    format = GL_RGBA;
    gluid = 0;
    glunit = 0;
    index = 0;
    minFilter = GL_LINEAR;
    magFilter = GL_LINEAR;
    globalFormat = GL_RGBA;
}

Texture::Texture(QString path, unsigned int _index)
{
    load(path);
    gluid = 0;
    glunit = unitFromIndex(_index);
    index = _index;
    minFilter = GL_LINEAR;
    magFilter = GL_LINEAR;
    globalFormat = GL_RGBA;
}

Texture::Texture(unsigned int _index)
{
    height = 0;
    width = 0;
    hasImage = false;
    format = GL_RGBA;
    index = _index;
    glunit = unitFromIndex(_index);
    gluid = 0;
    hasImage = false;
    minFilter = GL_LINEAR;
    magFilter = GL_LINEAR;
    globalFormat = GL_RGBA;
}

Texture::~Texture()
{
    glDeleteTextures(1, &gluid);
}

void Texture::load(QString path)
{
    image = QGLWidget::convertToGLFormat(QImage(path));
    height = image.height();
    width = image.width();
    format = GL_RGBA;
    hasImage = true;
}

void Texture::setupForFramebuffer(unsigned int _width, unsigned int _height, unsigned int _format, unsigned int _globalFormat)
{
    width = _width;
    height = _height;
    format = _format;
    globalFormat = _globalFormat;
    minFilter = GL_LINEAR;
    magFilter = GL_LINEAR;
}

void Texture::setFilters(unsigned int min, unsigned int mag)
{
    minFilter = min;
    magFilter = mag;
}

void Texture::init()
{
    glActiveTexture(glunit);
    glGenTextures(1, &gluid);
    glBindTexture(GL_TEXTURE_2D, gluid);

    if(hasImage)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, globalFormat, GL_UNSIGNED_BYTE, image.bits());

        if(minFilter == Texture::MIPMAP)
            glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        if(Utils::USE_ANISO)
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, Utils::MAX_ANISO);
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, globalFormat, GL_UNSIGNED_BYTE, NULL);
        if(format == GL_DEPTH_COMPONENT)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        }
        else
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColorB);
        }
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

void Texture::bind()
{
    glActiveTexture(glunit);
    glBindTexture(GL_TEXTURE_2D, gluid);

    if(Texture::needsUpdate)
        update();
}

void Texture::update()
{
    if(Utils::USE_ANISO)
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, Utils::MAX_ANISO);
    else
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0);
}

void Texture::resize(unsigned int _width, unsigned int _height)
{
    width = _width;
    height = _height;

    if(!hasImage)
    {
        bind();
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, globalFormat, GL_UNSIGNED_BYTE, NULL);
    }
}

int Texture::getHeight()
{
    return height;
}

int Texture::getWidth()
{
    return width;
}


/*!
 * @static
 */

bool Texture::needsUpdate = false;

unsigned int Texture::unitCount = 0;

float Texture::borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
float Texture::borderColorB[] = {0.0f, 0.0f, 0.0f, 0.0f};

void Texture::resetUnit(int textureUnitOffset)
{
    unitCount = textureUnitOffset;
}

Texture Texture::fromNextUnit()
{
    return Texture(unitCount++);
}

Texture* Texture::newFromNextUnit()
{
    return new Texture(unitCount++);
}

unsigned int Texture::unitFromIndex(unsigned int index)
{
    switch(index)
    {
        case 1: return GL_TEXTURE1;
        case 2: return GL_TEXTURE2;
        case 3: return GL_TEXTURE3;
        case 4: return GL_TEXTURE4;
        case 5: return GL_TEXTURE5;
        case 6: return GL_TEXTURE6;
        case 7: return GL_TEXTURE7;
        case 8: return GL_TEXTURE8;
        case 9: return GL_TEXTURE9;
        default: return GL_TEXTURE0;
    }
}
