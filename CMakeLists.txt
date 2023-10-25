cmake_minimum_required(VERSION 3.25)
project(Worms-Taller-1)


# set up SDL2DelRuso library
set(SDL2PP_WITH_IMAGE YES)
set(SDL2PP_WITH_TTF YES)
add_subdirectory(./Client/SDL2pp)
add_subdirectory(Server/box2d-main)
add_subdirectory(Client/ui)

set(CMAKE_CXX_STANDARD 17)

# find_package(box2d CONFIG REQUIRED)
# definitiones for SDL2DelRuso
add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/Client/data")
include_directories(${SDL2PP_INCLUDE_DIRS})

# Para el main mas externo: Server/main.cpp
add_executable(Worms-Taller-1 Server/src/Control/ServerMain.cpp

        #Server
        Server/src/Control/Server.h Server/src/Control/Server.cpp
        Server/src/Control/ServerProtocol.h Server/src/Control/ServerProtocol.cpp
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
        Client/src/ClientProtocol.cpp Server/src/Control/GameRoom.h Server/src/Control/GameRoom.cpp Server/src/Control/ProtectedGameRooms.h Server/src/Control/ProtectedGameRooms.cpp)


target_link_libraries(Worms-Taller-1 box2d SDL2pp)
