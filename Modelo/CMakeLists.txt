cmake_minimum_required(VERSION 3.25)
project(Modelo)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})


add_executable(Modelo main.cpp src/core/Engine.cpp src/core/Engine.h src/Graphics/TextManager.cpp src/Graphics/TextManager.h)

target_link_libraries(Modelo ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} -lSDL2_image)
# con -lSDL2_imagen enlazamos todas las depedencias de la libreria SDL2_IMAGE_LIBRARIES y no solo esa libreria.

