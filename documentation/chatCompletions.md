```
import QOpenAI

QOpenAIChat {
  id: openAIChat

  endPoint: QOpenAI.ChatCompletions
  model: "gpt-3.5-turbo"
  temperature: 1.0
  topP: 1.0
  n: 1
  stream: false
  stop: ""
  maxTokens: 2048
  presencePenalty: 0.0
  frequencyPenalty: 0.0
  logitBias: []
  user: ""
  systemMessage: "" // system message will be added to the model as firstmessage

  onRequestFinished: function (jsonObject) {
    const content = jsonObject.choices[0].message.content
    console.log("Message:", content)
    // need to add message to its model for continuous conversation
    openAIChat.messageModel.insertMessage(content, QOpenAIMessage.Role.Assistant)
  }

  onRequestError: function (error) {
    console.log("Error message:", error)
  }
}

// somewhere in the Qml code
onSendClicked: function (message) {
  openAIChat.messageModel.insertMessage(message, QOpenAIMessage.Role.User)
  openAIChat.sendRequest()
}
```