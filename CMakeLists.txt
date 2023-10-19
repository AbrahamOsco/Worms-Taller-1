cmake_minimum_required(VERSION 3.25)
project(Worms-Taller-1)


# set up SDL2DelRuso library
set(SDL2PP_WITH_IMAGE YES)
set(SDL2PP_WITH_TTF YES)
add_subdirectory(./Client/SDL2pp)
add_subdirectory(Server/box2d-main)

set(CMAKE_CXX_STANDARD 17)

find_package(box2d CONFIG REQUIRED)
# definitiones for SDL2DelRuso
add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/Client/data")
include_directories(${SDL2PP_INCLUDE_DIRS})

add_executable(Worms-Taller-1 Server/main.cpp
        Server/src/Modelo/Gusano.h
        Server/src/Modelo/Gusano.cpp
        Server/src/Modelo/Posicion.h
        Server/src/Modelo/Posicion.cpp )

target_link_libraries(Worms-Taller-1 PRIVATE box2d::box2d PUBLIC SDL2pp )
