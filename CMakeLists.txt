cmake_minimum_required(VERSION 3.25)
project(Worms-Taller-1)


# set up SDL2DelRuso library
set(SDL2PP_WITH_IMAGE YES)
set(SDL2PP_WITH_TTF YES)
set(SDL2PP_WITH_TTF YES)

add_subdirectory(Client/libs/SDL2pp)
add_subdirectory(Server/box2d-main)
add_subdirectory(Client/ui)

set(CMAKE_CXX_STANDARD 17)

# find_package(box2d CONFIG REQUIRED)
# definitiones for SDL2DelRuso
include_directories(${SDL2PP_INCLUDE_DIRS})

FIND_PACKAGE(yaml-cpp REQUIRED)
INCLUDE_DIRECTORIES(${YAML_CPP_INCLUDE_DIRS})

add_executable(worms-client Client/src/main.cpp
        Client/src/core/Engine.cpp
        Client/src/core/Engine.h
        Client/src/graphics/TextureManager.cpp
        Client/src/graphics/TextureManager.h
        Client/src/timer/Timer.cpp
        Client/src/timer/Timer.h
        Client/src/gameObject/GameObject.cpp
        Client/src/gameObject/GameObject.h
        Client/src/gameObject/IObject.h
        Client/src/loaderParams/LoaderParams.cpp
        Client/src/loaderParams/LoaderParams.h
        Client/src/gameObject/player/Player.cpp
        Client/src/gameObject/player/Player.h
        Client/src/animation/Animation.cpp
        Client/src/animation/Animation.h
        Common/DTO/DTO.h
        Common/DTO/DTO.cpp
        Common/DTO/ResponseInitialStateDTO.h
        Common/DTO/ResponseInitialStateDTO.cpp
        Common/DTO/RoomDTO.h
        Common/DTO/RoomDTO.cpp
        Common/DTO/ResolverInitialDTO.h
        Common/DTO/ResolverInitialDTO.cpp
        Client/src/gameObject/icons/Icon.cpp
        Client/src/gameObject/icons/Icon.h
        Client/src/gameObject/icons/AirAttackIcon.cpp
        Client/src/gameObject/icons/AirAttackIcon.h)

# Para el main mas externo: Server/main.cpp
add_executable(Worms-Taller-1 Server/src/Control/ServerMain.cpp

        #Server
        Server/src/Control/Server.h Server/src/Control/Server.cpp
        Server/src/Protocol/ServerProtocol.h Server/src/Protocol/ServerProtocol.cpp
        Server/src/Control/AcceptorThread.h Server/src/Control/AcceptorThread.cpp
        Server/src/Control/ClientThread.h Server/src/Control/ClientThread.cpp
        Server/src/Control/ReceiverThread.h Server/src/Control/ReceiverThread.cpp
        Server/src/Control/SenderThread.h Server/src/Control/SenderThread.cpp

        #¢ommon
        Common/Thread/Thread.h Common/Thread/Thread.cpp
        Common/Queue/Queue.h

        #Socket
        Common/Socket/LibError.h Common/Socket/LibError.cpp
        Common/Socket/ResolveError.h Common/Socket/ResolveError.cpp
        Common/Socket/Resolver.h Common/Socket/Resolver.cpp
        Common/Socket/Socket.h Common/Socket/Socket.cpp

        #Protocol
        Common/Protocol/Protocol.h Common/Protocol/Protocol.cpp

        #DTOs
        Common/DTO/BeamDTO.h Common/DTO/BeamDTO.cpp
        Common/DTO/DTO.h Common/DTO/DTO.cpp
        Common/DTO/LobbyAnswerDTO.h Common/DTO/LobbyAnswerDTO.cpp
        Common/DTO/WormDTO.h Common/DTO/WormDTO.cpp
        Common/DTO/MapDTO.h     Common/DTO/MapDTO.cpp
        Client/src/protocol/ClientProtocol.cpp
        Server/src/Control/GameRoom.h Server/src/Control/GameRoom.cpp
        Server/src/Control/ProtectedGameRooms.h Server/src/Control/ProtectedGameRooms.cpp

        Server/src/Control/GamesProtected.h Server/src/Control/GamesProtected.cpp Server/src/Control/Engine.h Server/src/Control/Engine.cpp Server/src/Control/ClientLogin.h Server/src/Control/ClientLogin.cpp Common/DTO/InitialStateDTO.h Common/DTO/InitialStateDTO.cpp)

target_link_libraries(worms-client PUBLIC SDL2pp yaml-cpp)

target_link_libraries(Worms-Taller-1 box2d SDL2pp)
