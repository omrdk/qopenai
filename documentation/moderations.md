```
import QOpenAI

QOpenAIModerations {
  id: openAIModerations

  model: "text-moderation-latest" // text-moderation-stable
  input: ""

  onRequestFinished: function (jsonObject) {
    const content = jsonObject....
    console.log("Message:", content)
  }

  onRequestError: function (error) {
    console.log("Error message:", error)
  }
}

// somewhere in the Qml code
onSendClicked: function (input) {
  openAIModerations.input = input
  openAIModerations.sendRequest()
}
```
