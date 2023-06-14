```
import QOpenAI

QOpenAIEdits {
  id: openAIEdits

  endPoint: QOpenAI.Edits
  model: "text-davinci-edit-001" // code-davinci-edit-001
  input: ""
  instruction: "Fix the grammer"
  n: 1
  temperature: 1.0
  topP: 1.0

  onRequestFinished: function (jsonObject) {
    const content = jsonObject.choices[0].text
    console.log("Message:", content)
  }

  onRequestError: function (error) {
    console.log("Error message:", error)
  }

// somewhere in the Qml code
onSendClicked: function (input) {
  openAIEdits.input = input
  openAIEdits.sendRequest()
}
```