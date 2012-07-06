#include "mainwindow.h"
#include "../helpers/utils.h"
#include <QDebug>

MainWindow::MainWindow()
{
    Utils::MAIN = this;

    setGLFormat();
    initPaneGL();
    initPaneParam();

    resize(1280, 700);
}

void MainWindow::setGLFormat()
{
    QGLFormat format;
    format.setProfile(QGLFormat::CoreProfile);
    format.setDoubleBuffer(true);
    format.setDepth(true);
    format.setRgba(true);
    //format.setVersion(4, 0);
    QGLFormat::setDefaultFormat(format);
}

void MainWindow::initPaneGL()
{
    paneGL = new Window();
    setCentralWidget(paneGL);
}

void MainWindow::initPaneParam()
{
    dock = new QDockWidget("Parameters", this);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    paneParams = new QWidget;
    dock->setWidget(paneParams);

    // Global quality
    QSlider* qualitySlider = new QSlider(Qt::Horizontal);
    qualitySlider->setRange(0, 1);
    qualitySlider->setValue(1);

    QVBoxLayout* layoutQuality = new QVBoxLayout;
    layoutQuality->addWidget(qualitySlider);

    QGroupBox* groupQuality = new QGroupBox("Effects quality");
    groupQuality->setLayout(layoutQuality);

    // Post effects
    QPushButton* postBtnFXAA = new QPushButton("FXAA Edge Smoothing");
    postBtnFXAA->setCheckable(true);
    postBtnFXAA->setChecked(true);

    QPushButton* postBtnCascade = new QPushButton("HQ Cascading Shadows");
    postBtnCascade->setCheckable(true);
    postBtnCascade->setChecked(true);

    QPushButton* postBtnAniso = new QPushButton("Anisotropic Filtering");
    postBtnAniso->setCheckable(true);
    postBtnAniso->setChecked(true);

    QPushButton* postBtnGodrays = new QPushButton("Godrays");
    postBtnGodrays->setCheckable(true);
    postBtnGodrays->setChecked(true);

    QPushButton* postBtnBloom = new QPushButton("Bloom HDRA");
    postBtnBloom->setCheckable(true);
    postBtnBloom->setChecked(true);

    QPushButton* postBtnFlares = new QPushButton("Lense Flares");
    postBtnFlares->setCheckable(true);
    postBtnFlares->setChecked(false);

    QPushButton* postBtnDistord = new QPushButton("Lense blur");
    postBtnDistord->setCheckable(true);
    postBtnDistord->setChecked(false);

    QVBoxLayout* layoutPost = new QVBoxLayout;
    layoutPost->addWidget(postBtnFXAA);
    layoutPost->addWidget(postBtnCascade);
    layoutPost->addWidget(postBtnAniso);
    layoutPost->addWidget(postBtnGodrays);
    layoutPost->addWidget(postBtnBloom);
    layoutPost->addWidget(postBtnFlares);
    layoutPost->addWidget(postBtnDistord);

    QGroupBox* groupPost = new QGroupBox("Effects");
    groupPost->setLayout(layoutPost);

    // Camera
    QPushButton* cameraBtnReset = new QPushButton("Reset camera");

    QVBoxLayout* layoutCamera = new QVBoxLayout;
    layoutCamera->addWidget(cameraBtnReset);

    QGroupBox* groupCamera = new QGroupBox("Camera");
    groupCamera->setLayout(layoutCamera);

    // Sliders
    QLabel* ratioLabel = new QLabel("Render resolution");
    QSlider* ratioSlider = new QSlider(Qt::Horizontal);
    ratioSlider->setRange(1, 10);
    ratioSlider->setValue(10);

    QLabel* sunLabelSpeed = new QLabel("Sun speed");
    QSlider* sunSliderSpeed = new QSlider(Qt::Horizontal);
    sunSliderSpeed->setRange(0, 100);
    sunSliderSpeed->setValue(0);

    QVBoxLayout* layoutFlare = new QVBoxLayout;
    layoutFlare->addWidget(ratioLabel);
    layoutFlare->addWidget(ratioSlider);
    layoutFlare->addWidget(sunLabelSpeed);
    layoutFlare->addWidget(sunSliderSpeed);

    QGroupBox* groupSliders = new QGroupBox("Parameters");
    groupSliders->setLayout(layoutFlare);

    // Actions
    QPushButton* actionBtnFS = new QPushButton("Go Fullscreen");
    actionBtnFS->setChecked(true);

    QVBoxLayout* layoutAction = new QVBoxLayout;
    layoutAction->addWidget(actionBtnFS);

    QGroupBox* groupAction = new QGroupBox("Actions");
    groupAction->setLayout(layoutAction);

    // FPS
    QVBoxLayout* layoutFPS = new QVBoxLayout;
    FPSDisplay = new QLCDNumber(2);
    FPSDisplay->setSegmentStyle(QLCDNumber::Flat);
    FPSDisplay->setFrameStyle(QFrame::NoFrame|QFrame::Plain);
    FPSDisplay->display(0.0);
    layoutFPS->addWidget(FPSDisplay);

    QGroupBox* groupFPS = new QGroupBox("FPS");
    groupFPS->setContentsMargins(0,4,0,0);
    groupFPS->setLayout(layoutFPS);

    QPushButton* btnPlay = new QPushButton("play / stop");
    btnPlay->setCheckable(true);
    btnPlay->setChecked(true);

    QVBoxLayout* layoutMusique = new QVBoxLayout;
    layoutMusique->addWidget(btnPlay);

    QGroupBox* groupMusique = new QGroupBox("Musique");
    groupMusique->setLayout(layoutMusique);


    QPushButton* btnRegenerate = new QPushButton("Go !");

    QVBoxLayout* layoutRegenerate = new QVBoxLayout;
    layoutRegenerate->addWidget(btnRegenerate);

    QGroupBox* groupRegenerate = new QGroupBox("Regenerate");
    groupRegenerate->setLayout(layoutRegenerate);

    // Dock layout
    QVBoxLayout* layoutDock = new QVBoxLayout;
    layoutDock->addWidget(groupFPS);
    layoutDock->addWidget(groupQuality);
    layoutDock->addWidget(groupPost);
    layoutDock->addWidget(groupCamera);
    layoutDock->addWidget(groupSliders);
    layoutDock->addWidget(groupAction);
    layoutDock->addWidget(groupMusique);
    layoutDock->addWidget(groupRegenerate);
    layoutDock->addStretch();

    paneParams->setLayout(layoutDock);

    QObject::connect(qualitySlider, SIGNAL(valueChanged(int)), paneGL, SLOT(exQuality(int)));
    QObject::connect(postBtnFXAA, SIGNAL(toggled(bool)), paneGL, SLOT(exPostFXAA(bool)));
    QObject::connect(postBtnCascade, SIGNAL(toggled(bool)), paneGL, SLOT(exShadowCascade(bool)));
    QObject::connect(postBtnAniso, SIGNAL(toggled(bool)), paneGL, SLOT(exAnisotropy(bool)));
    QObject::connect(postBtnFlares, SIGNAL(toggled(bool)), paneGL, SLOT(exPostLenseFlares(bool)));
    QObject::connect(postBtnDistord, SIGNAL(toggled(bool)), paneGL, SLOT(exPostDistord(bool)));
    QObject::connect(postBtnGodrays, SIGNAL(toggled(bool)), paneGL, SLOT(exPostGodrays(bool)));
    QObject::connect(postBtnBloom, SIGNAL(toggled(bool)), paneGL, SLOT(exPostBloom(bool)));
    QObject::connect(cameraBtnReset, SIGNAL(clicked()), paneGL, SLOT(exResetCamera()));
    QObject::connect(ratioSlider, SIGNAL(valueChanged(int)), paneGL, SLOT(exRenderRatio(int)));
    QObject::connect(sunSliderSpeed, SIGNAL(valueChanged(int)), paneGL, SLOT(exSunSpeed(int)));
    QObject::connect(actionBtnFS, SIGNAL(clicked()), this, SLOT(showFullScreen()));

    QObject::connect(btnPlay, SIGNAL(toggled(bool)), paneGL, SLOT(playBtn(bool)));
    QObject::connect(btnRegenerate, SIGNAL(clicked()), paneGL, SLOT(reGenerate()));
}

QDockWidget* MainWindow::getDock()
{
    return dock;
}

QLCDNumber* MainWindow::getFPSDisplay()
{
    return FPSDisplay;
}
