#ifndef QOPENAIMESSAGE_H
#define QOPENAIMESSAGE_H
#pragma once

#include <QtQml>
#include <QObject>

class QOpenAIMessage : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Not creatable")

public:
    enum class Role {
        Undefined,
        System,
        User,
        Assistant
    };
    Q_ENUM(Role)

    explicit QOpenAIMessage(const QString& content = nullptr, Role role = Role::Undefined, QObject *parent = nullptr);

    const QString& getContent() const;
    Role getRole() const;
    QString getRoleString() const;

private:
    QString _content = "";
    Role _role = Role::User;

};

#endif // QOPENAIMESSAGE_H

