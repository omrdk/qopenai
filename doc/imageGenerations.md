```
import QOpenAI

QOpenAIImage {
  id: openAIImage

  endPoint: QOpenAI.ImageGenerations
  prompt: ""
  n: 1
  imageSize: "512x512"
  responseFormat: "url"
  user: ""

  onRequestFinished: function (jsonObject) {
    let imageUrls = jsonObject.data
    for (var i = 0; i < imageUrls.length; i++) {
      let url = imageUrls[i].url
      openAIImage.messageModel.insertMessage(url, QOpenAIMessage.Role.ASSISTANT)
    }
  }

  onRequestError: function (error) {
    console.log("Error message:", error)
  }
}

// somewhere in the Qml code
onSendClicked: function(prompt) {
  openAIImage.prompt = prompt
  openAIImage.sendRequest()
}
```