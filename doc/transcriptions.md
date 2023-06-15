```
import QOpenAI

QOpenAIAudio {
  id: openAIAudioTranscriptions

  endPoint: QOpenAI.Transcriptions

  model: "whisper-1"
  responseFormat: "json"
  temperature: 1.0

  onRequestFinished: function (jsonObject) {
    const content = jsonObject.text
    console.log("Message:", content)
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
  // stop recording and then:
  openAIAudioTranscriptions.file = audioFile
  openAIAudioTranscriptions.sendRequest()
}
  
```