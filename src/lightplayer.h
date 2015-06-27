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

class lightPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit lightPlayer(QWidget *parent = 0);
    ~lightPlayer();

private:
    Ui::lightPlayer *ui;
};

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
    qint64 bytesAvailable() const;

private:
    void generateData(const QAudioFormat &format, qint64 durationUs, int sampleRate);

private:
    qint64 m_pos;
    QByteArray m_buffer;
};

class AudioTest : public QMainWindow
{
    Q_OBJECT

public:
    AudioTest();
    ~AudioTest();

private:
    void initializeWindow();
    void initializeAudio();
    void createAudioOutput();

private:
    QTimer *m_pullTimer;

    // Owned by layout
    QPushButton *m_modeButton;
    QPushButton *m_suspendResumeButton;
    QComboBox *m_deviceBox;
    QLabel *m_volumeLabel;
    QSlider *m_volumeSlider;

    QAudioDeviceInfo m_device;
    Generator *m_generator;
    QAudioOutput *m_audioOutput;
    QIODevice *m_output; // not owned
    QAudioFormat m_format;

    bool m_pullMode;
    QByteArray m_buffer;

private slots:
    void pullTimerExpired();
    void toggleMode();
    void toggleSuspendResume();
    void deviceChanged(int index);
    void volumeChanged(int);
};
#endif // LIGHTPLAYER_H
