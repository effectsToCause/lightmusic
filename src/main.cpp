#include "lightplayer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    lightPlayer w;
    w.show();

    return a.exec();
}
