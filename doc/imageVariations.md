```
import QOpenAI

QOpenAIImageVariations {
  id: openAIImageVariations

  endPoint: QOpenAI.ImageVariations
  image: ""
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
onSendClicked: function(image) {
  openAIImageVariations.image = image
  openAIImageVariations.sendRequest()
}
```