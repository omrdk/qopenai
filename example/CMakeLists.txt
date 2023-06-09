cmake_minimum_required(VERSION 3.16)

project(example VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick Core Network Multimedia Gui)

set(SOURCES src/main.cpp)

if(IOS)
    list(APPEND SOURCES src/ImagePicker.mm inc/ImagePicker.h)
endif()

qt_add_resources(SOURCES resources/icons.qrc)

qt_add_executable(appexample ${SOURCES})

qt6_add_qml_module(appexample
    URI ${PROJECT_NAME}
    VERSION 1.0
    QML_FILES
        resources/qml/Main.qml
        resources/qml/SessionListView.qml
        resources/qml/ChatInput.qml
        resources/qml/ChatPage.qml
        resources/qml/EndPointsPopup.qml
        resources/qml/IconButton.qml
        resources/qml/IconItem.qml
        resources/qml/PopupItem.qml
        resources/qml/TextAreaItem.qml
        resources/qml/SelectedImagePopup.qml
    SOURCES
        src/InteractiveImage.cpp
        src/AudioRecorder.cpp
        inc/InteractiveImage.h
        inc/AudioRecorder.h
        inc/EventInstaller.h
)

include_directories(inc)

add_subdirectory(${CMAKE_SOURCE_DIR}/../qopenai ${CMAKE_BINARY_DIR}/qopenai)

if(APPLE)
    set_target_properties(appexample PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER qopenai.example.com
        MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1"
        MACOSX_BUNDLE_LONG_VERSION_STRING "0.1"
        MACOSX_BUNDLE_BUNDLE_VERSION "0.1"
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
    )
    if(IOS)
        set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer")
        set_target_properties(appexample PROPERTIES
            QT_IOS_LAUNCH_SCREEN ${CMAKE_CURRENT_SOURCE_DIR}/platforms/iOS/Launch.storyboard
            MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/platforms/iOS/Info.plist
        )
    else()
        set_target_properties(appexample PROPERTIES
            MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/platforms/macOS/Info.plist
        )
    endif()
endif()

if(WIN32)
    set_target_properties(appexample PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

# uncomment if you'll instantiate openai classes in C++
target_link_libraries(appexample PRIVATE Qt::Quick Qt::Core Qt::Network Qt::Multimedia Qt::Gui qopenaiplugin)
target_include_directories(appexample PUBLIC ${CMAKE_SOURCE_DIR}/../qopenai "${CMAKE_BINARY_DIR}/qopenai")

install(TARGETS appexample BUNDLE DESTINATION . LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})






