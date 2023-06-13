```
import QOpenAI

QOpenAIImageEdits {
  id: openAIImageEdits

  endPoint: QOpenAI.ImageEdits
  image: ""
  mask: ""
  prompt: ""
  n: 1
  imageSize: "512x512"
  responseFormat: "url"
  user: ""

  onRequestFinished: function (jsonObject) {
    let imageUrls = jsonObject.data
    for (var i = 0; i < imageUrls.length; i++) {
      let url = imageUrls[i].url
      console.log(url)
    }
  }

  onRequestError: function (error) {
    console.log("Error message:", error)
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