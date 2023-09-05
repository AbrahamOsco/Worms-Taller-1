cmake_minimum_required(VERSION 3.20t)
project(Modelo)

# set up SDL2pp library
set(SDL2PP_WITH_IMAGE YES)
set(SDL2PP_WITH_TTF YES)
add_subdirectory(SDL2pp)

# add compilation flags
set(CMAKE_CXX_STANDARD 17)
add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/data")
include_directories(${SDL2PP_INCLUDE_DIRS})

# define targets
add_executable(Modelo main.cpp)
target_link_libraries(Modelo PUBLIC SDL2pp)


