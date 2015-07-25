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

    /*/////////////Color Keys//////////////*/

    //--Infrared/Red
    const static int IRu1 =740;
    const static int IR0 = 370;
    const static int IRd1 = 185;

    //--Red
    const static int Ru1 =784;
    const static int R0 = 392;
    const static int Rd1 = 196;

    //--Red/Orange
    const static int ROu1 =830;
    const static int RO0 = 415;
    const static int ROd1 = 208;

    //--Orange
    const static int Ou1 =880;
    const static int O0 = 440;
    const static int Od1 = 220;

    //--Yellow
    const static int Yu1 =932;
    const static int Y0 = 466;
    const static int Yd1 = 233;

    //--Yellow/Green
    const static int YGu1 =988;
    const static int YG0 = 494;
    const static int YGd1 = 247;

    //--Green
    const static int Gu1 =1046;
    const static int G0 = 523;
    const static int Gd1 = 262;

    //--Green/Blue
    const static int GBu1 =1108;
    const static int GB0 = 554;
    const static int GBd1 = 277;

    //--Blue
    const static int Bu1 =1174;
    const static int B0 = 587;
    const static int Bd1 = 294;

    //--Blue/Violet
    const static int BVu1 =1244;
    const static int BV0 = 622;
    const static int BVd1 = 311;

    //--Violet
    const static int Vu1 =1320;
    const static int V0 = 660;
    const static int Vd1 = 330;

    //--Ultraviolet/Violet
    const static int UVu1 =1400;
    const static int UV0 = 700;
    const static int UVd1 = 350;

private slots:
    void toggleSuspendResume();

/*/////////////Color Buttons//////////////*/

    //--Infrared/Red
    void on_IR0Button_pressed();
    void on_IR0Button_released();
    void on_IRu1Button_pressed();
    void on_IRu1Button_released();
    void on_IRd1Button_pressed();
    void on_IRd1Button_released();

    //--Red
    void on_R0Button_pressed();
    void on_R0Button_released();
    void on_Ru1Button_pressed();
    void on_Ru1Button_released();
    void on_Rd1Button_pressed();
    void on_Rd1Button_released();

    //--Red/Orange
    void on_RO0Button_pressed();
    void on_RO0Button_released();
    void on_ROu1Button_pressed();
    void on_ROu1Button_released();
    void on_ROd1Button_pressed();
    void on_ROd1Button_released();

    //--Orange
    void on_O0Button_pressed();
    void on_O0Button_released();
    void on_Ou1Button_pressed();
    void on_Ou1Button_released();
    void on_Od1Button_pressed();
    void on_Od1Button_released();

    //--Yellow
    void on_Y0Button_pressed();
    void on_Y0Button_released();
    void on_Yu1Button_pressed();
    void on_Yu1Button_released();
    void on_Yd1Button_pressed();
    void on_Yd1Button_released();

    //--Yellow/Green
    void on_YG0Button_pressed();
    void on_YG0Button_released();
    void on_YGu1Button_pressed();
    void on_YGu1Button_released();
    void on_YGd1Button_pressed();
    void on_YGd1Button_released();

    //--Green
    void on_G0Button_pressed();
    void on_G0Button_released();
    void on_Gu1Button_pressed();
    void on_Gu1Button_released();
    void on_Gd1Button_pressed();
    void on_Gd1Button_released();

    //--Green/Blue
    void on_GB0Button_pressed();
    void on_GB0Button_released();
    void on_GBu1Button_pressed();
    void on_GBu1Button_released();
    void on_GBd1Button_pressed();
    void on_GBd1Button_released();

    //--Blue
    void on_B0Button_pressed();
    void on_B0Button_released();
    void on_Bu1Button_pressed();
    void on_Bu1Button_released();
    void on_Bd1Button_pressed();
    void on_Bd1Button_released();

    //--Blue/Violet
    void on_BV0Button_pressed();
    void on_BV0Button_released();
    void on_BVu1Button_pressed();
    void on_BVu1Button_released();
    void on_BVd1Button_pressed();
    void on_BVd1Button_released();

    //--Violet
    void on_V0Button_pressed();
    void on_V0Button_released();
    void on_Vu1Button_pressed();
    void on_Vu1Button_released();
    void on_Vd1Button_pressed();
    void on_Vd1Button_released();

    //--Ultraviolet/Violet
    void on_UV0Button_pressed();
    void on_UV0Button_released();
    void on_UVu1Button_pressed();
    void on_UVu1Button_released();
    void on_UVd1Button_pressed();
    void on_UVd1Button_released();



private:
    Ui::lightPlayer *ui;
};

#endif // LIGHTPLAYER_H
