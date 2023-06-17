cmake_minimum_required(VERSION 3.5)

enable_testing()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(requests tst_requests.cpp)
add_test(NAME EndPointRequest COMMAND EndPointRequest)

file(COPY "assets" DESTINATION ${CMAKE_BINARY_DIR}/test)

include_directories(${CMAKE_SOURCE_DIR}/../qopenai)

target_link_libraries(requests PRIVATE Qt${QT_VERSION_MAJOR}::Test qopenai)
