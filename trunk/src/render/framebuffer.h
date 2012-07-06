#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <QStringList>
#include <GL/glew.h>
#include "../core/texture.h"
#include "shader.h"

/*!
 * FrameBuffer
 * Stock un FBO et ses textures correspondantes.
 */
class FrameBuffer
{
public:
    FrameBuffer(bool storeDepth = false);
    FrameBuffer(QStringList textures, unsigned int _width = RT_SIZE_DEFAULT, unsigned int _height = RT_SIZE_DEFAULT, bool storeDepth = false);
    ~FrameBuffer();

    void clear();
    void init(int textureUnitOffset = 0, bool linearFilter = false);
    void bind();
    void unbind();
    void resize(unsigned int _width, unsigned int _height);
    void resizeViewport();

    void bindAndTransmitTextures(Shader* shader);

    unsigned int getAttachementFromIndex(unsigned int index);

    Texture *getTexture(QString name);
    unsigned int getWidth();
    unsigned int getHeight();

    static const int RT_SIZE_DEFAULT;

protected:
    unsigned int uid;

    unsigned int width;
    unsigned int height;

    bool hasDepth;
    unsigned int depthBuffer;

    QStringList texturesNames;
    QList<Texture*> textures;

    unsigned int size;
    unsigned int* drawBuffers;
};

#endif // FRAMEBUFFER_H
