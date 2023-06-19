```qml
  import QOpenAI

  QOpenAIChat {
    id: openAIChatCompletions

    endPoint: QOpenAI.ChatCompletions
    model: "gpt-3.5-turbo"

    onRequestFinished: function (jsonObject) {
      const content = jsonObject.choices[0].message.content
      openAIChatCompletions.messageModel.insertMessage(content, QOpenAIMessage.Role.Assistant)
      console.log("Content:", content)
    }

    onRequestError: function (error) {
      console.log("Error:", error)
    }
  }

  // somewhere in the Qml code
  onSendClicked: function (message) {
    openAIChatCompletions.messageModel.insertMessage(message, QOpenAIMessage.Role.User)
    openAIChat.systemMessage = "Act as a friend."
    openAIChatCompletions.sendRequest()
  }
```

```c++
  #include <QOpenAIChat.h>

  // somewhere in the C++ code, make sure the instance is in scope
  QOpenAIChat chatCompletions;
  chatCompletions.setEndPoint(QOpenAI::EndPoints::ChatCompletions);
  chatCompletions.setModel("gpt-3.5-turbo");
  chatCompletions.setSystemMessage("Act as a friend.");
  chatCompletions.getMessageModel()->insertMessage("What is up?", QOpenAIMessage::Role::User);

  connect(&chatCompletions, &QOpenAIChat::requestFinished, this, [&](const QJsonObject& response) {
    QString content = responseJson.value("choices").toArray()[0].toObject().value("message").toObject().value("content").toString();
    chatCompletions.getMessageModel()->insertMessage(content, QOpenAIMessage::Role::Assistant);
    qDebug() << content;
  });

  connect(&chatCompletions, &QOpenAIChat::requestError, this, [&](const QString& error) {
    qDebug() << error;
  });

  chatCompletions.sendRequest();
```
- For continuous conversation, the message to be send and the message to be returned must be added to QOpenAIChat's message model.