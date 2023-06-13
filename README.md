## `Description`

OpenAI plugin for QML or a library for C++ that could be used as a templete in Qt-based projects.

## `Features`

- [x] [Completions]()
- [X] [Chat Completions]()
- [X] [Edits]()
- [x] [Image Generations]()
- [x] [Image Edits]()
- [x] [Image Variations]() 
- [x] [Embeddings]() 
- [x] [Transcriptions]() 
- [x] [Translations]() 
- [x] [Moderation]() 
- [ ] [Files]() 
- [ ] [Fine Tunes]() 

## `Authentication`

Example checks if the OPENAI_API_KEY environment variable before starting the application. So, add the environment variable to the selected kit's run configuration on Qt Creator:

Set OPENAI_API_KEY in Qt Creator to run the example to interact with the OpenAI endpoints:

Projects -> Your kit -> Run -> Environment -> Details -> Add: OPENAI_API_KEY="your-key"

## `How to link qopenai`

- Copy `qopenai` folder under your project's root directory
- Add `qopenai` as a sub-directory in project's root CMakeLists.txt file after creating executable for your target(see qt_add_executable):
```
add_subdirectory(qopenai)
```
- Link required Qt modules and `qopenaiplugin` to the target:
```
target_link_libraries(appexample PRIVATE Qt::Quick Qt::Core Qt::Network Qt::Multimedia qopenaiplugin)
```
- Should you be interested in using this plugin as a library and instantiate them in C++, link it to the target with qopenai name instead of qopenaiplugin as below:
```
target_link_libraries(appexample PRIVATE Qt::Quick Qt::Core Qt::Network Qt::Multimedia qopenai)
```
- Then include directories for target to be able to `#include` and instantiate them in C++:
```
target_include_directories(qopenai PUBLIC ${CMAKE_SOURCE_DIR}/qopenai "${CMAKE_BINARY_DIR}/qopenai")
```

## `How to use it `

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
  systemMessage: ""

  onRequestFinished: function (jsonObject) {
    const content = jsonObject.choices[0].message.content
    console.log("Message:", content)
    // need to its model for continuous conversation
    openAIChat.messageModel.insertMessage(content, QOpenAIMessage.Role.Assistant)
  }

  onRequestError: function (error) {
    console.log("Error message:", error)
  }
}

// somewhere in the Qml code
onClicked: {
  openAIChat.messageModel.insertMessage("naber", QOpenAIMessage.Role.User)
  openAIChat.sendRequest()
}


```

## `Appendix`
- Example app tested on OSX and iOS platforms with the Qt's 6.5.0 verion.
- 'gpt-3.5-turbo' model for chat endpoint doesn't follow system role messages at all and can be overridden with user role messages(in case you are planning to use gpt-4 then consider to modify system message part of the plugin). 
- Image and audio(if recorded audio is too long) may return responses a bit late than expected, so wait for it.

