cmake_minimum_required(VERSION 3.26)
project(metal-qt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include(FetchContent)

message(CHECK_START "Fetching metal-cpp")
FetchContent_Declare(
        metal-cpp
        GIT_REPOSITORY https://github.com/Servall4/metal-cpp-cmake.git
        GIT_TAG 08795e7
)
set(METAL_CPP_BUILD_EXAMPLES OFF)
FetchContent_MakeAvailable(metal-cpp)
message(CHECK_PASS "Fetched")

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)

add_executable(metal-qt
        main.cpp
        MainWindow.h
        MainWindow.cpp
        MetalHelper.mm
        MetalHelper.h
        Renderer.cpp
        Renderer.h
        ViewDelegate.cpp
        ViewDelegate.h
        MetalWidget.cpp
        MetalWidget.h
)

target_link_libraries(metal-qt PRIVATE Qt6::Widgets Qt6::Core)
target_link_libraries(metal-qt PRIVATE METAL_CPP)
