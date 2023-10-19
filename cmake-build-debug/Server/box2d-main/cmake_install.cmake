# Install script for directory: /home/riclui/Documentos/fiuba/taller-de-programacion-I/Worms-Taller-1/Server/box2d-main

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/riclui/Documentos/fiuba/taller-de-programacion-I/Worms-Taller-1/Server/box2d-main/include/box2d")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/riclui/Documentos/fiuba/taller-de-programacion-I/Worms-Taller-1/cmake-build-debug/Server/box2d-main/src/cmake_install.cmake")
  include("/home/riclui/Documentos/fiuba/taller-de-programacion-I/Worms-Taller-1/cmake-build-debug/Server/box2d-main/extern/glad/cmake_install.cmake")
  include("/home/riclui/Documentos/fiuba/taller-de-programacion-I/Worms-Taller-1/cmake-build-debug/Server/box2d-main/extern/glfw/cmake_install.cmake")
  include("/home/riclui/Documentos/fiuba/taller-de-programacion-I/Worms-Taller-1/cmake-build-debug/Server/box2d-main/extern/imgui/cmake_install.cmake")
  include("/home/riclui/Documentos/fiuba/taller-de-programacion-I/Worms-Taller-1/cmake-build-debug/Server/box2d-main/extern/sajson/cmake_install.cmake")
  include("/home/riclui/Documentos/fiuba/taller-de-programacion-I/Worms-Taller-1/cmake-build-debug/Server/box2d-main/testbed/cmake_install.cmake")

endif()

