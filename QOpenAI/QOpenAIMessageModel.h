#ifndef QOPENAIMESSAGEMODEL_H
#define QOPENAIMESSAGEMODEL_H
#pragma once

#include <QAbstractListModel>
#include <QtQml>

#include "QOpenAIMessage.h"

class QOpenAIMessageModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QList<QOpenAIMessage*> messages READ getMessages WRITE setMessages NOTIFY messagesChanged)
    QML_ELEMENT

public:
    enum Roles {
        Content,
        TimeStamp,
        MessageRole
    };

    explicit QOpenAIMessageModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    QList<QOpenAIMessage *>& getMessages();
    void setMessages(QList<QOpenAIMessage*> messages);

public slots:
    void insertMessage(const QString& content, QOpenAIMessage::Role role);

private:
    QList<QOpenAIMessage*> _messages;

signals:
    void messagesChanged();
};

#endif // MESSAGEMODEL_H
