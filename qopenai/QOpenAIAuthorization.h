#ifndef QOPENAIAUTHORIZATION_H
#define QOPENAIAUTHORIZATION_H

#include "QtCore/qdebug.h"
#include <QString>

class QOpenAIAuthorization
{
public:
    QOpenAIAuthorization() = default;
    ~QOpenAIAuthorization() {}

    QOpenAIAuthorization(QOpenAIAuthorization const&) = delete;
    void operator=(QOpenAIAuthorization const&) = delete;

    QOpenAIAuthorization(QOpenAIAuthorization&&) = delete;
    void operator=(QOpenAIAuthorization&&) = delete;

    static QOpenAIAuthorization& Authorizer() {
        static QOpenAIAuthorization instance;
        return instance;
    }

    const QString getKey() const {
        const auto key = qEnvironmentVariable("OPENAI_API_KEY");
        return key;
    }

    bool setKey(const QString& key) {
        if(!key.isEmpty()) {
            return qputenv("OPENAI_API_KEY", key.toStdString().c_str());
        }
        return false;
    }
};

#endif // QOPENAIAUTHORIZATION_H
