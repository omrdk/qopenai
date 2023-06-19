```qml
  import QOpenAI

  QOpenAIEdits {
    id: openAIEdits

    endPoint: QOpenAI.Edits
    model: "text-davinci-edit-001" // or code-davinci-edit-001
    instruction: chatPage.instructionItem.text

    onRequestFinished: function (jsonObject) {
      const content = jsonObject.choices[0].text
      console.log("Content:", content)
    }

    onRequestError: function (error) {
      console.log("Error:", error)
    }
  }

  // somewhere in the Qml code
  onSendClicked: function (input) {
    openAIEdits.input = input
    openAIEdits.sendRequest()
  }
```

```c++
  #include <QOpenAIEdits.h>

  // somewhere in the C++ code, make sure the instance is in scope
  QOpenAIEdits edits;
  edits.setEndPoint(QOpenAI::EndPoints::Edits);
  edits.setModel("text-davinci-edit-001");  // or code-davinci-edit-001
  edits.setInstruction("Fix the grammer.");
  edits.setInput("I has been doing sth.");

  connect(&edits, &QOpenAIEdits::requestFinished, this, [&](const QJsonObject& response) {
    QString content = responseJson.object().value("choices").toArray()[0].toObject().value("text").toString();
    qDebug() << content;
  });

  connect(&edits, &QOpenAIEdits::requestError, this, [&](const QString& error) {
    qDebug() << error;
  });

  edits.sendRequest();
```
