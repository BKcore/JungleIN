#include "shadowbuffer.h"

ShadowBuffer::ShadowBuffer(QString texname, int width, int height)
{
    this->width = width;
    this->height = height;
    uid = 0;
    texturesNames = QStringList();
    texturesNames.append(texname);
    textures = QList<Texture*>();
}

void ShadowBuffer::init(unsigned int textureUnitOffset)
{
    glGenFramebuffers(1, &uid);
    glBindFramebuffer(GL_FRAMEBUFFER, uid);

    size = 1;

    drawBuffers = new unsigned int[size];

    Texture::resetUnit(textureUnitOffset);
    Texture* tex = Texture::newFromNextUnit();
    tex->setupForFramebuffer(width, height, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT);
    tex->setFilters(Texture::LINEAR, Texture::LINEAR);
    tex->init();
    tex->bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex->gluid, 0);

    textures.append(tex);

    drawBuffers[0] = GL_NONE;

    glDrawBuffers(size, drawBuffers);
    unbind();
}
