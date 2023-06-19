```qml
  import QOpenAI

  QOpenAIImage {
    id: openAIImage

    endPoint: QOpenAI.ImageGenerations

    onRequestFinished: function (jsonObject) {
      let imageUrls = jsonObject.data
      for (var i = 0; i < imageUrls.length; i++) {
        let url = imageUrls[i].url
        console.log(url)
      }
    }

    onRequestError: function (error) {
      console.log("Error:", error)
    }
  }

  // somewhere in the Qml code
  onSendClicked: function(prompt) {
    openAIImage.prompt = prompt
    openAIImage.sendRequest()
  }
```

```c++
  #include <QOpenAIImage.h>

  QOpenAIImage imageGenerations;
  imageGenerations.setEndPoint(QOpenAI::EndPoints::ImageGenerations);
  imageGenerations.setPrompt("Draw an 3D cube.");
  imageGenerations.setN(2);
  
  connect(&imageGenerations, &QOpenAIImage::requestFinished, this, [&](const QJsonObject& response) {
    QJsonArray imageUrls = response.value("data").toArray();
    for (const QJsonValue& value : imageUrls) {
      QString url = value.toObject().value("url").toString();
      qDebug() << url;
    }
  });
  
  connect(&imageGenerations, &QOpenAIImage::requestError, this, [&](const QString& error) {
    qDebug() << error;
  });
  
  imageGenerations.sendRequest();
```