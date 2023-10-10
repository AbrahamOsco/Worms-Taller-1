cmake_minimum_required(VERSION 3.25)
project(Worms-Taller-1)

set(CMAKE_CXX_STANDARD 17)

find_package(box2d CONFIG REQUIRED)

add_executable(Worms-Taller-1 Server/main.cpp
        Server/src/Modelo/Gusano.h
        Server/src/Modelo/Gusano.cpp
        Server/src/Modelo/Posicion.h
        Server/src/Modelo/Posicion.cpp )

target_link_libraries(Worms-Taller-1 PRIVATE box2d::box2d )

