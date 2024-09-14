cmake_minimum_required(VERSION 3.26)
project(Fractal_Editor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(Fractal_Editor main.cpp
        src/App.cpp
        src/App.h
        src/header.h
        src/Label.h
        src/GraphWidget.cpp
        src/GraphWidget.h
        src/MainWindow.cpp
        src/MainWindow.h
        src/Complex.h)
target_link_libraries(Fractal_Editor
        Qt6::Widgets
)

