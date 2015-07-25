#ifndef LIGHTPLAYER_H
#define LIGHTPLAYER_H

#include <math.h>
#include <QAudioOutput>
#include <QByteArray>
#include <QComboBox>
#include <QIODevice>
#include <QLabel>
#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QSlider>
#include <QTimer>
#include <QMainWindow>

namespace Ui {
class lightPlayer;
}

class Generator : public QIODevice
{
    Q_OBJECT

public:
    Generator(const QAudioFormat &format, qint64 durationUs, int sampleRate, QObject *parent);
    ~Generator();

    void start();
    void stop();

    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);

private:
    void generateData(const QAudioFormat &format, qint64 durationUs, int sampleRate);

private:
    qint64 m_pos;
    QByteArray m_buffer;
};

class lightPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit lightPlayer(QWidget *parent = 0);
    ~lightPlayer();

private:
    void initializeAudio();
    void createAudioOutput();

private:
    QAudioDeviceInfo m_device;
    Generator *m_generator;
    QAudioOutput *m_audioOutput;
    QIODevice *m_output; // not owned
    QAudioFormat m_format;
    QByteArray m_buffer;

private slots:
    void toggleSuspendResume();


/*/////////////Color Keys//////////////*/

    //--Infrared/Red
    void on_IR0_pressed();
    void on_IR0_released();
    void on_IRu1_pressed();
    void on_IRu1_released();
    void on_IRd1_pressed();
    void on_IRd1_released();

    //--Red
    void on_R0_pressed();
    void on_R0_released();
    void on_Ru1_pressed();
    void on_Ru1_released();
    void on_Rd1_pressed();
    void on_Rd1_released();

    //--Red/Orange
    void on_RO0_pressed();
    void on_RO0_released();
    void on_ROu1_pressed();
    void on_ROu1_released();
    void on_ROd1_pressed();
    void on_ROd1_released();

    //--Orange
    void on_O0_pressed();
    void on_O0_released();
    void on_Ou1_pressed();
    void on_Ou1_released();
    void on_Od1_pressed();
    void on_Od1_released();

    //--Yellow
    void on_Y0_pressed();
    void on_Y0_released();
    void on_Yu1_pressed();
    void on_Yu1_released();
    void on_Yd1_pressed();
    void on_Yd1_released();

    //--Yellow/Green
    void on_YG0_pressed();
    void on_YG0_released();
    void on_YGu1_pressed();
    void on_YGu1_released();
    void on_YGd1_pressed();
    void on_YGd1_released();

    //--Green
    void on_G0_pressed();
    void on_G0_released();
    void on_Gu1_pressed();
    void on_Gu1_released();
    void on_Gd1_pressed();
    void on_Gd1_released();

    //--Green/Blue
    void on_GB0_pressed();
    void on_GB0_released();
    void on_GBu1_pressed();
    void on_GBu1_released();
    void on_GBd1_pressed();
    void on_GBd1_released();

    //--Blue
    void on_B0_pressed();
    void on_B0_released();
    void on_Bu1_pressed();
    void on_Bu1_released();
    void on_Bd1_pressed();
    void on_Bd1_released();

    //--Blue/Violet
    void on_BV0_pressed();
    void on_BV0_released();
    void on_BVu1_pressed();
    void on_BVu1_released();
    void on_BVd1_pressed();
    void on_BVd1_released();

    //--Violet
    void on_V0_pressed();
    void on_V0_released();
    void on_Vu1_pressed();
    void on_Vu1_released();
    void on_Vd1_pressed();
    void on_Vd1_released();

    //--Ultraviolet/Violet
    void on_UV0_pressed();
    void on_UV0_released();
    void on_UVu1_pressed();
    void on_UVu1_released();
    void on_UVd1_pressed();
    void on_UVd1_released();



private:
    Ui::lightPlayer *ui;
};

#endif // LIGHTPLAYER_H
