```qml
  import QOpenAI

  QOpenAIModerations {
    id: openAIModerations

    endPoint: QOpenAI.Moderations
    model: "text-moderation-latest" // or "text-moderation-latest" 

    onRequestFinished: function (jsonObject) {
      const categories = jsonObject.results[0].categories
      for (var key in categories) {
        console.log(key + ": " + categories[key])
      }
    }

    onRequestError: function (error) {
      console.log("Error message:", error)
    }
  }

  // somewhere in the Qml code
  onSendClicked: function (input) {
    openAIModerations.input = input
    openAIModerations.sendRequest()
  }
```

```c++
  #include <QOpenAIModerations.h>

  QOpenAIModerations moderations;
  moderations.setEndPoint(QOpenAI::EndPoints::Moderations);
  moderations.setModel("text-moderation-latest"); // or text-moderation-stable
  moderations.setInput("I want to kill them.");

  connect(&moderations, &QOpenAIModerations::requestFinished, this, [&](const QJsonObject& response) {
    QJsonObject categoriesObject = response.value("results").toArray()[0].toObject().value("categories").toObject();
    for (auto it = categoriesObject.begin(); it != categoriesObject.end(); ++it) {
      qDebug() << it.key() << ":" << it.value().toBool();
    }
  });

  connect(&moderations, &QOpenAIModerations::requestError, this, [&](const QString& error) {
    qDebug() << error;
  });

  moderations.sendRequest();
```