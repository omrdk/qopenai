```qml
  import QOpenAI

  QOpenAIImageEdits {
    id: openAIImageEdits

    endPoint: QOpenAI.ImageEdits

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
  onSendClicked: function(prompt, imagePath, maskPath) {
    openAIImageEdits.image = imagePath
    openAIImageEdits.mask = maskPath
    openAIImageEdits.prompt = prompt
    openAIImageEdits.sendRequest()
  }
```

```c++
  #include <QOpenAIImageEdits.h>

  QOpenAIImageEdits imageEdits;
  imageEdits.setEndPoint(QOpenAI::EndPoints::ImageEdits);
  imageEdits.setImage(QDir::currentPath() + "/assets/arthur.png");
  imageEdits.setMask(QDir::currentPath() + "/assets/mask.png");
  imageEdits.setPrompt("A man who has purple eyes.");
  
  connect(&imageEdits, &QOpenAIImageEdits::requestFinished, this, [&](const QJsonObject& response) {
  QJsonArray imageUrls = response.value("data").toArray();
    for (const QJsonValue& value : imageUrls) {
      QString url = value.toObject().value("url").toString();
      qDebug() << url;
    }
  });
  
  connect(&imageEdits, &QOpenAIImageEdits::requestError, this, [&](const QString& error) {
    qDebug() << error;
  });
  
  imageEdits.sendRequest();
```