```
import QOpenAI

QOpenAIEmbeddings {
  id: openAIEmbeddings

  model: "text-embedding-ada-002"
  input: ""
  user: ""

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
  openAIEmbeddings.input = input
  openAIEmbeddings.sendRequest()
}
```
