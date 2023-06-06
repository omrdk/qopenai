#include "QOpenAIText.h"

QOpenAIText::QOpenAIText(QObject *parent) : QOpenAI{parent} {

}

void QOpenAIText::sendRequest(const QString &content) {
    QNetworkRequest request(getUrl(_endPoint));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + OPENAI_API_KEY).toUtf8());
    QByteArray requestBodyBytes = genRequestBody(content);
    QNetworkReply *reply = _networkManager->post(request, requestBodyBytes);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            QJsonDocument responseJson = QJsonDocument::fromJson(response);
            QString content;

            switch (_endPoint) {
            case QOpenAI::EndPoints::ChatCompletions:
                content = responseJson.object().value("choices").toArray()[0].toObject().value("message").toObject().value("content").toString();
                //QString role = responseJson.object().value("choices").toArray()[0].toObject().value("message").toObject().value("role").toString();
                break;
            default:
                content = responseJson.object().value("choices").toArray()[0].toObject().value("text").toString();
            }
            emit requestFinished(content);
        } else {
            qDebug() << "REQUEST ERR: " << reply->error();
            emit requestError(reply->errorString());
        }
        reply->deleteLater();
    });
}

QByteArray QOpenAIText::genRequestBody(const QString &content) const {
    QJsonObject body;
    body.insert("model", _model);
    switch (_endPoint) {
        case QOpenAI::EndPoints::Completions: {
            body.insert("prompt", content);
            body.insert("suffix", _suffix);
            body.insert("max_tokens", _maxTokens);
            body.insert("temperature", _temperature);
            body.insert("top_p", _topP);
            body.insert("n", _n);
            body.insert("stream", _stream);
            body.insert("logprobs", _logProbs);
            body.insert("echo", _echo);
            body.insert("stop", _stop);
            body.insert("presence_penalty", _presencePenalty);
            body.insert("frequency_penalty", _frequencyPenalty);
            body.insert("best_of", _bestOf);
            //body.insert("logit_bias", _logitBias);
            break;
        }
        case QOpenAI::EndPoints::ChatCompletions: {
            QJsonArray messagesBranch;
            const auto messages = _messageModel->getMessages();
            for(auto message: messages) { // do not insert message if role is undefined, there is no system messages yet since user role can override it easily
                QJsonObject branch;
                branch.insert("role", message->getRoleString());
                qDebug() << message->getContent();
                branch.insert("content", message->getContent());
                //branch.insert("name", "John_Doe");
                messagesBranch.append(branch);
            }
            body.insert("messages", messagesBranch);
            body.insert("temperature", _temperature);
            body.insert("top_p", _topP);
            body.insert("n", _n);
            body.insert("stream", _stream);
            body.insert("stop", _stop);
            body.insert("max_tokens", _maxTokens);
            body.insert("presence_penalty", _presencePenalty);
            body.insert("frequency_penalty", _frequencyPenalty);
            //body.insert("logit_bias", _logitBias);
            break;
        }
        case QOpenAI::EndPoints::Edits: {
            body.insert("input", content); // TODO delete imput class member
            body.insert("instruction", _instruction);
            body.insert("temperature", _temperature);
            body.insert("top_p", _topP);
            body.insert("n", _n);
            break;
        }
        default:
            break;
    }
    body.insert("user", _user);
    QJsonDocument json;

    json.setObject(body);
    qDebug() << json; // - !
    QByteArray jsonBytes = json.toJson();
    return jsonBytes;
}
