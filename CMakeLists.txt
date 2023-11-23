cmake_minimum_required(VERSION 3.22.1)
project(Worms-Taller-1)


# set up SDL2DelRuso library
set(SDL2PP_WITH_IMAGE YES)
set(SDL2PP_WITH_MIXER YES)
set(SDL2PP_WITH_TTF YES)

add_subdirectory(Client/libs/SDL2pp)
add_subdirectory(Server/box2d-main)
add_subdirectory(Client/ui)

set(CMAKE_CXX_STANDARD 17)

# find_package(box2d CONFIG REQUIRED)
# definitiones for SDL2DelRuso
#mas
include_directories(${SDL2PP_INCLUDE_DIRS})

FIND_PACKAGE(yaml-cpp REQUIRED)
INCLUDE_DIRECTORIES(${YAML_CPP_INCLUDE_DIRS})

#SETUP DEL QT inicial @Girardi
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets COMPONENTS Widgets REQUIRED)
find_package(Qt5Multimedia)

include_directories(${PROJECT_SOURCE_DIR}/Client/ui/include)

# Archivos Fuente Cliente @Ricardo
file(GLOB_RECURSE client_src "Client/src/*.cpp" "Client/src/*.h" "Common/DTO/*.h" "Client/src/game/*.h"
        "Client/src/command/*.h" "Client/src/gameObject/*.h" "Client/src/gameObject/weapon/*.h")
file(GLOB_RECURSE common_src "Common/*.cpp" "Common/*.h" "Common/DTO/*.cpp" "Client/src/game/*.cpp"
        "Client/src/command/*.cpp" "Client/src/gameObject/*.cpp"  "Client/src/gameObject/weapon/*.cpp")

#File de girardi  @Girardi  # parte qt
file(GLOB_RECURSE qt_src "Client/ui/*.cpp" "Client/ui/*.h")
include_directories(${PROJECT_BINARY_DIR})
qt5_wrap_ui(UIS_HEADERS
        Client/ui/ui/login.ui
        Client/ui/ui/mainmenu.ui
        Client/ui/ui/crearpartida.ui
        Client/ui/ui/buscarpartida.ui
        Client/ui/ui/lobby.ui)

add_executable(worms-client ${UIS_HEADERS}  ${client_src} ${qt_src} ${common_src}
        Common/DTO/CommandDTO.cpp
        Common/DTO/CommandDTO.h)

