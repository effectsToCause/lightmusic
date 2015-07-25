#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QDebug>
#include <QVBoxLayout>
#include <qmath.h>
#include <qendian.h>

#include "lightplayer.h"
#include "ui_lightplayer.h"

int ToneSampleRateHz;
const int DurationSeconds = 1;
const int DataSampleRateHz = 44100;
const int BufferSize      = 32768;

lightPlayer::lightPlayer(QWidget *parent)
    :   QMainWindow(parent)
    ,   m_device(QAudioDeviceInfo::defaultOutputDevice())
    ,   m_generator(0)
    ,   m_audioOutput(0)
    ,   m_output(0)
    ,   m_buffer(BufferSize, 0)
    ,   ui(new Ui::lightPlayer)
{
    initializeAudio();
    ui->setupUi(this);
}

/*///////////////////audio generation/////////////////////////*/

Generator::Generator(const QAudioFormat &format,
                     qint64 durationUs,
                     int sampleRate,
                     QObject *parent)
    :   QIODevice(parent)
    ,   m_pos(0)
{
    if (format.isValid())
        generateData(format, durationUs, sampleRate);
}

Generator::~Generator()
{

}

void Generator::start()
{
    open(QIODevice::ReadOnly);
}

void Generator::stop()
{
    m_pos = 0;
    close();
}

void Generator::generateData(const QAudioFormat &format, qint64 durationUs, int sampleRate)
{
    const int channelBytes = format.sampleSize() / 8;
    const int sampleBytes = format.channelCount() * channelBytes;

    qint64 length = (format.sampleRate() * format.channelCount() * (format.sampleSize() / 8))
                        * durationUs / 100000;

    Q_ASSERT(length % sampleBytes == 0);
    Q_UNUSED(sampleBytes) // suppress warning in release builds

    m_buffer.resize(length);
    unsigned char *ptr = reinterpret_cast<unsigned char *>(m_buffer.data());
    int sampleIndex = 0;

    while (length) {
        const qreal x = qSin(2 * M_PI * sampleRate * qreal(sampleIndex % format.sampleRate()) / format.sampleRate());
        for (int i=0; i<format.channelCount(); ++i) {
            if (format.sampleSize() == 8 && format.sampleType() == QAudioFormat::UnSignedInt) {
                const quint8 value = static_cast<quint8>((1.0 + x) / 2 * 255);
                *reinterpret_cast<quint8*>(ptr) = value;
            } else if (format.sampleSize() == 8 && format.sampleType() == QAudioFormat::SignedInt) {
                const qint8 value = static_cast<qint8>(x * 127);
                *reinterpret_cast<quint8*>(ptr) = value;
            } else if (format.sampleSize() == 16 && format.sampleType() == QAudioFormat::UnSignedInt) {
                quint16 value = static_cast<quint16>((1.0 + x) / 2 * 65535);
                if (format.byteOrder() == QAudioFormat::LittleEndian)
                    qToLittleEndian<quint16>(value, ptr);
                else
                    qToBigEndian<quint16>(value, ptr);
            } else if (format.sampleSize() == 16 && format.sampleType() == QAudioFormat::SignedInt) {
                qint16 value = static_cast<qint16>(x * 32767);
                if (format.byteOrder() == QAudioFormat::LittleEndian)
                    qToLittleEndian<qint16>(value, ptr);
                else
                    qToBigEndian<qint16>(value, ptr);
            }

            ptr += channelBytes;
            length -= channelBytes;
        }
        ++sampleIndex;
    }
}

qint64 Generator::readData(char *data, qint64 len)
{
    qint64 total = 0;
    if (!m_buffer.isEmpty()) {
        while (len - total > 0) {
            const qint64 chunk = qMin((m_buffer.size() - m_pos), len - total);
            memcpy(data + total, m_buffer.constData() + m_pos, chunk);
            m_pos = (m_pos + chunk) % m_buffer.size();
            total += chunk;
        }
    }
    return total;
}

qint64 Generator::writeData(const char *data, qint64 len)
{
    Q_UNUSED(data);
    Q_UNUSED(len);

    return 0;
}

void lightPlayer::initializeAudio()
{
    m_format.setSampleRate(DataSampleRateHz);
    m_format.setChannelCount(1);
    m_format.setSampleSize(16);
    m_format.setCodec("audio/pcm");
    m_format.setByteOrder(QAudioFormat::LittleEndian);
    m_format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(m_format)) {
        qWarning() << "Default format not supported - trying to use nearest";
        m_format = info.nearestFormat(m_format);
    }
}

void lightPlayer::createAudioOutput()
{
    delete m_generator;
    delete m_audioOutput;
    m_generator = new Generator(m_format, DurationSeconds*1000000, ToneSampleRateHz, this);
    m_audioOutput = 0;
    m_audioOutput = new QAudioOutput(m_device, m_format, this);
    m_generator->start();
    m_audioOutput->start(m_generator);
    toggleSuspendResume();
}

