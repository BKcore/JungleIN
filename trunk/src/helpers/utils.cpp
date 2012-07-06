#include "utils.h"

#include <stdio.h>
#include <QDebug>
#include <QTime>
#include "../ui/mainwindow.h"

QWidget* Utils::WINDOW = NULL;
MainWindow* Utils::MAIN = NULL;
bool Utils::USE_ANISO = false;
unsigned int Utils::MAX_ANISO = 0x0000;
int Utils::QUALITY = 1;

double Utils::TARGET_FPS = 32.0;

char* Utils::getFileContent(QString path)
{
    FILE* fp;
    char* content = NULL;
    long length;

    fp = fopen( path.toAscii(), "rb" );
    if (fp)
    {
        fseek( fp, 0, SEEK_END );
        length = ftell( fp );
        fseek( fp, 0, SEEK_SET );
        content = new char [length+1];
        fread( content, sizeof( char ), length, fp );
        fclose( fp );
        content[length] = '\0';
    }

    return content;
}


double Utils::calculFPS()
{
    static double current_time = 0;
    static double last_time = 0;
    static double average = 0;
    static int count = 0;
    static double av = 0;
    last_time = current_time;

    QTime t;
    current_time = t.currentTime().msec();

    if (current_time > last_time)
    {
         average += 1000/(current_time - last_time);
         count++;
    }

    if (count == 30)
    {

        Utils::MAIN->getFPSDisplay()->display(average/count);
        av = average / count;
        count = 0;
        average = 0;

    }
    return av;

}

double Utils::random(double min, double max)
{
    return (rand() / static_cast<double>(RAND_MAX)) * (max - min) + min;
}
