```
impprt QOpenAI

QOpenAICompletions {
  id: openAICompletions

  endPoint: QOpenAI.Completions
  model: "text-davinci-003"
  prompt: ""
  suffix: ""
  maxTokens: 16
  temperature: 1.0
  topP: 1.0
  n: 1
  stream: false
  logProbs: 0
  echo: false
  stop: ""
  presencePenalty: 0.0
  frequencyPenalty: 0.0
  bestOf: 1
  logitBias: []
  user: ""

  onRequestFinished: function (jsonObject) {
    const content = jsonObject.choices[0].text
    console.log("Message:", content)
  }

  onRequestError: function (error) {
    console.log("Error message:", error)
  }
}

// somewhere in the Qml code
onSendClicked: function (prompt) {
  openAIChat.prompt = prompt
  openAIChat.sendRequest()
}
```