void lightPlayer::toggleSuspendResume()
{
    if (m_audioOutput->state() == QAudio::SuspendedState) {
        m_audioOutput->resume();
    } else if (m_audioOutput->state() == QAudio::ActiveState) {
        m_audioOutput->suspend();
    } else if (m_audioOutput->state() == QAudio::StoppedState) {
        m_audioOutput->resume();
    } else if (m_audioOutput->state() == QAudio::IdleState) {
        // no-op
    }
}

/*///////////////////instrument player/////////////////////////*/

//---Infrared/Red
void lightPlayer::on_IRu1_pressed()
{
    ToneSampleRateHz = 740;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_IR0_pressed()
{
    ToneSampleRateHz = 370;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_IRd1_pressed()
{
    ToneSampleRateHz = 185;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_IRu1_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_IR0_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_IRd1_released()
{
    toggleSuspendResume();
}

//---Red
void lightPlayer::on_Ru1_pressed()
{
    ToneSampleRateHz = 784;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_R0_pressed()
{
    ToneSampleRateHz = 392;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_Rd1_pressed()
{
    ToneSampleRateHz = 196;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_Ru1_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_R0_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_Rd1_released()
{
    toggleSuspendResume();
}


//---Red/Orange
void lightPlayer::on_ROu1_pressed()
{
    ToneSampleRateHz = 830;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_RO0_pressed()
{
    ToneSampleRateHz = 415;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_ROd1_pressed()
{
    ToneSampleRateHz = 208;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_ROu1_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_RO0_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_ROd1_released()
{
    toggleSuspendResume();
}

//---Orange
void lightPlayer::on_Ou1_pressed()
{
    ToneSampleRateHz = 880;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_O0_pressed()
{
    ToneSampleRateHz = 440;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_Od1_pressed()
{
    ToneSampleRateHz = 220;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_Ou1_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_O0_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_Od1_released()
{
    toggleSuspendResume();
}

//---Yellow
void lightPlayer::on_Yu1_pressed()
{
    ToneSampleRateHz = 932;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_Y0_pressed()
{
    ToneSampleRateHz = 466;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_Yd1_pressed()
{
    ToneSampleRateHz = 233;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_Yu1_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_Y0_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_Yd1_released()
{
    toggleSuspendResume();
}

//---Yellow/Green
void lightPlayer::on_YGu1_pressed()
{
    ToneSampleRateHz = 988;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_YG0_pressed()
{
    ToneSampleRateHz = 494;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_YGd1_pressed()
{
    ToneSampleRateHz = 247;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_YGu1_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_YG0_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_YGd1_released()
{
    toggleSuspendResume();
}

//---Green
void lightPlayer::on_Gu1_pressed()
{
    ToneSampleRateHz = 1046;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_G0_pressed()
{
    ToneSampleRateHz = 523;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_Gd1_pressed()
{
    ToneSampleRateHz = 262;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_Gu1_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_G0_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_Gd1_released()
{
    toggleSuspendResume();
}

//---Green/Blue
void lightPlayer::on_GBu1_pressed()
{
    ToneSampleRateHz = 1108;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_GB0_pressed()
{
    ToneSampleRateHz = 554;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_GBd1_pressed()
{
    ToneSampleRateHz = 277;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_GBu1_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_GB0_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_GBd1_released()
{
    toggleSuspendResume();
}

//---Blue
void lightPlayer::on_Bu1_pressed()
{
    ToneSampleRateHz = 1174;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_B0_pressed()
{
    ToneSampleRateHz = 587;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_Bd1_pressed()
{
    ToneSampleRateHz = 294;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_Bu1_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_B0_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_Bd1_released()
{
    toggleSuspendResume();
}

//---Blue/Violet
void lightPlayer::on_BVu1_pressed()
{
    ToneSampleRateHz = 1244;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_BV0_pressed()
{
    ToneSampleRateHz = 622;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_BVd1_pressed()
{
    ToneSampleRateHz = 311;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_BVu1_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_BV0_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_BVd1_released()
{
    toggleSuspendResume();
}

//---Violet
void lightPlayer::on_Vu1_pressed()
{
    ToneSampleRateHz = 1320;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_V0_pressed()
{
    ToneSampleRateHz = 660;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_Vd1_pressed()
{
    ToneSampleRateHz = 330;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_Vu1_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_V0_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_Vd1_released()
{
    toggleSuspendResume();
}

//---Ultra/Violet
void lightPlayer::on_UVu1_pressed()
{
    ToneSampleRateHz = 1400;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_UV0_pressed()
{
    ToneSampleRateHz = 700;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_UVd1_pressed()
{
    ToneSampleRateHz = 350;
    createAudioOutput();
    toggleSuspendResume();
}
void lightPlayer::on_UVu1_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_UV0_released()
{
    toggleSuspendResume();
}
void lightPlayer::on_UVd1_released()
{
    toggleSuspendResume();
}

lightPlayer::~lightPlayer()
{
    delete ui;
}
