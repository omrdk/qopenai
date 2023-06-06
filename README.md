## Description

OpenAI plugin for QML or library for C++ that you can use as a templete in your future projects.

## Platform

OSX fully and iOS partially(except image edits and image variations) supported. Tested on Qt verion 6.5.0.

## Set your api key

Set OPENAI_API_KEY in Qt Creator to interact with the OpenAI endpoints:

Projects -> Your kit -> Run -> Environment -> Details -> Add:

OPENAI_API_KEY="your-key"

## How you can use the plugin in your project

- Copy `QOpenAI` folder under your project's root directory
- Find required modules in root CMakeLists.txt file:
```
find_package(Qt6 6.2 REQUIRED COMPONENTS Quick Core Network Multimedia)
```
- Add `QOpenAI` as a sub-directory in project's root CMakeLists.txt file after creating executable for your target(see qt_add_executable):
```
add_subdirectory(QOpenAI)
```
- Link required Qt modules and `qopenaiplugin` to the target:
```
target_link_libraries(appexample PRIVATE Qt::Quick Qt::Core Qt::Network Qt::Multimedia qopenaiplugin)
```
- If you are planning to use corresponding endpoints classes in C++, you should link it to the target with qopenai name instead of qopenaiplugin as below:
```
target_link_libraries(appexample PRIVATE Qt::Quick Qt::Core Qt::Network Qt::Multimedia qopenai)
```
- Then you should include QOpenAI directory to be able to `#include` and instantiate them in C++:
```
target_include_directories(qopenai PUBLIC ${CMAKE_SOURCE_DIR}/QOpenAI "${CMAKE_BINARY_DIR}/QOpenAI")
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

'gpt-3.5-turbo' model for chat endpoint doesn't follow system role messages at all and can be overridden with user role messages(in case you are planning to use gpt-4 then consider to modify system message part of the plugin). 

