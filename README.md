## Description

OpenAI plugin for QML or library for C++ that you can use as a templete in your future projects.

## Platform

Example supports only OSX and iOS platforms. Tested on Qt verion 6.5.0.

## Set your api key

Set OPENAI_API_KEY in Qt Creator to interact with the OpenAI endpoints:

Projects -> Your kit -> Run -> Environment -> Details -> Add: OPENAI_API_KEY="your-key"

## How to link the qopenai to your application

- Copy `QOpenAI` folder under your project's root directory
- Add `QOpenAI` as a sub-directory in project's root CMakeLists.txt file after creating executable for your target(see qt_add_executable):
```
add_subdirectory(QOpenAI)
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
target_include_directories(qopenai PUBLIC ${CMAKE_SOURCE_DIR}/QOpenAI "${CMAKE_BINARY_DIR}/QOpenAI")
```

## How to use it 

### - In QML

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

  onRequestFinished: function (content) {
    console.log("Response message:", content)
  }

  onRequestError: function (error) {
    console.log("Error message:", error)
  }
}

// somewhere in your application
onClicked: {
  openAIChat.sendRequest(textItem.text)
}


```

## Features

Plugin provides below endpoints:

- /v1/completions
- /v1/chat/completions
- /v1/edits
- /v1/audio/transcriptions
- /v1/audio/translations
- /v1/images/generations
- /v1/images/edits
- /v1/images/variations


## Appendix

- 'gpt-3.5-turbo' model for chat endpoint doesn't follow system role messages at all and can be overridden with user role messages(in case you are planning to use gpt-4 then consider to modify system message part of the plugin). 
- Image and audio(if recorded audio is too long) may return responses a bit late than expected, so wait for it.

