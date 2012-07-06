#include "window.h"

#include "mainwindow.h"

Window::Window() : QGLWidget()
{
    startTimer(30);
    resize(1024, 768);

    musique = new QSound("ambiant.wav");
    musique->setLoops(-1);
    musique->play();

    setFocusPolicy(Qt::WheelFocus);
    setWindowTitle("JungleIN");

    Utils::WINDOW = this;

}

Window::~Window()
{
}

void Window::timerEvent(QTimerEvent *)
{
    updateGL();
}

void Window::initializeGL()
{
    glewExperimental = GL_TRUE;

    GLenum error = glewInit();
    if(error != GLEW_OK)
    {
        QMessageBox::critical(this, "Erreur", "Echec de l'initialization de GLEW: "+QString(reinterpret_cast<const char *>(glewGetErrorString(error))));
        exit(-1);
    }

    if (!strstr((char*)glGetString(GL_EXTENSIONS),
        "GL_EXT_texture_filter_anisotropic"))
    {
       Utils::USE_ANISO = false;
       Utils::MAX_ANISO = 0x0000;
    }
    else
    {
        Utils::USE_ANISO = true;
        float maxAniso;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);
        Utils::MAX_ANISO = maxAniso;
    }

    initializeObjects();
}

void Window::initializeObjects()
{
    renderer = new Renderer();
    renderer->loadShaders();

    scene = SceneBuilder::build();
    scene->init();

    renderer->init(scene, 1024, 768);
    renderer->start();

}


void Window::paintGL()
{
    renderer->render();
}

void Window::resizeGL(int w, int h)
{
    renderer->resize(w, h);
}

void Window::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
      case Qt::Key_Left:
        scene->getCurrentCamera()->setLeftKey(true);
        break;
      case Qt::Key_Right:
        scene->getCurrentCamera()->setRightKey(true);
        break;
      case Qt::Key_Down:
        scene->getCurrentCamera()->setDownKey(true);
        break;
      case Qt::Key_Up:
        scene->getCurrentCamera()->setUpKey(true);
        break;
      default:
        break;
    }

}

void Window::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Left:
        scene->getCurrentCamera()->setLeftKey(false);
        event->accept();
        break;
    case Qt::Key_Right:
         scene->getCurrentCamera()->setRightKey(false);
        event->accept();
        break;
    case Qt::Key_Down:
        scene->getCurrentCamera()->setDownKey(false);
        event->accept();
        break;
    case Qt::Key_Up:
        scene->getCurrentCamera()->setUpKey(false);
        event->accept();
        break;
    case Qt::Key_Escape:
        Utils::MAIN->showNormal();
        break;
    case Qt::Key_O:
        ((MainWindow*)(Utils::MAIN))->getDock()->isHidden() ? ((MainWindow*)(Utils::MAIN))->getDock()->show() : ((MainWindow*)(Utils::MAIN))->getDock()->hide();
        break;
    default:
        break;
    }

}


void Window::mousePressEvent(QMouseEvent *)
{
    scene->getCurrentCamera()->activeLook(true);
}

void Window::mouseReleaseEvent(QMouseEvent *)
{
    scene->getCurrentCamera()->activeLook(false);
}


void Window::exQuality(int value)
{
    Utils::QUALITY = value;
    renderer->getPostComposer()->resizeHalfBuffers();
}

void Window::exResetCamera()
{
    scene->getCurrentCamera()->reset();
}

void Window::exPostFXAA(bool active)
{
    renderer->getPostComposer()->toggleFXAA(active);
}

void Window::exPostDistord(bool active)
{
    renderer->getPostComposer()->toggleDistord(active);
}

void Window::exPostLenseFlares(bool active)
{
    renderer->getPostComposer()->toggleLenseFlares(active);
}

void Window::exPostGodrays(bool active)
{
    renderer->getPostComposer()->toggleGodrays(active);
}

void Window::exPostBloom(bool active)
{
    renderer->getPostComposer()->toggleBloom(active);
}

void Window::exFlareDisp(int value)
{
    renderer->getPostComposer()->setFlareDispersal(value/100.0);
}

void Window::exFlareIntensity(int value)
{
    renderer->getPostComposer()->setFlareIntensity(value/100.0);
}

void Window::exSunSpeed(int value)
{
    scene->getSun()->setSpeed(value/10.0);
}

void Window::exGamma(int value)
{
    renderer->getPostComposer()->setGamma(value/100.0);
}

void Window::exAnisotropy(bool active)
{
    Utils::USE_ANISO = active;
    Texture::needsUpdate = true;
}

void Window::exShadowCascade(bool active)
{
    renderer->toggleShadowCascade(active);
}

void Window::exRenderRatio(int value)
{
    renderer->setRatio(value / 10.0);
}

void Window::playBtn(bool active)
{
    if (active)
        musique->play();
    else
        musique->stop();
}

void Window::reGenerate()
{
    ReloadWindow* test = new ReloadWindow();
    test->show();
}
