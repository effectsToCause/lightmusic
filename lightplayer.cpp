#include "lightplayer.h"
#include "ui_lightplayer.h"

lightPlayer::lightPlayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::lightPlayer)
{
    ui->setupUi(this);
}

lightPlayer::~lightPlayer()
{
    delete ui;
}
