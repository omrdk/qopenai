```qml
  import QOpenAI

  QOpenAICompletions {
    id: openAICompletions

    endPoint: QOpenAI.Completions
    model: "text-davinci-003"

    onRequestFinished: function (jsonObject) {
      const content = jsonObject.choices[0].text
      console.log("Content:", content)
    }

    onRequestError: function (error) {
      console.log("Error:", error)
    }
  }

  // somewhere in the Qml code
  onSendClicked: function (prompt) {
    openAICompletions.prompt = prompt
    openAICompletions.sendRequest()
  }
```

```c++
  #include <QOpenAICompletions.h>

  // somewhere in the C++ code, make sure the instance is in scope
  QOpenAICompletions completions;
  completions.setEndPoint(QOpenAI::EndPoints::Completions);
  completions.setModel("text-davinci-003");
  completions.setPrompt("I am a");

  connect(&completions, &QOpenAICompletions::requestFinished, this, [&](const QJsonObject& response) {
    QString content = response.value("choices").toArray()[0].toObject().value("text").toString();
    qDebug() << content;
  });

  connect(&completions, &QOpenAICompletions::requestError, this, [&](const QString& error) {
    qDebug() << error;
  });

  completions.sendRequest();
```