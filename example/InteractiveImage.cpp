#include "InteractiveImage.h"
#include "qimagewriter.h"

#include <QRect>
#include <QFileInfo>
#include <QStandardPaths>

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
    refreshAndDuplicate();
    emit sourceChanged() ;
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
    QFileInfo inputFile(_source);
    _image.save(QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/" + inputFile.completeBaseName() + "_mask.png");
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
        QFileInfo inputFile(_source);
        _image.save(QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/" + inputFile.completeBaseName() + "_mask.png");
        break;
    }
    default:
        break;
    }
}

void InteractiveImage::refreshAndDuplicate()
{
    if(!_source.isEmpty()) {
        _image = QImage(width(), height(), QImage::Format_ARGB32);
        _image.fill(Qt::transparent);
        _image.load(_source);
        _image = _image.scaled(width(), height(), Qt::KeepAspectRatio);
        QFileInfo inputFile(_source);
        _image.save(QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/" + inputFile.completeBaseName() + "_copy.png");
        _imageY = (height() - _image.height()) / 2;
    }
}

void InteractiveImage::removeAlphaFromImage(const QPointF &point) {
    QPainter painter(&_image);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOut);
    painter.setPen(QPen(Qt::color1, 40, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(QPointF(_prevPoint.x(), _prevPoint.y() - _imageY), QPointF(point.x(), point.y() - _imageY));
    _prevPoint = point;
    update();
}
