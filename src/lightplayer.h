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
    void on_pushButton_pressed();

private:
    Ui::lightPlayer *ui;
};

#endif // LIGHTPLAYER_H
