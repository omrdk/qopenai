#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H
#pragma once

#include <QObject>
#include <QtQml>
#include <QMediaCaptureSession>
#include <QMediaRecorder>
#include <QUrl>

class AudioRecorder : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isRecording MEMBER _isRecording NOTIFY isRecordingChanged)
    QML_ELEMENT

public:
    explicit AudioRecorder(QObject *parent = nullptr);

    Q_INVOKABLE void toggleRecord();

private:
    QMediaCaptureSession _captureSession;
    QMediaRecorder _audioRecorder;
    bool _isRecording = false;

signals:
    void emptySignal();
    void recordingFinished(const QString& audioFilePath); // it was url
    void isRecordingChanged();
};

#endif // AUDIORECORDER_H
