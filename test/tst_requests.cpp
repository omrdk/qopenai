#include <QTest>
#include <QSignalSpy>

#include <QOpenAICompletions.h>
#include <QOpenAIChat.h>
#include <QOpenAIEdits.h>
#include <QOpenAIImage.h>
#include <QOpenAIImageEdits.h>
#include <QOpenAIImageVariations.h>
#include <QOpenAIAudio.h>
#include <QOpenAIEmbeddings.h>
#include <QOpenAIModerations.h>

class EndPointRequest : public QObject
{
    Q_OBJECT

public:
    EndPointRequest() {};
    ~EndPointRequest() {};

private slots:
    void testCompletionsRequest();
    void testChatCompletionsRequest();
    void testEditsRequest();
    void testImageGenerationsRequest();
    void testImageEdits();
    void testImageVariations();
    void testTransciptions();
    void testTranslations();
    void testEmbeddings();
    void testModerations();
};

void EndPointRequest::testCompletionsRequest() {
    QOpenAICompletions completions;
    completions.setEndPoint(QOpenAI::EndPoints::Completions);
    completions.setModel("text-davinci-003");
    completions.setPrompt("I am a");

    QSignalSpy finishedSpy(&completions, &QOpenAICompletions::requestFinished);
    QSignalSpy errorSpy(&completions, &QOpenAICompletions::requestError);

    completions.sendRequest();
    finishedSpy.wait(10000);

    if (!errorSpy.isEmpty()) {
        QString error = errorSpy.at(0).at(0).toString();
        QFAIL(error.toStdString().c_str());
    }
}

void EndPointRequest::testChatCompletionsRequest() {
QOpenAIChat chatCompletions;
chatCompletions.setEndPoint(QOpenAI::EndPoints::ChatCompletions);
chatCompletions.setModel("gpt-3.5-turbo");
chatCompletions.setSystemMessage("Act as a friend.");
chatCompletions.getMessageModel()->insertMessage("What is up?", QOpenAIMessage::Role::User);

QSignalSpy finishedSpy(&chatCompletions, &QOpenAIChat::requestFinished);
QSignalSpy errorSpy(&chatCompletions, &QOpenAIChat::requestError);

chatCompletions.sendRequest();
finishedSpy.wait(10000);

if (!errorSpy.isEmpty()) {
    QString error = errorSpy.at(0).at(0).toString();
    QFAIL(error.toStdString().c_str());
}
}

void EndPointRequest::testEditsRequest() {
    QOpenAIEdits edits;
    edits.setEndPoint(QOpenAI::EndPoints::Edits);
    edits.setModel("text-davinci-edit-001");  // or code-davinci-edit-001
    edits.setInstruction("Fix the grammer.");
    edits.setInput("I has been doing sth.");

    QSignalSpy finishedSpy(&edits, &QOpenAIEdits::requestFinished);
    QSignalSpy errorSpy(&edits, &QOpenAIEdits::requestError);

    edits.sendRequest();
    finishedSpy.wait(10000);

    if (!errorSpy.isEmpty()) {
        QString error = errorSpy.at(0).at(0).toString();
        QFAIL(error.toStdString().c_str());
    }
}

void EndPointRequest::testImageGenerationsRequest() {
    QOpenAIImage imageGenerations;
    imageGenerations.setEndPoint(QOpenAI::EndPoints::ImageGenerations);
    imageGenerations.setPrompt("Draw an 3D cube.");

    QSignalSpy finishedSpy(&imageGenerations, &QOpenAIImage::requestFinished);
    QSignalSpy errorSpy(&imageGenerations, &QOpenAIImage::requestError);

    imageGenerations.sendRequest();
    finishedSpy.wait(10000);

    if (!errorSpy.isEmpty()) {
        QString error = errorSpy.at(0).at(0).toString();
        QFAIL(error.toStdString().c_str());
    }
}

