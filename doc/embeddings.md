```qml
  import QOpenAI

  QOpenAIEmbeddings {
    id: openAIEmbeddings

    property list<double> embeddings

    endPoint: QOpenAI.Embeddings
    model: "text-embedding-ada-002"

    onRequestFinished: function (jsonObject) {
      let embedding = jsonObject.data[0].embedding
      console.log(embedding)
    }

    onRequestError: function (error) {
      console.log("Error:", error)
    }
  }

  // somewhere in the Qml code
  onSendClicked: function (input) {
    openAIEmbeddings.input = input
    openAIEmbeddings.sendRequest()
  }
```

```c++
  #include <QOpenAIEmbeddings.h>

  QOpenAIEmbeddings embeddings;
  embeddings.setEndPoint(QOpenAI::EndPoints::Embeddings);
  embeddings.setModel("text-embedding-ada-002");
  embeddings.setInput("The food was delicious and the waiter...");
  
  connect(&embeddings, &QOpenAIEmbeddings::requestFinished, this, [&](const QJsonObject& response) {
    qDebug() << response.value("data").toArray()[0].toObject().value("embedding").toArray();
  });
  
  connect(&embeddings, &QOpenAIEmbeddings::requestError, this, [&](const QString& error) {
    qDebug() << error;
  });
  
  embeddings.sendRequest();
```