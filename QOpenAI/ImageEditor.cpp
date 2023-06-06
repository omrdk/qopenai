#include "ImageEditor.h"

ImageEditor::ImageEditor(QObject *parent)
    : QObject{parent}
{

}

QString ImageEditor::convertToPng(const QString &imagePath) {
    bool isSuffixIsPng = checkSuffixIsPng(imagePath);
    if(isSuffixIsPng) {
        return imagePath;
    }
    QFileInfo inputFile(imagePath);
    QString outputFilePath = inputFile.path() + "/" + inputFile.completeBaseName() + ".png";
    QImage image(imagePath);
    image.save(outputFilePath, "png");
    return outputFilePath;
}

bool ImageEditor::checkImageFormatSupported(const QString &imagePath) const {
    QImageReader imageReader(imagePath);
    const auto format = imageReader.format();
    if(QImageWriter::supportedImageFormats().contains(format)) {
        return true;
    }
    return false;
}

bool ImageEditor::checkSuffixIsPng(const QString &imagePath) const {
    QImageReader imageReader(imagePath);
    const auto format = imageReader.format();
    if(format == "png") {
        return true;
    }
    return false;
}
