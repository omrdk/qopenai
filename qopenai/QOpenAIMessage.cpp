#include "QOpenAIMessage.h"

QOpenAIMessage::QOpenAIMessage(const QString &content, Role role, QObject *parent) : _content(content), _role(role), QObject{parent} {

}

const QString& QOpenAIMessage::getContent() const
{
    return _content;
}

QOpenAIMessage::Role QOpenAIMessage::getRole() const
{
    return _role;
}

QString QOpenAIMessage::getRoleString() const
{
    switch (_role) {
    case Role::Undefined:
        break;
    case Role::User:
        return "user";
    case Role::Assistant:
        return "assistant";
    case Role::System:
        return "system";
    }
    return "";
}
