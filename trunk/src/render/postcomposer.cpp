#include "postcomposer.h"

#include "shaderlibrary.h"
#include "../helpers/utils.h"
#include <GL/glew.h>
#include <QDebug>

PostComposer::PostComposer(FrameBuffer *inputFBO)
{
    width = inputFBO->getWidth();
    height = inputFBO->getHeight();
    widthf = (float)width;
    heightf = (float)height;
    finalRenderWidth = width;
    finalRenderHeight = height;

    halfBuffersRatio = 2;

    inputBuffer = inputFBO;
    readBuffer = new FrameBuffer(QStringList()<<"texScene", width, height, false);
    readBuffer->init(0, true);
    writeBuffer = new FrameBuffer(QStringList()<<"texScene", width, height, false);
    writeBuffer->init(0, true);
    readHalfBuffer = new FrameBuffer(QStringList()<<"texScene", width/halfBuffersRatio, height/halfBuffersRatio, false);
    readHalfBuffer->init(1, true);
    writeHalfBuffer = new FrameBuffer(QStringList()<<"texScene", width/halfBuffersRatio, height/halfBuffersRatio, false);
    writeHalfBuffer->init(1, true);

    quad = new SSQuad();
    quad->init();

    shaderCompose = ShaderLibrary::getShader("ss_compose");
    shaderDisplay = ShaderLibrary::getShader("ss_display");
    shaderFXAA = ShaderLibrary::getShader("ss_fxaa");
    shaderLenseFlare1 = ShaderLibrary::getShader("ss_lenseflare_p1");
    shaderLenseFlare2 = ShaderLibrary::getShader("ss_lenseflare_p2");
    shaderLenseFlare3 = ShaderLibrary::getShader("ss_lenseflare_p3");
    shaderBlurLinearH = ShaderLibrary::getShader("ss_blur_linearh");
    shaderBlurLinearV = ShaderLibrary::getShader("ss_blur_linearv");
    shaderDistortion = ShaderLibrary::getShader("ss_distortion");
    shaderGodrays1 = ShaderLibrary::getShader("ss_godrays_p1");
    shaderGodrays2 = ShaderLibrary::getShader("ss_godrays_p2");
    shaderBloom1 = ShaderLibrary::getShader("ss_bloom_p1");
    shaderBloom2 = ShaderLibrary::getShader("ss_bloom_p2");

    doFXAA = true;
    doDistord = false;
    doLenseFlares = false;
    doGodrays = true;
    doBloom = true;

    //gammaRGB = Vector3(2.2, 2.2, 2.2);
    gammaRGB = Vector3(1.0, 1.0, 1.0);

    flareThreshold = Vector3(0.5,0.5,0.5);
    flareSamples = 12;
    flareDispersal = 0.10;
    flareHaloWidth = 0.22;
    flareChromaDispertion = Vector3(1.02,1.0,0.98);
    flareIntensity = 1.0;
    flareDirt = new Texture("resources/maps/post/lensdirt_highc.jpg", 2);
    flareDirt->init();
}

void PostComposer::swapBuffers()
{
    FrameBuffer* tmp = readBuffer;
    readBuffer = writeBuffer;
    writeBuffer = tmp;
}

void PostComposer::swapHalfBuffers()
{
    FrameBuffer* tmp = readHalfBuffer;
    readHalfBuffer = writeHalfBuffer;
    writeHalfBuffer = tmp;
}

void PostComposer::render()
{
    compose();

    if(doFXAA) passFXAA();
    if(doBloom) passBloom();
    if(doLenseFlares) passLenseFlare();
    if(doGodrays) passGodrays();
    if(doDistord) passDistortion();

    display();
}

void PostComposer::compose()
{
    readBuffer->bind();

    glClear(GL_COLOR_BUFFER_BIT);

    shaderCompose->bind();

    inputBuffer->bindAndTransmitTextures(shaderCompose);

    quad->draw(shaderCompose->attribute("position"));

    readBuffer->unbind();
}

void PostComposer::passFXAA()
{
    writeBuffer->bind();

    glClear(GL_COLOR_BUFFER_BIT);

    shaderFXAA->bind();
    shaderFXAA->transmitUniform("resolution", 1/widthf, 1/heightf);

    readBuffer->bindAndTransmitTextures(shaderFXAA);

    quad->draw(shaderFXAA->attribute("position"));

    writeBuffer->unbind();

    swapBuffers();
}

void PostComposer::passDistortion()
{
    writeBuffer->bind();

    glClear(GL_COLOR_BUFFER_BIT);

    shaderDistortion->bind();
    shaderFXAA->transmitUniform("resolution", 1/widthf, 1/heightf);

    readBuffer->bindAndTransmitTextures(shaderDistortion);

    quad->draw(shaderDistortion->attribute("position"));

    writeBuffer->unbind();

    swapBuffers();
}

