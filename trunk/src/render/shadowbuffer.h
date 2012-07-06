#ifndef SHADOWBUFFER_H
#define SHADOWBUFFER_H

#include "framebuffer.h"

class ShadowBuffer : public FrameBuffer
{
public:
    ShadowBuffer(QString texname, int width, int height);
    void init(unsigned int textureUnitOffset = 0);
};

#endif // SHADOWBUFFER_H
