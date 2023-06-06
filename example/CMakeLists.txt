cmake_minimum_required(VERSION 3.16)

project(example VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick Core Network Multimedia Gui)

if(IOS)
    set(SOURCES main.cpp ImagePicker.mm ImagePicker.h)
else()
    set(SOURCES main.cpp)
endif()

qt_add_resources(SOURCES res.qrc)

qt_add_executable(appexample ${SOURCES})

qt6_add_qml_module(appexample
    URI ${PROJECT_NAME}
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        qml/SessionListView.qml
        qml/ChatInput.qml
        qml/ChatPage.qml
        qml/EndPointsPopup.qml
        qml/IconButton.qml
        qml/IconItem.qml
        qml/PopupItem.qml
        qml/TextAreaItem.qml
        qml/SelectedImagePopup.qml
    SOURCES
        EventInstaller.h
        InteractiveImage.cpp
        InteractiveImage.h
)

add_subdirectory(${CMAKE_SOURCE_DIR}/../QOpenAI ${CMAKE_BINARY_DIR}/QOpenAI)

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

target_link_libraries(appexample PRIVATE Qt::Quick Qt::Core Qt::Network Qt::Multimedia Qt::Gui qopenaiplugin #[[qopenai]]) # uncomment if you ll use as a library

# uncomment if you will use QOpenAI as a library
#target_include_directories(appexample PUBLIC ${CMAKE_SOURCE_DIR}/../QOpenAI "${CMAKE_BINARY_DIR}/QOpenAI")

install(TARGETS appexample
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})