/*!
 * Based on a Lense flare tutorial by http://www.john-chapman.net/content.php?id=18
 */
void PostComposer::passLenseFlare()
{
    // Pass 1 : Threshold + downsample + flip
    writeHalfBuffer->resizeViewport();
    writeHalfBuffer->bind();

    glClear(GL_COLOR_BUFFER_BIT);

    shaderLenseFlare1->bind();
    shaderLenseFlare1->transmitUniform("flareThreshold", flareThreshold);

    //readBuffer->bindAndTransmitTextures(shaderLenseFlare1);
    Texture* thresh = inputBuffer->getTexture("texThreshold");
    thresh->bind();
    shaderLenseFlare1->transmitUniform("texScene", thresh);

    quad->draw(shaderLenseFlare1->attribute("position"));

    writeHalfBuffer->unbind();

    swapHalfBuffers();

    // Pass 1b : Pre-blur
    if(Utils::QUALITY == 1) passBlurLinear(true);

    // Pass 2 : Flaring
    writeHalfBuffer->bind();

    glClear(GL_COLOR_BUFFER_BIT);

    shaderLenseFlare2->bind();
    shaderLenseFlare2->transmitUniform("flareSamples", flareSamples);
    shaderLenseFlare2->transmitUniform("flareDispersal", flareDispersal);
    shaderLenseFlare2->transmitUniform("flareHaloWidth", flareHaloWidth);
    shaderLenseFlare2->transmitUniform("flareChromaDispertion", flareChromaDispertion);

    readHalfBuffer->bindAndTransmitTextures(shaderLenseFlare2);

    quad->draw(shaderLenseFlare2->attribute("position"));

    writeHalfBuffer->unbind();

    swapHalfBuffers();

    // Pass 3 : Bluring (fast gaussian)
    if(Utils::QUALITY == 1) passBlurLinear(true);

    // Pass 4 : Upsample + blur + compose
    writeBuffer->resizeViewport();
    writeBuffer->bind();

    glClear(GL_COLOR_BUFFER_BIT);

    shaderLenseFlare3->bind();
    Texture* flareTex = readHalfBuffer->getTexture("texScene");
    flareTex->bind();
    shaderLenseFlare3->transmitUniform("texFlare", flareTex);
    flareDirt->bind();
    shaderLenseFlare3->transmitUniform("texDirt", flareDirt);
    shaderLenseFlare3->transmitUniform("flareIntensity", flareIntensity);

    readBuffer->bindAndTransmitTextures(shaderLenseFlare3);

    quad->draw(shaderLenseFlare3->attribute("position"));

    writeBuffer->unbind();

    swapBuffers();
}

void PostComposer::passGodrays()
{
    // Pass 1 : downsample
    writeHalfBuffer->resizeViewport();
    writeHalfBuffer->bind();

    glClear(GL_COLOR_BUFFER_BIT);

    shaderCompose->bind();
    Texture* thresh = inputBuffer->getTexture("texThreshold");
    thresh->bind();
    shaderCompose->transmitUniform("texScene", thresh);

    quad->draw(shaderGodrays1->attribute("position"));

    writeHalfBuffer->unbind();

    swapHalfBuffers();

    // Pass 1.b : blur
    passBlurLinear(true);


    // Pass 2 : rays
    writeHalfBuffer->resizeViewport();
    writeHalfBuffer->bind();

    glClear(GL_COLOR_BUFFER_BIT);

    shaderGodrays1->bind();
    shaderGodrays1->transmitUniform("lightPos", lightPosScreen);

    readHalfBuffer->bindAndTransmitTextures(shaderGodrays1);

    quad->draw(shaderGodrays1->attribute("position"));

    writeHalfBuffer->unbind();

    swapHalfBuffers();

    // Pass 1b : Pre-blur
    //if(Utils::QUALITY == 1) passBlurLinear(true);

    // Pass 3 : compose + upsample
    writeBuffer->resizeViewport();
    writeBuffer->bind();

    glClear(GL_COLOR_BUFFER_BIT);

    shaderGodrays2->bind();
    Texture* base = readBuffer->getTexture("texScene");
    base->bind();
    shaderGodrays2->transmitUniform("texScene", base);
    Texture* godrays = readHalfBuffer->getTexture("texScene");
    godrays->bind();
    shaderGodrays2->transmitUniform("texGodrays", godrays);

    quad->draw(shaderGodrays2->attribute("position"));

    writeBuffer->unbind();

    swapBuffers();
}

