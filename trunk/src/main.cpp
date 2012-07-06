#include "ui/mainwindow.h"

#include <QApplication>
#include <stdio.h>
#include <QPixmap>
#include <QSplashScreen>
#include <QWidget>
#include <QMainWindow>
#include <QDebug>


int main(int argc, char *argv[])
{
    srand(QTime::currentTime().msec());

    QApplication app(argc, argv);


    QPixmap pixmap("splash.png");
    QSplashScreen splash(pixmap);
    splash.show();
    splash.showMessage("Wait...");
    qApp->processEvents();

    MainWindow main;
    main.show();
    splash.finish(&main);

	return app.exec();
}
