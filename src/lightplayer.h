#ifndef LIGHTPLAYER_H
#define LIGHTPLAYER_H

#include <QMainWindow>

namespace Ui {
class lightPlayer;
}

class lightPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit lightPlayer(QWidget *parent = 0);
    ~lightPlayer();

private:
    Ui::lightPlayer *ui;
};

#endif // LIGHTPLAYER_H