void PostComposer::passBloom()
{
    // Pass 1 : downsample
    writeHalfBuffer->resizeViewport();
    writeHalfBuffer->bind();

    glClear(GL_COLOR_BUFFER_BIT);

    shaderBloom1->bind();
    readBuffer->bindAndTransmitTextures(shaderBloom1);

    quad->draw(shaderBloom1->attribute("position"));

    writeHalfBuffer->unbind();

    swapHalfBuffers();

    // Pass 1.b : blur
    passBlurLinear(true);


    // Pass 2 : compose + upsample
    writeBuffer->resizeViewport();
    writeBuffer->bind();

    glClear(GL_COLOR_BUFFER_BIT);

    shaderBloom2->bind();
    Texture* base = readBuffer->getTexture("texScene");
    base->bind();
    shaderBloom2->transmitUniform("texScene", base);
    Texture* bloom = readHalfBuffer->getTexture("texScene");
    bloom->bind();
    shaderBloom2->transmitUniform("texBloom", bloom);

    quad->draw(shaderBloom2->attribute("position"));

    writeBuffer->unbind();

    swapBuffers();
}

/*!
 * Fast gaussian approximation blur based on http://rastergrid.com/blog/2010/09/efficient-gaussian-blur-with-linear-sampling/
 */
void PostComposer::passBlurLinear(bool useHalf)
{
    float res = useHalf ? 2.0 : 1.0;

    FrameBuffer* inBuffer = useHalf ? readHalfBuffer : readBuffer;
    FrameBuffer* outBuffer = useHalf ? writeHalfBuffer : writeBuffer;

    // Vertical
    outBuffer->bind();

    glClear(GL_COLOR_BUFFER_BIT);

    shaderBlurLinearV->bind();
    shaderBlurLinearV->transmitUniform("resolution", res/widthf, res/heightf);

    inBuffer->bindAndTransmitTextures(shaderBlurLinearV);

    quad->draw(shaderBlurLinearV->attribute("position"));

    outBuffer->unbind();

    // Swap buffers
    FrameBuffer* tmp = inBuffer;
    inBuffer = outBuffer;
    outBuffer = tmp;

    // Horizontal
    outBuffer->bind();

    glClear(GL_COLOR_BUFFER_BIT);

    shaderBlurLinearH->bind();
    shaderBlurLinearH->transmitUniform("resolution", res/widthf, res/heightf);

    inBuffer->bindAndTransmitTextures(shaderBlurLinearH);

    quad->draw(shaderBlurLinearH->attribute("position"));

    outBuffer->unbind();
}

void PostComposer::display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glViewport(0, 0, finalRenderWidth, finalRenderHeight);

    shaderDisplay->bind();

    readBuffer->bindAndTransmitTextures(shaderDisplay);

    shaderDisplay->transmitUniform("aspect", widthf/heightf);

    quad->draw(shaderDisplay->attribute("position"));
}

void PostComposer::debugQuad(Texture* tex)
{
    glClear(GL_COLOR_BUFFER_BIT);

    shaderCompose->bind();

    tex->bind();
    shaderCompose->transmitUniform("texScene", tex);

    quad->draw(shaderCompose->attribute("position"));
}

void PostComposer::resize(unsigned int _width, unsigned int _height)
{
    width = _width;
    height = _height;
    widthf = (float)_width;
    heightf = (float)_height;
    finalRenderWidth = width;
    finalRenderHeight = height;
    halfBuffersRatio = Utils::QUALITY == 1 ? 3 : 4;
    unsigned int halfwidth = width/halfBuffersRatio;
    unsigned int halfheight = height/halfBuffersRatio;

    readBuffer->resize(width, height);
    writeBuffer->resize(width, height);
    readHalfBuffer->resize(halfwidth, halfheight);
    writeHalfBuffer->resize(halfwidth, halfheight);
}

void PostComposer::resizeHalfBuffers()
{
    halfBuffersRatio = Utils::QUALITY == 1 ? 3 : 4;
    unsigned int halfwidth = width/halfBuffersRatio;
    unsigned int halfheight = height/halfBuffersRatio;
    readHalfBuffer->resize(halfwidth, halfheight);
    writeHalfBuffer->resize(halfwidth, halfheight);
}

void PostComposer::toggleFXAA(bool active)
{
    doFXAA = active;
}

void PostComposer::toggleDistord(bool active)
{
    doDistord = active;
}

void PostComposer::toggleLenseFlares(bool active)
{
    doLenseFlares = active;
}

void PostComposer::toggleGodrays(bool active)
{
    doGodrays = active;
}

void PostComposer::toggleBloom(bool active)
{
    doBloom = active;
}

void PostComposer::setFlareDispersal(float value)
{
    flareDispersal = value;
}

void PostComposer::setFlareIntensity(float value)
{
    flareIntensity = value;
}

void PostComposer::setGamma(float value)
{
    gammaRGB.set(value, value, value);
}

void PostComposer::setLightPosScreen(const Vector3 &pos)
{
    lightPosScreen.copy(pos);
    //qDebug()<<lightPosScreen.toString();
}

void PostComposer::setFinalRenderSize(int w, int h)
{
    finalRenderWidth = w;
    finalRenderHeight = h;
}
