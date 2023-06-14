#ifndef QOPENAIEMBEDDINGS_H
#define QOPENAIEMBEDDINGS_H

#include "QOpenAI.h"

class QOpenAIEmbeddings : public QOpenAI
{
    Q_OBJECT
    Q_PROPERTY(QString model READ getModel WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(QString input READ getInput WRITE setInput NOTIFY inputChanged)
    Q_PROPERTY(QString user READ getUser WRITE setUser NOTIFY userChanged)
    QML_ELEMENT

public:
    explicit QOpenAIEmbeddings(QObject *parent = nullptr);
    explicit QOpenAIEmbeddings(const QString& model, const QString& input, QObject *parent = nullptr);

    Q_INVOKABLE void sendRequest() override;

    QString getModel() const;
    void setModel(const QString& model);

    QString getInput() const;
    void setInput(const QString& input);

    QString getUser() const;
    void setUser(const QString& user);

private:
    QString m_model = "";
    QString m_input = "";
    QString m_user = "";

signals:
    void modelChanged();
    void inputChanged();
    void userChanged();
};

#endif // QOPENAIEMBEDDINGS_H
