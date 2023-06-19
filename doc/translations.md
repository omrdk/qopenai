```qml
  import QOpenAI

  QOpenAIAudio {
    id: openAIAudioTranscriptions

    endPoint: QOpenAI.Translations
    model: "whisper-1"

    onRequestFinished: function (jsonObject) {
      const content = jsonObject.text
      console.log("Content:", content)
    }

    onRequestError: function (error) {
      console.log("Error message:", error)
    }
  }

  // somewhere in the Qml code
  onRecordingStarted: {
    // start to record audio
  }

  onRecordingFinished: function(audioFile){
    // stop recording, then:
    openAIAudioTranscriptions.file = audioFile
    openAIAudioTranscriptions.sendRequest()
  }
  
```

```c++
  #include <QOpenAIAudio.h>

  QOpenAIAudio translations;
  translations.setEndPoint(QOpenAI::EndPoints::Transcriptions);
  translations.setModel("whisper-1");
  translations.setFile(QDir::currentPath() + "/assets/audio.m4a");
  translations.setLanguage("tr");
  
  connect(&translations, &QOpenAIAudio::requestFinished, this, [&](const QJsonObject& response) {
    QString content = response.value("text").toString();
    qDebug() << content;
  });
  
  connect(&translations, &QOpenAIAudio::requestError, this, [&](const QString& error) {
    qDebug() << error;
  });
  
  translations.sendRequest();
```