#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "window.h"

class MainWindow : public QMainWindow
{
    //Q_OBJECT

public:
    MainWindow();
    void setGLFormat();
    void initPaneGL();
    void initPaneParam();

    QDockWidget* getDock();
    QLCDNumber* getFPSDisplay();

private:
    Window* paneGL;
    QWidget* paneParams;
    QDockWidget* dock;
    QLCDNumber* FPSDisplay;
};

#endif // MAINWINDOW_H
