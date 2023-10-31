cmake_minimum_required(VERSION 3.22)

project(editor)

set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets COMPONENTS Widgets REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

qt5_wrap_ui(UIS_HEADERS
        ui/chooseMapToEdit.ui
        ui/editingWindow.ui
        ui/editor.ui
        ui/nameNewMap.ui
)

include_directories(${PROJECT_BINARY_DIR})

add_executable(editor
        src/main.cpp
        include/editor.h
        src/editor.cpp
        include/chooseMapToEdit.h
        src/chooseMapToEdit.cpp
        include/nameNewMap.h
        src/nameNewMap.cpp
        include/editingWindow.h
        src/editingWindow.cpp
        ${UIS_HEADERS})

target_link_libraries(editor Qt5::Widgets yaml-cpp)

