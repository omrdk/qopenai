#include "AudioRecorder.h"

#include <QAudioInput>
#include <QAudioDevice>
#include <QMediaFormat>
#include <QFileInfo>

AudioRecorder::AudioRecorder(QObject *parent)
    : QObject{parent}
{
    _captureSession.setRecorder(&_audioRecorder);
    _captureSession.setAudioInput(new QAudioInput(this));

    connect(&_audioRecorder, &QMediaRecorder::recorderStateChanged, this, [&](QMediaRecorder::RecorderState state) {
        qDebug() << "'State:" << state;
        switch (state) {
        case QMediaRecorder::RecorderState::StoppedState:
            emit recordingFinished(QUrl::fromLocalFile(QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/recorded_voice"));
            break;
        default:
            break;
        }
    });

    connect(&_audioRecorder, &QMediaRecorder::errorOccurred, this, [&](QMediaRecorder::Error error, const QString &errorString) {
        // Is _audioRecorder->stop() call needed here?
        qDebug() << "'Error:" << error << " " << errorString;
    });
}

void AudioRecorder::toggleRecord() {
    if (_audioRecorder.recorderState() == QMediaRecorder::StoppedState) {
        _captureSession.audioInput()->setDevice(QVariant(QString()).value<QAudioDevice>());
        //_captureSession.audioInput()->setVolume(50);
        QMediaFormat format;
        format.setAudioCodec(QMediaFormat::AudioCodec::Unspecified);
        format.setFileFormat(QMediaFormat::FileFormat::UnspecifiedFormat);
        qDebug() << _captureSession.audioInput()->device().description();
        _audioRecorder.setMediaFormat(format);
        _audioRecorder.setAudioSampleRate(44100);
        _audioRecorder.setAudioBitRate(0);
        _audioRecorder.setQuality(QMediaRecorder::Quality::VeryHighQuality);
        _audioRecorder.setEncodingMode(QMediaRecorder::ConstantQualityEncoding);

        #ifdef Q_OS_IOS
        QFile::remove(QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/recorded_voice.m4a");
        #endif

        _audioRecorder.setOutputLocation(QUrl::fromLocalFile(QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/recorded_voice"));
        _audioRecorder.record();
        _isRecording = true;
    } else {
        _audioRecorder.stop();
        _isRecording = false;
    }
    emit isRecordingChanged();
}
