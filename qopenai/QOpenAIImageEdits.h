#ifndef QOPENAIIMAGEEDITS_H
#define QOPENAIIMAGEEDITS_H

#include "QOpenAI.h"

class QOpenAIImageEdits : public QOpenAI
{
    Q_OBJECT
    Q_PROPERTY(QString image READ getImage WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(QString mask READ getMask WRITE setMask NOTIFY maskChanged)
    Q_PROPERTY(QString prompt READ getPrompt WRITE setPrompt NOTIFY promptChanged)
    Q_PROPERTY(int n READ getN WRITE setN NOTIFY nChanged)
    Q_PROPERTY(QString size READ getSize WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(QString responseFormat READ getResponseFormat WRITE setResponseFormat NOTIFY responseFormatChanged)
    Q_PROPERTY(QString user READ getUser WRITE setUser NOTIFY userChanged)
    QML_ELEMENT

public:
    explicit QOpenAIImageEdits(QObject *parent = nullptr);
    explicit QOpenAIImageEdits(const QString& image, const QString& prompt, QObject *parent = nullptr);

    Q_INVOKABLE void sendRequest() override;

    QString getImage() const;
    void setImage(const QString& image);

    QString getMask() const;
    void setMask(const QString& mask);

    QString getPrompt() const;
    void setPrompt(const QString& prompt);

    int getN() const;
    void setN(int n);

    QString getSize() const;
    void setSize(const QString& size);

    QString getResponseFormat() const;
    void setResponseFormat(const QString& responseFormat);

    QString getUser() const;
    void setUser(const QString& user);

private:
    QString m_image = "";
    QString m_mask = "";
    QString m_prompt = "";
    int m_n = 1;
    QString m_size = "1024x1024";
    QString m_responseFormat = "url";
    QString m_user = "";

signals:
    void imageChanged();
    void maskChanged();
    void promptChanged();
    void nChanged();
    void sizeChanged();
    void responseFormatChanged();
    void userChanged();

};

#endif // QOPENAIIMAGEEDITS_H
