#ifndef INTERACTIVEIMAGE_H
#define INTERACTIVEIMAGE_H

#include <QQuickPaintedItem>
#include <QObject>
#include <QImage>
#include <QPainter>
#include <QStandardPaths>
#include <QFileInfo>

/*!
 * \brief Costum QQuickItem to remove alpha channel partially from an image in order to create the mask image
 */
class InteractiveImage : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString source READ getSource WRITE setSource NOTIFY sourceChanged);
    Q_PROPERTY(QString imagePath MEMBER _imagePath NOTIFY imagePathChanged);
    Q_PROPERTY(QString maskPath MEMBER _maskPath NOTIFY maskPathChanged);
    QML_ELEMENT

public:
    explicit InteractiveImage(QQuickPaintedItem* parent = nullptr);

    void paint(QPainter *painter) override;

    QString getSource() const;
    void setSource(const QString& source);

    Q_INVOKABLE QString convertToPng(const QString& imagePath);
    Q_INVOKABLE bool isFormatSupported(const QString& imagePath) const;

protected:
    void mousePressEvent(QMouseEvent * event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void touchEvent(QTouchEvent *event) override;

private:
    QString _source = "";
    QImage _image;
    qreal _imageY = 0.0;
    QPointF _prevPoint;
    QString _imagePath = "";
    QString _maskPath = "";

    bool isPngImage(const QString& imagePath) const;
    void removeAlphaFromImage(const QPointF& point);
    void updateImage();
    void createDuplicates();

signals:
    void sourceChanged();
    void imagePathChanged();
    void maskPathChanged();
    void duplicateImagesCreated(const QString& imagePath, const QString& maskPath);

};

#endif // INTERACTIVEIMAGE_H
