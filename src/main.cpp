#include "lightplayer.h"
#include "audiooutput.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    lightPlayer w;
    //w.show();

    AudioTest audio;
    audio.show();

    return a.exec();
}
