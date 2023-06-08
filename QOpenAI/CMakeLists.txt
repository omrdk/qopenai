cmake_minimum_required(VERSION 3.16)

project(qopenai VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Core Quick Network Multimedia)

qt6_add_library(${PROJECT_NAME} STATIC)

qt6_add_qml_module(${PROJECT_NAME}
    URI QOpenAI
    VERSION 1.0
    SOURCES
        QOpenAI.cpp
        QOpenAI.h
        QOpenAICompletions.cpp
        QOpenAICompletions.h
        QOpenAIChat.cpp
        QOpenAIChat.h
        QOpenAIEdits.cpp
        QOpenAIEdits.h
        QOpenAIAudio.cpp
        QOpenAIAudio.h
        QOpenAIImage.cpp
        QOpenAIImage.h
        QOpenAIImageEdits.cpp
        QOpenAIImageEdits.h
        QOpenAIImageVariations.cpp
        QOpenAIImageVariations.h
        QOpenAIMessage.cpp
        QOpenAIMessage.h
        QOpenAIMessageModel.cpp
        QOpenAIMessageModel.h
    RESOURCE_PREFIX /
)

target_link_libraries(${PROJECT_NAME} PUBLIC Qt::Quick Qt::Core Qt::Network Qt::Multimedia)

