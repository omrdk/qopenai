#ifndef INTERACTIVEIMAGE_H
#define INTERACTIVEIMAGE_H


#include <QQuickPaintedItem>
#include <QObject>
#include <QImage>
#include <QPainter>

/*!
 * \brief Costum QQuickItem to remove alpha channel partially on the loaded image
 */
class InteractiveImage : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString source READ getSource WRITE setSource NOTIFY sourceChanged);
    QML_ELEMENT

public:
    explicit InteractiveImage(QQuickPaintedItem* parent = nullptr);

    void paint(QPainter *painter) override;

    QString getSource() const;
    void setSource(const QString& source);

    void removeAlphaFromImage(const QPointF& point);

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

    void refreshAndDuplicate();

signals:
    void sourceChanged();
};

#endif // INTERACTIVEIMAGE_H
