#ifndef QOPENAIMODERATIONS_H
#define QOPENAIMODERATIONS_H

#include "QOpenAI.h"

class QOpenAIModerations : public QOpenAI
{
    Q_OBJECT
    Q_PROPERTY(QString input READ getInput WRITE setInput NOTIFY inputChanged)
    Q_PROPERTY(QString model READ getModel WRITE setModel NOTIFY modelChanged)
    QML_ELEMENT

public:
    explicit QOpenAIModerations(QObject *parent = nullptr);
    explicit QOpenAIModerations(const QString& input, QObject *parent = nullptr);

    Q_INVOKABLE void sendRequest() override;

    QString getInput() const;
    void setInput(const QString& input);

    QString getModel() const;
    void setModel(const QString& model);

private:
    QString m_input = "";
    QString m_model = "";

signals:
    void inputChanged();
    void modelChanged();

};

#endif // QOPENAIMODERATIONS_H
