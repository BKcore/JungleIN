#ifndef RENDERER_H
#define RENDERER_H

#include <QElapsedTimer>
#include <QCursor>
#include <QStack>
#include <QDebug>
#include <cmath>

#include "../math/matrix4.h"
#include "../helpers/utils.h"
#include "../core/texturecube.h"

#include "../materials/materialbasic.h"
#include "../materials/materialshadow.h"

#include "../render/shaderlibrary.h"
#include "../render/framebuffer.h"
#include "../render/shadowbuffer.h"
#include "../render/postcomposer.h"

#include "../objects/mesh.h"
#include "../objects/ssquad.h"
#include "../objects/camera.h"
#include "../objects/ground.h"
#include "../objects/scene.h"
#include "../objects/skybox.h"
#include "../objects/sun.h"

class Renderer
{
public:
    Renderer();

    void setScene(Scene* s);

    void init(Scene* _scene, unsigned int w, unsigned int h);
    void resize(unsigned int w, unsigned int h);
    void loadShaders();

    void start();
    void stop();
    void render();
    void renderShadow();

    void drawSky();
    void drawSun();
    void drawGround();
    void drawMeshes();
    void drawMeshesShadow();

    PostComposer* getPostComposer();

    void toggleShadowCascade(bool active);
    void setRatio(float r);

private:

    void pushMatrix(const Matrix4& mat);
    void popMatrix();

    bool cull(Instance *m, float offset = 0.0);

    void calcMVP();
    void transmitShadowMatrix();
    void transmitMVP();
    void transmitNormalMatrix();
    void transmitViewMatrix();

    QElapsedTimer timer;
    float delta;
    bool active;

    Scene* scene;
    unsigned int width, height;
    unsigned int finalWidth, finalHeight;
    float ratio;

    FrameBuffer* mainFBO;
    ShadowBuffer* shadowFBO;
    ShadowBuffer* shadowFBOCascade;
    MaterialShadow* shadowMat;
    PostComposer* postComposer;

    bool useShadowCascade;

    QStack<Matrix4> xform;
    Matrix4 matrixProj,
            matrixView,
            matrixModel;

    // Buffers
    Camera* __camera;
    Material* __material;
    Shader* __shader;
    SkyBox* __skybox;
    Sun* __sun;
    Ground* __ground;
    Matrix4 __mvp,
            __mv;
    Vector3 __lightDir;
    unsigned int
        __locPosition,
        __locColor,
        __locNormal,
        __locTexcoord,
        __locMVP;
};

#endif // RENDERER_H