# Para el main mas externo: Server/main.cpp
add_executable(Worms-Taller-1 Server/src/Control/ServerMain.cpp

        #Server
        Server/src/Control/Server.h Server/src/Control/Server.cpp
        Server/src/Protocol/ServerProtocol.h Server/src/Protocol/ServerProtocol.cpp
        Server/src/Control/AcceptorThread.h Server/src/Control/AcceptorThread.cpp

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
        Common/DTO/DTO.h Common/DTO/DTO.cpp
        Common/DTO/WormDTO.h Common/DTO/WormDTO.cpp
        Client/src/protocol/ClientProtocol.cpp

        Server/src/Control/GamesProtected.h Server/src/Control/GamesProtected.cpp
        Server/src/Control/Engine.h Server/src/Control/Engine.cpp
        Server/src/Control/ClientLogin.h Server/src/Control/ClientLogin.cpp
        Common/DTO/InitialStateDTO.h Common/DTO/InitialStateDTO.cpp
        # Nuevos
        Common/rateController/RateController.cpp
        Common/rateController/RateController.h
        Common/DTO/ResponseInitialStateDTO.h
        Common/DTO/ResponseInitialStateDTO.cpp
        Common/DTO/RoomDTO.h
        Common/DTO/RoomDTO.cpp
        Common/DTO/ResolverInitialDTO.h
        Common/DTO/ResolverInitialDTO.cpp
        Common/DTO/CommandDTO.cpp
        Common/DTO/CommandDTO.h
        Server/src/Model/ModelGame/Model.h Server/src/Model/ModelGame/Model.cpp
        Server/src/Model/Players/Player.h Server/src/Model/Players/Player.cpp
        Server/src/Control/ClientConnection.cpp Server/src/Control/ClientConnection.h Server/src/Model/Worm/Worm.cpp Server/src/Model/Worm/Worm.h Server/src/Model/Scenario/Stage/Stage.cpp Server/src/Model/Scenario/Stage/Stage.h
        Server/src/Control/EstablishedConnections.h Server/src/Control/EstablishedConnections.cpp
        Common/DTO/StageDTO.cpp Common/DTO/StageDTO.h Server/src/Model/Scenario/Beam/Beam.cpp Server/src/Model/Scenario/Beam/Beam.h Common/DTO/BeamDTO.cpp Common/DTO/BeamDTO.h Server/src/Model/YamlParser/YamlParser.cpp Server/src/Model/YamlParser/YamlParser.h Server/src/Model/GameObject/GameObject.cpp Server/src/Model/GameObject/GameObject.h Server/src/Model/Players/Players.h Server/src/Model/Players/Players.cpp Common/DTO/PlayerDTO.cpp Common/DTO/PlayerDTO.h
        Common/DTO/PlayersDTO.cpp Common/DTO/PlayersDTO.h

        Server/src/Model/Scenario/Edges/Edges.cpp Server/src/Model/Scenario/Edges/Edges.h Server/src/Model/Scenario/Water/Water.cpp Server/src/Model/Scenario/Water/Water.h Common/DTO/SnapShot.cpp Common/DTO/SnapShot.h Server/GameParameters/GameParameters.h
        Server/GameParameters/GameParameters.h Server/GameParameters/GameParameters.cpp
        Common/DTO/WeaponDTO.cpp Common/DTO/WeaponDTO.h Common/DTO/WeaponsDTO.cpp Common/DTO/WeaponsDTO.h
        Server/src/Model/Weapons/Armament/Armament.cpp Server/src/Model/Weapons/Armament/Armament.h Server/src/Model/Weapons/WeaponsWorm/Weapon.cpp Server/src/Model/Weapons/WeaponsWorm/Weapon.h Server/src/Model/Weapons/WeaponsWorm/Bat.cpp Server/src/Model/Weapons/WeaponsWorm/Bat.h Server/src/Model/Weapons/WeaponsWorm/Teleport.cpp Server/src/Model/Weapons/WeaponsWorm/Teleport.h Server/src/Model/Weapons/WeaponRayCast/WeaponRayCast.cpp Server/src/Model/Weapons/WeaponRayCast/WeaponRayCast.h Server/src/Model/Weapons/WeaponSight/WeaponSight.cpp Server/src/Model/Weapons/WeaponSight/WeaponSight.h

        Common/DTO/WeaponSightDTO.cpp Common/DTO/WeaponSightDTO.h

        Server/src/Model/Weapons/WeaponsWorm/Bazooka.cpp Server/src/Model/Weapons/WeaponsWorm/Bazooka.h Server/src/Model/Projectiles/ProjectileBazooka.cpp Server/src/Model/Projectiles/ProjectileBazooka.h
        Server/src/Model/GameContactListener/GameContactListener.cpp Server/src/Model/GameContactListener/GameContactListener.h Server/src/Model/QueriesToWorld/SaveWormsInAreaQuery.cpp Server/src/Model/QueriesToWorld/SaveWormsInAreaQuery.h
        Common/DTO/ProjectileDTO.cpp Common/DTO/ProjectileDTO.h
        Common/DTO/ProjectilesDTO.cpp Common/DTO/ProjectilesDTO.h
        Server/src/Model/Turns/Turns.cpp Server/src/Model/Turns/Turns.h
        Common/DTO/TurnDTO.cpp Common/DTO/TurnDTO.h


        Server/src/Model/TimeTurn/TimeTurn.cpp Server/src/Model/TimeTurn/TimeTurn.h
        Server/src/Model/QueriesToWorld/PositionInAreaisFreeQuery.cpp Server/src/Model/QueriesToWorld/PositionInAreaisFreeQuery.h Common/DTO/EndGameDTO.cpp Common/DTO/EndGameDTO.h Server/src/Model/Provision/Provision.cpp Server/src/Model/Provision/Provision.h Common/DTO/ProvisionDTO.cpp Common/DTO/ProvisionDTO.h Server/src/Model/Weapons/WeaponsWorm/AirAttackDetonator.cpp Server/src/Model/Weapons/WeaponsWorm/AirAttackDetonator.h Server/src/Model/Projectiles/AirAttackMissile.cpp Server/src/Model/Projectiles/AirAttackMissile.h Server/src/Model/Projectiles/Explodable/Explodable.cpp Server/src/Model/Projectiles/Explodable/Explodable.h Server/src/Model/Projectiles/Dynamite.cpp Server/src/Model/Projectiles/Dynamite.h Server/src/Model/Weapons/WeaponsWorm/DynamiteHolder.cpp Server/src/Model/Weapons/WeaponsWorm/DynamiteHolder.h

        Server/src/Model/Projectiles/Grenades/Grenade/Grenade.cpp Server/src/Model/Projectiles/Grenades/Grenade/Grenade.h Server/src/Model/Projectiles/Grenades/GreenGrenade/GreenGrenade.cpp Server/src/Model/Projectiles/Grenades/GreenGrenade/GreenGrenade.h Server/src/Model/Weapons/WeaponsWorm/GrenadeHolder.cpp Server/src/Model/Weapons/WeaponsWorm/GrenadeHolder.h Server/src/Model/Projectiles/Grenades/Banana/Banana.cpp Server/src/Model/Projectiles/Grenades/Banana/Banana.h Server/src/Model/Projectiles/Grenades/HolyGrenade/HolyGrenade.cpp Server/src/Model/Projectiles/Grenades/HolyGrenade/HolyGrenade.h Server/src/Model/Projectiles/Grenades/RedGrenade/RedGrenade.cpp Server/src/Model/Projectiles/Grenades/RedGrenade/RedGrenade.h Server/src/Model/Projectiles/Grenades/FragmentGrenade/FragmentGrenade.cpp Server/src/Model/Projectiles/Grenades/FragmentGrenade/FragmentGrenade.h)

# para el editor
include_directories(${PROJECT_SOURCE_DIR}/Editor/include)

qt5_wrap_ui(UIS_HEADERS
        Editor/ui/chooseMapToEdit.ui
        Editor/ui/editingWindow.ui
        Editor/ui/editor.ui
        Editor/ui/nameNewMap.ui
)

add_executable(worms-editor
        Editor/src/main.cpp
        Editor/include/editor.h
        Editor/src/editor.cpp
        Editor/include/chooseMapToEdit.h
        Editor/src/chooseMapToEdit.cpp
        Editor/include/nameNewMap.h
        Editor/src/nameNewMap.cpp
        Editor/include/editingWindow.h
        Editor/src/editingWindow.cpp
        Editor/include/zoom.h
        Editor/src/zoom.cpp
        ${UIS_HEADERS}



        )

target_link_libraries(worms-editor Qt5::Widgets yaml-cpp)
target_link_libraries(worms-client PUBLIC SDL2pp yaml-cpp Qt5::Widgets Qt5::Multimedia)
target_link_libraries(Worms-Taller-1 box2d SDL2pp yaml-cpp)
