#ifndef UTILS_H
#define UTILS_H

#include <QMainWindow>
#include <QWidget>

class MainWindow;

/*!
 * Utils
 * Fonctions diverses et variées (mais utiles)
 * @static
 */
class Utils
{
public:

    static char* getFileContent(QString path);

    static MainWindow* MAIN;
    static QWidget* WINDOW;
    static bool USE_ANISO;
    static unsigned int MAX_ANISO;
    static int QUALITY;

    static double TARGET_FPS;

    static double calculFPS();

    static double random(double min, double max);

};

#endif // UTILS_H