void EndPointRequest::testImageEdits() {
    QOpenAIImageEdits imageEdits;
    imageEdits.setEndPoint(QOpenAI::EndPoints::ImageEdits);
    imageEdits.setImage(QDir::currentPath() + "/assets/arthur.png");
    imageEdits.setMask(QDir::currentPath() + "/assets/mask.png");
    imageEdits.setPrompt("A man who has purple eyes.");

    QSignalSpy finishedSpy(&imageEdits, &QOpenAIImageEdits::requestFinished);
    QSignalSpy errorSpy(&imageEdits, &QOpenAIImageEdits::requestError);

    imageEdits.sendRequest();
    finishedSpy.wait(10000);

    if (!errorSpy.isEmpty()) {
        QString error = errorSpy.at(0).at(0).toString();
        QFAIL(error.toStdString().c_str());
    }
}

void EndPointRequest::testImageVariations() {
    QOpenAIImageVariations imageVariations;
    imageVariations.setEndPoint(QOpenAI::EndPoints::ImageVariations);
    imageVariations.setImage(QDir::currentPath() + "/assets/arthur.png");

    QSignalSpy finishedSpy(&imageVariations, &QOpenAIImageVariations::requestFinished);
    QSignalSpy errorSpy(&imageVariations, &QOpenAIImageVariations::requestError);

    imageVariations.sendRequest();
    finishedSpy.wait(10000);

    if (!errorSpy.isEmpty()) {
        QString error = errorSpy.at(0).at(0).toString();
        QFAIL(error.toStdString().c_str());
    }
}

void EndPointRequest::testTransciptions() {
    QOpenAIAudio transcriptions;
    transcriptions.setEndPoint(QOpenAI::EndPoints::Transcriptions);
    transcriptions.setModel("whisper-1");
    transcriptions.setFile(QDir::currentPath() + "/assets/audio.m4a"); // extension depend on OS since default selected
    transcriptions.setLanguage("tr");

    QSignalSpy finishedSpy(&transcriptions, &QOpenAIAudio::requestFinished);
    QSignalSpy errorSpy(&transcriptions, &QOpenAIAudio::requestError);

    transcriptions.sendRequest();
    finishedSpy.wait(10000);

    if (!errorSpy.isEmpty()) {
        QString error = errorSpy.at(0).at(0).toString();
        QFAIL(error.toStdString().c_str());
    }
}

void EndPointRequest::testTranslations() {
    QOpenAIAudio translations;
    translations.setEndPoint(QOpenAI::EndPoints::Translations);
    translations.setModel("whisper-1");
    translations.setFile(QDir::currentPath() + "/assets/audio.m4a"); // extension depend on OS since default selected

    QSignalSpy finishedSpy(&translations, &QOpenAIAudio::requestFinished);
    QSignalSpy errorSpy(&translations, &QOpenAIAudio::requestError);

    translations.sendRequest();
    finishedSpy.wait(10000);

    if (!errorSpy.isEmpty()) {
        QString error = errorSpy.at(0).at(0).toString();
        QFAIL(error.toStdString().c_str());
    }
}

void EndPointRequest::testEmbeddings() {
    QOpenAIEmbeddings embeddings;
    embeddings.setEndPoint(QOpenAI::EndPoints::Embeddings);
    embeddings.setModel("text-embedding-ada-002");
    embeddings.setInput("The food was delicious and the waiter...");

    QSignalSpy finishedSpy(&embeddings, &QOpenAIEmbeddings::requestFinished);
    QSignalSpy errorSpy(&embeddings, &QOpenAIEmbeddings::requestError);

    embeddings.sendRequest();
    finishedSpy.wait(10000);

    if (!errorSpy.isEmpty()) {
        QString error = errorSpy.at(0).at(0).toString();
        QFAIL(error.toStdString().c_str());
    }
}

void EndPointRequest::testModerations() {
    QOpenAIModerations moderations;
    moderations.setEndPoint(QOpenAI::EndPoints::Moderations);
    moderations.setModel("text-moderation-latest"); // or text-moderation-stable
    moderations.setInput("I want to kill them.");

    QSignalSpy finishedSpy(&moderations, &QOpenAIModerations::requestFinished);
    QSignalSpy errorSpy(&moderations, &QOpenAIModerations::requestError);

    moderations.sendRequest();
    finishedSpy.wait(10000);

    if (!errorSpy.isEmpty()) {
        QString error = errorSpy.at(0).at(0).toString();
        QFAIL(error.toStdString().c_str());
    }
}

QTEST_MAIN(EndPointRequest)

#include "tst_requests.moc"
