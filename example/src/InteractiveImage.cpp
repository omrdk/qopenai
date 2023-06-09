#include "InteractiveImage.h"

#include <QImageWriter>
#include <QImageReader>

InteractiveImage::InteractiveImage(QQuickPaintedItem *parent)
    : QQuickPaintedItem{parent}
{
    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptTouchEvents(true);
}

QString InteractiveImage::getSource() const {
    return _source;
}

void InteractiveImage::setSource(const QString &source) {
    _source = source;
    updateImage();
    emit sourceChanged() ;
    update();
}

void InteractiveImage::removeAlphaFromImage(const QPointF &point) {
    QPainter painter(&_image);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOut);
    painter.setPen(QPen(Qt::color1, 40, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(QPointF(_prevPoint.x(), _prevPoint.y() - _imageY), QPointF(point.x(), point.y() - _imageY));
    _prevPoint = point;
    update();
}

void InteractiveImage::paint(QPainter *painter) {
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawImage(QPoint(0, _imageY), _image);
}

void InteractiveImage::mousePressEvent(QMouseEvent *event) {
    _prevPoint = event->position();
    removeAlphaFromImage(event->position());
}

void InteractiveImage::mouseMoveEvent(QMouseEvent *event) {
    removeAlphaFromImage(event->position());
}

void InteractiveImage::mouseReleaseEvent(QMouseEvent *event) {
    removeAlphaFromImage(event->position());
    _image.save(_maskPath);
}

void InteractiveImage::touchEvent(QTouchEvent *event)
{
    const auto eventType = event->type();
    switch (eventType) {
    case QEvent::TouchBegin: {
        _prevPoint = event->points().last().position();
        removeAlphaFromImage(event->points().last().position());
        break;
    }
    case QEvent::TouchUpdate: {
        removeAlphaFromImage(event->points().last().position());
        break;
    }
    case QEvent::TouchEnd: {
        removeAlphaFromImage(event->points().last().position());
        _image.save(_maskPath);
        break;
    }
    default:
        break;
    }
}

void InteractiveImage::updateImage()
{
    if(!_source.isEmpty()) {
        _image = QImage(width(), height(), QImage::Format_ARGB32);
        _image.fill(Qt::transparent);
        _image.load(_source);
        _image = _image.scaled(width(), height(), Qt::KeepAspectRatio);
        _imageY = (height() - _image.height()) / 2;
        createDuplicates();
    }
}

void InteractiveImage::createDuplicates()
{
    QFileInfo inputFile(_source);
    QString tempLocation = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
    _imagePath = tempLocation + "/" + inputFile.completeBaseName() + "_copy." + inputFile.suffix();
    _maskPath = tempLocation + "/" + inputFile.completeBaseName() + "_mask." + inputFile.suffix();
    _image.save(_imagePath);
    _image.save(_maskPath);
    emit duplicateImagesCreated(_imagePath, _maskPath);
}

bool InteractiveImage::isFormatSupported(const QString &imagePath) const {
    QImageReader imageReader(imagePath);
    const auto format = imageReader.format();
    if(QImageWriter::supportedImageFormats().contains(format)) {
        return true;
    }
    return false;
}

QString InteractiveImage::convertToPng(const QString &imagePath) {
    bool isSuffixIsPng = isPngImage(imagePath);
    if(isSuffixIsPng) {
        return imagePath;
    }
    QFileInfo inputFile(imagePath);
    QString outputFilePath = inputFile.path() + "/" + inputFile.completeBaseName() + "." + inputFile.suffix();
    QImage image(imagePath);
    image.save(outputFilePath, "png");
    return outputFilePath;
}

bool InteractiveImage::isPngImage(const QString &imagePath) const {
    QImageReader imageReader(imagePath);
    const auto format = imageReader.format();
    if(format == "png") {
        return true;
    }
    return false;
}


