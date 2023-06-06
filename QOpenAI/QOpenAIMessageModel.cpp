#include "QOpenAIMessageModel.h"

QOpenAIMessageModel::QOpenAIMessageModel(QObject *parent) : QAbstractListModel(parent) {

}

int QOpenAIMessageModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return _messages.count();
}

QVariant QOpenAIMessageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    QOpenAIMessage* message = _messages.at(index.row());

    switch (role) {
    case Roles::Content:
        return message->getContent();
    case Roles::TimeStamp:
        return "";
    case Roles::MessageRole:
        return static_cast<int>(message->getRole());
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> QOpenAIMessageModel::roleNames() const
{
    return {
        { Roles::Content, "content" },
        { Roles::TimeStamp, "time" },
        { Roles::MessageRole, "role" }
    };
}

QList<QOpenAIMessage *>& QOpenAIMessageModel::getMessages() {
    return _messages;
}

void QOpenAIMessageModel::setMessages(QList<QOpenAIMessage*> messages) {
    if(_messages != messages) {
        _messages = messages;
        emit messagesChanged();
    }
}

void QOpenAIMessageModel::insertMessage(const QString& content, QOpenAIMessage::Role role)
{
    QOpenAIMessage* message = new QOpenAIMessage(content, role, this);
    beginInsertRows(QModelIndex(), _messages.count(), _messages.count());
    _messages.append(message);
    endInsertRows();
}
