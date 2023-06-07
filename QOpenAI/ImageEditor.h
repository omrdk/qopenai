#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H
#pragma once

#include <QObject>
#include <QtQml>

class ImageEditor : public QObject
{
    Q_OBJECT
    QML_UNCREATABLE("Not creatable")

public:
    explicit ImageEditor(QObject *parent = nullptr);

    QString convertToPng(const QString& imagePath);
    bool checkImageFormatSupported(const QString& imagePath) const;

private:
    bool checkSuffixIsPng(const QString& imagePath) const;
};

#endif // IMAGEEDITOR_H
