```qml
  import QOpenAI

  QOpenAIImageVariations {
    id: openAIImageVariations

    endPoint: QOpenAI.ImageVariations

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
  onSendClicked: function(image) {
    openAIImageVariations.image = image
    openAIImageVariations.sendRequest()
  }
```

```c++
  #include <QOpenAIImageVariations.h>

  QOpenAIImageVariations imageVariations;
  imageVariations.setEndPoint(QOpenAI::EndPoints::ImageVariations);
  imageVariations.setImage(QDir::currentPath() + "/assets/arthur.png");
  
  connect(&imageVariations, &QOpenAIImageVariations::requestFinished, this, [&](const QJsonObject& response) {
    QJsonArray imageUrls = response.value("data").toArray();
    for (const QJsonValue& value : imageUrls) {
      QString url = value.toObject().value("url").toString();
      qDebug() << url;
    }
  });
  
  connect(&imageVariations, &QOpenAIImageVariations::requestError, this, [&](const QString& error) {
    qDebug() << error;
  });
  
  imageVariations.sendRequest();
```