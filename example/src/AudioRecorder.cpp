#include "AudioRecorder.h"

#include <QAudioInput>
#include <QAudioDevice>
#include <QMediaFormat>
#include <QStandardPaths>

AudioRecorder::AudioRecorder(QObject *parent) : QObject{parent} {
    _captureSession.setRecorder(&_audioRecorder);
    _captureSession.setAudioInput(new QAudioInput(this));

    connect(&_audioRecorder, &QMediaRecorder::recorderStateChanged, this, [&](QMediaRecorder::RecorderState state) {
        switch (state) {
        case QMediaRecorder::RecorderState::StoppedState: {
            QString audioFilePath = _audioRecorder.actualLocation().toString();
            emit recordingFinished(audioFilePath);
            break;
        }
        default:
            break;
        }
    });

    connect(&_audioRecorder, &QMediaRecorder::errorOccurred, this, [&](QMediaRecorder::Error error, const QString &errorString) {
        if(_audioRecorder.recorderState() != QMediaRecorder::StoppedState) {
            _audioRecorder.stop();
        }
        qDebug() << "Error:" << error << " " << errorString;
    });
}

void AudioRecorder::toggleRecord() {
    if (_audioRecorder.recorderState() == QMediaRecorder::StoppedState) {
        _captureSession.audioInput()->setDevice(QVariant(QString()).value<QAudioDevice>());
        QMediaFormat format;
        format.setAudioCodec(QMediaFormat::AudioCodec::Unspecified);
        format.setFileFormat(QMediaFormat::FileFormat::UnspecifiedFormat);
        _audioRecorder.setMediaFormat(format);
        _audioRecorder.setAudioSampleRate(44100);
        _audioRecorder.setAudioBitRate(0);
        _audioRecorder.setQuality(QMediaRecorder::Quality::VeryHighQuality);
        _audioRecorder.setEncodingMode(QMediaRecorder::ConstantQualityEncoding);
        #ifdef Q_OS_IOS
        QFile::remove(QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/recorded_voice.m4a");
        //QFile::remove(_audioRecorder.actualLocation().toString()) // TODO: test
        #endif
        QUrl audioFilePathUrl = QUrl::fromLocalFile(QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/audio");
        _audioRecorder.setOutputLocation(audioFilePathUrl);
        if(_audioRecorder.isAvailable()) {
            _audioRecorder.record();
            _isRecording = true;
        }
    } else {
        _audioRecorder.stop();
        _isRecording = false;
    }
    emit isRecordingChanged();
}
