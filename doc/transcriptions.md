```qml
  import QOpenAI

  QOpenAIAudio {
    id: openAIAudioTranscriptions

    endPoint: QOpenAI.Transcriptions
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

  QOpenAIAudio transcriptions;
  transcriptions.setEndPoint(QOpenAI::EndPoints::Transcriptions);
  transcriptions.setModel("whisper-1");
  transcriptions.setFile(QDir::currentPath() + "/assets/audio.m4a");
  transcriptions.setLanguage("tr");
  
  connect(&transcriptions, &QOpenAIAudio::requestFinished, this, [&](const QJsonObject& response) {
    QString content = response.value("text").toString();
    qDebug() << content;
  });
  
  connect(&transcriptions, &QOpenAIAudio::requestError, this, [&](const QString& error) {
    qDebug() << error;
  });
  
  transcriptions.sendRequest();
```