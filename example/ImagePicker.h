#ifndef IMAGEPICKER_H
#define IMAGEPICKER_H
#pragma once

#include <QQuickItem>

/*!
 * \brief The ImagePicker class for opening iOS photos by using its native dialog
 */

class ImagePicker : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString selectedImage READ getSelectedImage WRITE setSelectedImage NOTIFY selectedImageChanged)

public:
    explicit ImagePicker(QQuickItem *parent = nullptr);

    QString getSelectedImage() const {
        return _selectedImage;
    }

    void setSelectedImage(const QString& selectedImage) {
        if(_selectedImage != selectedImage) {
            _selectedImage = selectedImage;
            emit selectedImageChanged(_selectedImage);
        }
    }

    Q_INVOKABLE void open();

private:
    void *m_delegate;
    QString _selectedImage = "";

signals:
    void selectedImageChanged(const QString& selectedImage);
};

#endif // IMAGEPICKER_H

