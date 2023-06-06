#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <QQuickItem>
#include <QtQml>
#include <QObject>

class EventListener : public QObject {
    Q_OBJECT
protected:
    bool eventFilter(QObject *obj, QEvent *event) override {
        if (event->type() == QEvent::InputMethodQuery) {
            QInputMethodQueryEvent *imEvt = static_cast<QInputMethodQueryEvent *>(event);
            if (imEvt->queries() == Qt::InputMethodQuery::ImCursorRectangle) {
                imEvt->setValue(Qt::InputMethodQuery::ImCursorRectangle, QRectF());
                return true;
            }
        }
        return QObject::eventFilter(obj, event);
    }
};

class EventInstaller : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
   // explicit EventInstaller(QObject* parent = nullptr) { ; }

    Q_INVOKABLE void setupEventFilter(QQuickItem *item) {
        static thread_local EventListener imf;
        item->installEventFilter(&imf);
    }
};

#endif // EVENTLISTENER_H
