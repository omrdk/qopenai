## `Description`

OpenAI plugin for QML or a library for C++ that could be used in Qt-based projects.

## `Features`

- [x] [Completions](https://github.com/omrdk/qopenai/tree/master/doc/completions.md)
- [X] [Chat Completions](https://github.com/omrdk/qopenai/tree/master/doc/chat_completions.md)
- [X] [Edits](https://github.com/omrdk/qopenai/tree/master/doc/edits.md)
- [x] [Image Generations](https://github.com/omrdk/qopenai/tree/master/doc/image_generations.md)
- [x] [Image Edits](https://github.com/omrdk/qopenai/tree/master/doc/image_edits.md)
- [x] [Image Variations](https://github.com/omrdk/qopenai/tree/master/doc/image_variations.md) 
- [x] [Embeddings](https://github.com/omrdk/qopenai/tree/master/doc/embeddings.md) 
- [x] [Transcriptions](https://github.com/omrdk/qopenai/tree/master/doc/transcriptions.md) 
- [x] [Translations](https://github.com/omrdk/qopenai/tree/master/doc/translations.md) 
- [x] [Moderations](https://github.com/omrdk/qopenai/tree/master/doc/moderations.md) 
- [ ] [Files]() 
- [ ] [Fine Tunes]() 

## `Authentication`

Make sure you defined OPENAI_API_KEY environment. You could also do that active kit's run configuration on Qt Creator:

Projects -> Your kit -> Run -> Environment -> Details -> Add: OPENAI_API_KEY="your-key"

## `How to link qopenai`

- Copy `qopenai` folder under your project's root directory
- Add `qopenai` as a sub-directory in project's root CMakeLists.txt file after creating executable for your target(see qt_add_executable):
```
add_subdirectory(qopenai)
```
- Link required Qt modules and `qopenaiplugin` to the target:
```
target_link_libraries(appexample PRIVATE qopenaiplugin)
```
- Should you be interested in using this plugin as a library and instantiate them in C++, link it to the target with qopenai name instead of qopenaiplugin as below:
```
target_link_libraries(appexample PRIVATE qopenai)
```
- Then include directories for target to be able to `#include` and instantiate them in C++:
```
target_include_directories(qopenai PUBLIC ${CMAKE_SOURCE_DIR}/qopenai "${CMAKE_BINARY_DIR}/qopenai")
```

## `Appendix`
- Example app tested on Windows, OSX and iOS platforms with the Qt's 6.5.0 kit.
- Image and audio responses may take a bit more time than expected so wait for it.

