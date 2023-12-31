#include <gmock/gmock.h>
#include <arpa/inet.h>
#include <gtest/gtest.h>
#include <iostream>
#include <cstring>
#include "Mock_Socket.h"
#include <vector>
#include <memory>
#include "../Common/Protocol/Protocol.h"
#include "../Client/src/protocol/ClientProtocol.h"
#include "../Server/src/Protocol/ServerProtocol.h"
#include "../Common/DTO/BeamDTO.h"
#include "../Common/DTO/CommandDTO.h"
#include "../Common/DTO/DTO.h"
#include "../Common/DTO/InitialStateDTO.h"
#include "../Common/DTO/PlayerDTO.h"
#include "../Common/DTO/PlayersDTO.h"
#include "../Common/DTO/ProjectileDTO.h"
#include "../Common/DTO/ProjectilesDTO.h"
#include "../Common/DTO/ResolverInitialDTO.h"
#include "../Common/DTO/ResponseInitialStateDTO.h"
#include "../Common/DTO/RoomDTO.h"
#include "../Common/DTO/SnapShot.h"
#include "../Common/DTO/StageDTO.h"
#include "../Common/DTO/TurnDTO.h"
#include "../Common/DTO/WeaponDTO.h"
#include "../Common/DTO/WeaponsDTO.h"
#include "../Common/DTO/WeaponSightDTO.h"
#include "../Common/DTO/WormDTO.h"

TEST(TEST_MOCK_SOCKET, SEND_SOME) {
    // Arrenge
    Socket skt;
    std::vector<char> data;
    bool closed;
    std::vector<char> buff;
    // Act
    for (int i = 0; i < 10; i++) {
        data.push_back((char) i+60);
    }
    skt.sendall(data.data(), 5, &closed);
    skt.sendall(data.data()+5, 5, &closed);
    buff = skt.getBuffer();
    // Assert
    for (int i = 0; i < 10; i++)
        ASSERT_TRUE(data[i] == buff[i]);
}
TEST(TEST_MOCK_SOCKET, RECV_SOME) {
    // Arrenge
    Socket skt;
    std::vector<char> data;
    bool closed;
    std::vector<char> read(10);
    // Act
    for (int i = 0; i < 10; i++) {
        data.push_back((char) i);
    }
    skt.setBuffer(data);
    skt.recvall(read.data(), 4, &closed);
    skt.recvall(read.data()+4, 6, &closed);
    // Assert
    for (int i = 0; i < 10; i++)
        ASSERT_TRUE(data[i] == read[i]);
}
TEST(TEST_PROTOCOL_COMMON_SEND, sendANumberByte) {
    // Arrenge
    Socket skt;
    Protocol protocol(skt);
    uint8_t byte = 54;
    std::vector<char> buff;
    // Act
    protocol.sendANumberByte(byte);
    buff = skt.getBuffer();
    // Assert
    ASSERT_TRUE(byte == buff[0]);
}
TEST(TEST_PROTOCOL_COMMON_SEND, sendNum2Bytes) {
    // Arrenge
    Socket skt;
    Protocol protocol(skt);
    uint16_t word = 2000;
    uint16_t sent;
    std::vector<char> buff;
    // Act
    protocol.sendNum2Bytes(word);
    buff = skt.getBuffer();
    memcpy(&sent, buff.data(), 2);
    sent = ntohs(sent);
    // Assert
    ASSERT_TRUE(sent == word);
}
TEST(TEST_PROTOCOL_COMMON_RECV, recvANumberByte) {
    // Arrenge
    Socket skt;
    Protocol protocol(skt);
    uint8_t byte = 25;
    uint8_t read;
    // Act
    protocol.sendANumberByte(byte);
    read = protocol.recvANumberByte();
    // Assert
    ASSERT_TRUE(read == byte);
}
TEST(TEST_PROTOCOL_COMMON_RECV, recvNum2Bytes) {
    // Arrenge
    Socket skt;
    Protocol protocol(skt);
    std::vector<char> data;
    uint16_t word = 0x12AC;
    uint16_t read;
    // Act
    protocol.sendNum2Bytes(word);
    read = protocol.recvNum2Bytes();
    // Assert
    ASSERT_TRUE(word == read);
}
TEST(TEST_PROTOCOL_CLIENT_SEND, sendInitialStateDTO) {
    // Arrenge
    Socket skt;
    uint16_t size;
    size_t offset = 0;
    std::vector<char> buffer;
    ClientProtocol protocol(skt);
    std::string name("Pedro");
    InitialStateDTO dto(SCENARIO_LIST_REQUEST, name);
    // Act
    protocol.sendInitialStateDTO(dto);
    // Assert
    buffer = skt.getBuffer();
    ASSERT_TRUE(SCENARIO_LIST_REQUEST == buffer[offset]);
    offset++;
    memcpy(&size, buffer.data()+offset, 2);
    size = ntohs(size);
    ASSERT_TRUE(name.size() == size);
    offset = offset + 2;
    std::string aux(buffer.data()+offset, size);
    ASSERT_TRUE(name == aux);
}
TEST(TEST_PROTOCOL_CLIENT_SEND, sendResponseInitialStateDTO_Create_Game) {
    // Arrenge
    Socket skt;
    uint16_t size;
    ClientProtocol protocol(skt);
    std::vector<char> buffer;
    size_t offset = 0;
    std::string gameName("Mostaza");
    std::string scenarioName("Ruinas");
    size_t playersNumber = 5;
    ResponseInitialStateDTO dto(FINAL_CREATE_GAME, gameName, scenarioName, playersNumber);
    // Act
    protocol.sendResponseInitialStateDTO(dto);
    // Assert
    buffer = skt.getBuffer();
    ASSERT_TRUE(FINAL_CREATE_GAME == buffer[0]);
    offset++;
    memcpy(&size, buffer.data()+offset, 2);
    size = ntohs(size);
    ASSERT_TRUE(gameName.size() == size);
    offset = offset+2;
    std::string aux(buffer.data()+offset, size);
    ASSERT_TRUE(gameName == aux);
    offset = offset + gameName.size();
    memcpy(&size, buffer.data()+offset, 2);
    size = ntohs(size);
    ASSERT_TRUE(scenarioName.size() == size);
    offset = offset+2;
    std::string aux2(buffer.data()+offset, size);
    ASSERT_TRUE(scenarioName == aux2);
    offset = offset + scenarioName.size();
    ASSERT_TRUE(playersNumber == buffer[offset]);
}
TEST(TEST_PROTOCOL_CLIENT_SEND, sendResponseInitialStateDTO_Join_Game) {
    // Arrenge
    Socket skt;
    uint16_t size;
    ClientProtocol protocol(skt);
    std::vector<char> buffer;
    size_t offset = 0;
    std::string gameName("Mostaza");
    ResponseInitialStateDTO dto(FINAL_JOIN_GAME, gameName);
    // Act
    protocol.sendResponseInitialStateDTO(dto);
    // Assert
    buffer = skt.getBuffer();
    ASSERT_TRUE(FINAL_JOIN_GAME == buffer[0]);
    offset++;
    memcpy(&size, buffer.data()+offset, 2);
    size = ntohs(size);
    ASSERT_TRUE(gameName.size() == size);
    offset = offset+2;
    std::string aux(buffer.data()+offset, size);
    ASSERT_TRUE(gameName == aux);
}
TEST(TEST_PROTOCOL_CLIENT_SEND, sendCommandDTO) {
    // Arrenge
    Socket skt;
    int x, y;
    uint16_t word;
    std::vector<char> buff;
    ClientProtocol protocol(skt);
    CommandDTO dto;
    size_t offset = 0;
    dto.setTypeCommand(SELECT_HOLY_GRENADE);
    x = 23747;
    y = 9671;
    dto.setX(x);
    dto.setY(y);
    // Act
    protocol.sendCommandDTO(dto);
    // Assert
    buff = skt.getBuffer();
    ASSERT_TRUE(COMMAND == buff[offset]);
    offset++;
    ASSERT_TRUE(SELECT_HOLY_GRENADE == buff[offset]);
    offset++;
    memcpy(&word, buff.data()+offset, 2);
    word = ntohs(word);
    ASSERT_TRUE(x == word);
    offset = offset + 2;
    memcpy(&word, buff.data()+offset, 2);
    word = ntohs(word);
    ASSERT_TRUE(y == word);
}
TEST(TEST_PROTOCOL_SERVER_SEND, sendResolverInitialDTO_RES_INI_CREATE_GAME) {
    // Arrenge
    Socket skt;
    ServerProtocol protocol(skt);
    std::vector<std::string> scenarios;
    std::vector<size_t> maxPlayers;
    std::vector<char> buffer;
    size_t offset = 0;
    uint8_t amount = 0;
    uint16_t word;
    scenarios.push_back("Ruinas");
    maxPlayers.push_back(3);
    amount++;
    scenarios.push_back("Laboratorio");
    maxPlayers.push_back(8);
    amount++;
    scenarios.push_back("Cascadas");
    maxPlayers.push_back(14);
    amount++;
    ResolverInitialDTO dto(RESPONSE_INITIAL_CREATE_GAME, scenarios, maxPlayers);
    // Act
    protocol.sendResolverInitialDTO(dto);
    // Assert
    buffer = skt.getBuffer();
    ASSERT_TRUE(RESPONSE_INITIAL_CREATE_GAME == buffer[offset]);
    offset++;
    ASSERT_TRUE(amount == buffer[offset]);
    offset++;
    for (int i = 0; i < amount; i++) {
        memcpy(&word, buffer.data()+offset, 2);
        word = htons(word);
        ASSERT_TRUE(scenarios[i].size() == word);
        offset = offset + 2;
        std::string aux(buffer.data()+offset, word);
        ASSERT_TRUE(scenarios[i] == aux);
        offset = offset + word;
    }
}
TEST(TEST_PROTOCOL_SERVER_SEND, sendResolverInitialDTO_RES_FIN_CREATE_GAME) {
    // Arrenge
    Socket skt;
    ServerProtocol protocol(skt);
    std::vector<char> buffer;
    ResolverInitialDTO dto(RESPONSE_FINAL_CREATE_GAME, 1);
    // Act
    protocol.sendResolverInitialDTO(dto);
    // Assert
    buffer = skt.getBuffer();
    ASSERT_TRUE(RESPONSE_FINAL_CREATE_GAME == buffer[0]);
    ASSERT_EQ(1, buffer[1]);
}
TEST(TEST_PROTOCOL_SERVER_SEND, sendResolverInitialDTO_RES_INI_JOIN_GAME) {
    // Arrenge
    Socket skt;
    ServerProtocol protocol(skt);
    std::vector<char> buffer;
    ResolverInitialDTO dto;
    size_t offset = 0;
    uint16_t word;
    dto.setOperationType(RESPONSE_INITIAL_JOIN_GAME);
    std::vector<RoomDTO> games;
    std::vector<std::string> names;
    std::vector<std::string> scenarios;
    std::vector<size_t> currentPlayers;
    std::vector<size_t> maxPlayers;
    names.push_back("mi partida");
    names.push_back("partida adsgsdsd");
    scenarios.push_back("mapa pequeño");
    scenarios.push_back("mapa definitivo mortal xd");
    currentPlayers.push_back(1);
    currentPlayers.push_back(3);
    maxPlayers.push_back(5);
    maxPlayers.push_back(9);
    games.push_back(RoomDTO(names[0], scenarios[0], currentPlayers[0], maxPlayers[0]));
    games.push_back(RoomDTO(names[1], scenarios[1], currentPlayers[1], maxPlayers[1]));
    dto.setGameRooms(games);
    // Act
    protocol.sendResolverInitialDTO(dto);
    // Assert
    buffer = skt.getBuffer();
    ASSERT_TRUE(RESPONSE_INITIAL_JOIN_GAME == buffer[offset]);
    offset++;
    ASSERT_TRUE(games.size() == buffer[offset]);
    offset++;
    for (size_t i = 0; i < games.size(); i++) {
        ASSERT_TRUE(ROOM_GAME == buffer[offset]);
        offset++;
        memcpy(&word, buffer.data()+offset, 2);
        word = ntohs(word);
        ASSERT_TRUE(names[i].size() == word);
        offset = offset + 2;
        std::string aux1(buffer.data()+offset, word);
        ASSERT_TRUE(names[i] == aux1);
        offset = offset + word;
        memcpy(&word, buffer.data()+offset, 2);
        word = ntohs(word);
        ASSERT_TRUE(scenarios[i].size() == word);
        offset = offset + 2;
        std::string aux2(buffer.data()+offset, word);
        ASSERT_TRUE(scenarios[i] == aux2);
        offset = offset + word;
        ASSERT_TRUE(currentPlayers[i] == buffer[offset]);
        offset++;
        ASSERT_TRUE(maxPlayers[i] == buffer[offset]);
        offset++;
    }
}
TEST(TEST_PROTOCOL_SERVER_SEND, sendResolverInitialDTO_RES_FIN_JOIN_GAME) {
    // Arrenge
    Socket skt;
    ServerProtocol protocol(skt);
    std::vector<char> buffer;
    ResolverInitialDTO dto(RESPONSE_FINAL_JOIN_GAME, 1);
    // Act
    protocol.sendResolverInitialDTO(dto);
    // Assert
    buffer = skt.getBuffer();
    ASSERT_TRUE(RESPONSE_FINAL_JOIN_GAME == buffer[0]);
    ASSERT_EQ(1, buffer[1]);
}
TEST(TEST_PROTOCOL_SERVER_SEND, START_GAME) {
    // Arrenge
    Socket skt;
    ServerProtocol protocol(skt);
    std::vector<char> buffer;
    // Act
    protocol.sendANumberByte(START_GAME);
    // Assert
    buffer = skt.getBuffer();
    ASSERT_EQ(START_GAME, buffer[0]);
}
TEST(TEST_PROTOCOL_SERVER_SEND, sendBeamDTO) {
    // Arrenge
    Socket skt;
    size_t offset = 0;
    uint16_t word;
    ServerProtocol protocol(skt);
    std::vector<char> buffer;
    BeamDTO dto(SHORT_BEAM, 53, 69, 120, 78, 96);
    // Act
    protocol.sendBeamDTO(dto);
    // Assert
    buffer = skt.getBuffer();
    ASSERT_EQ(dto.getOperationType(), buffer[offset]);
    offset++;
    ASSERT_EQ(dto.getTypeBeam(), buffer[offset]);
    offset++;
    memcpy(&word, buffer.data()+offset, 2);
    word = ntohs(word);
    ASSERT_EQ(dto.getXCenter(), word);
    offset = offset + 2;
    memcpy(&word, buffer.data()+offset, 2);
    word = ntohs(word);
    ASSERT_EQ(dto.getYCenter(), word);
    offset = offset + 2;
    ASSERT_EQ(dto.getAngle(), buffer[offset]);
    offset++;
    ASSERT_EQ(dto.getLenghth(), buffer[offset]);
    offset++;
    ASSERT_EQ(dto.getHeight(), buffer[offset]);
}
TEST(TEST_PROTOCOL_SERVER_SEND, sendStage) {
    // Arrenge
    Socket skt;
    size_t offset = 0;
    uint16_t word;
    ServerProtocol protocol(skt);
    std::vector<char> buffer;
    std::vector<BeamDTO> beams;
    beams.push_back(BeamDTO(SHORT_BEAM, 53, 69, 120, 78, 96));
    beams.push_back(BeamDTO(WATER_BEAM, 153, 169, 20, 39, 127));
    beams.push_back(BeamDTO(LONG_BEAM, 0, 0, 127, 127, 127));
    StageDTO dto(beams, 1, "background");
    dto.setIdPlayer(127);
    // Act
    protocol.sendStage(dto);
    // Assert
    buffer = skt.getBuffer();
    ASSERT_TRUE(STAGE == buffer[offset]);
    offset++;
    ASSERT_EQ(beams.size(), buffer[offset]);
    offset++;
    for (size_t i = 0; i < beams.size(); i++) {
        ASSERT_EQ(beams[i].getOperationType(), buffer[offset]);
        offset++;
        ASSERT_EQ(beams[i].getTypeBeam(), buffer[offset]);
        offset++;
        memcpy(&word, buffer.data()+offset, 2);
        word = ntohs(word);
        ASSERT_EQ(beams[i].getXCenter(), word);
        offset = offset + 2;
        memcpy(&word, buffer.data()+offset, 2);
        word = ntohs(word);
        ASSERT_EQ(beams[i].getYCenter(), word);
        offset = offset + 2;
        ASSERT_EQ(beams[i].getAngle(), buffer[offset]);
        offset++;
        ASSERT_EQ(beams[i].getLenghth(), buffer[offset]);
        offset++;
        ASSERT_EQ(beams[i].getHeight(), buffer[offset]);
        offset++;
    }
    ASSERT_EQ(dto.getIdPlayer(), buffer[offset]);
    offset++;
    memcpy(&word, buffer.data()+offset, 2);
    word = ntohs(word);
    ASSERT_EQ(dto.getPositionYWater(), word);
    offset = offset + 2;
    memcpy(&word, buffer.data()+offset, 2);
    word = ntohs(word);
    ASSERT_EQ(dto.getBackground().size(), word);
    offset = offset + 2;
    std::string aux(buffer.data()+offset, word);
    ASSERT_EQ(dto.getBackground(), aux);
}
TEST(TEST_PROTOCOL_SERVER_SEND, sendPlayersDTO) {
    // Arrenge
    Socket skt;
    size_t offset = 0;
    uint16_t word;
    ServerProtocol protocol(skt);
    std::vector<char> buffer;
    std::vector<PlayerDTO> players;
    players.push_back(PlayerDTO(15, "fede", MY_TURN, 100));
    players.push_back(PlayerDTO(42, "pepe", NOT_IS_MY_TURN, 125));
    PlayersDTO dto(players);
    // Act
    protocol.sendPlayersDTO(dto);
    // Assert
    buffer = skt.getBuffer();
    ASSERT_TRUE(PLAYERS_TOTAL == buffer[offset]);
    offset++;
    ASSERT_EQ(players.size(), buffer[offset]);
    offset++;
    for (size_t i = 0; i < players.size(); i++) {
        ASSERT_TRUE(PLAYER == buffer[offset]);
        offset++;
        ASSERT_TRUE(players[i].getIdPlayer() == buffer[offset]);
        offset++;
        memcpy(&word, buffer.data()+offset, 2);
        word = ntohs(word);
        ASSERT_TRUE(players[i].getNamePlayer().size() == word);
        offset = offset + 2;
        std::string aux(buffer.data()+offset, word);
        ASSERT_TRUE(players[i].getNamePlayer() == aux);
        offset = offset + word;
        ASSERT_TRUE(players[i].getTurnType() == buffer[offset]);
        offset++;
        memcpy(&word, buffer.data()+offset, 2);
        word = ntohs(word);
        ASSERT_TRUE(players[i].getTotalHpWorms() == word);
        offset = offset + 2;
    }
}
TEST(TEST_PROTOCOL_SERVER_SEND, sendAWormDTO) {
    // Arrenge
    Socket skt;
    size_t offset = 0;
    uint16_t word;
    ServerProtocol protocol(skt);
    std::vector<char> buffer;
    WormDTO dto(50, 75, 69, 125, LEFT, NO_FOCUS, WALKING, RED_GRENADE);
    // Act
    protocol.sendAWormDTO(dto);
    // Assert
    buffer = skt.getBuffer();
    ASSERT_EQ(dto.getOperationType(), buffer[offset]);
    offset++;
    memcpy(&word, buffer.data()+offset, 2);
    word = ntohs(word);
    ASSERT_EQ(dto.getPositionX(), word);
    offset = offset + 2;
    memcpy(&word, buffer.data()+offset, 2);
    word = ntohs(word);
    ASSERT_EQ(dto.getPositionY(), word);
    offset = offset + 2;
    ASSERT_EQ(dto.getIdPlayer(), buffer[offset]);
    offset++;
    ASSERT_EQ(dto.getHpWorm(), buffer[offset]);
    offset++;
    ASSERT_EQ(dto.getDirectionLook(), buffer[offset]);
    offset++;
    ASSERT_EQ(dto.getMoveWorm(), buffer[offset]);
    offset++;
    ASSERT_EQ(dto.getTypeFocus(), buffer[offset]);
    offset++;
    ASSERT_EQ(dto.getWeaponCurrent(), buffer[offset]);
}
TEST(TEST_PROTOCOL_SERVER_SEND, sendWeaponsDTO) {
    // Arrenge
    Socket skt;
    size_t offset = 0;
    uint16_t word;
    ServerProtocol protocol(skt);
    std::vector<char> buffer;
    std::vector<WeaponDTO> weapons;
    weapons.push_back(WeaponDTO(BANANA, NO_INFINITE, 100));
    weapons.push_back(WeaponDTO(HOLY_GRENADE, NO_INFINITE, 5));
    weapons.push_back(WeaponDTO(MORTAR, NO_INFINITE, 1));
    WeaponsDTO dto(25, weapons, BANANA);
    // Act
    protocol.sendWeaponsDTO(dto);
    // Assert
    buffer = skt.getBuffer();
    ASSERT_EQ(dto.getOperationType(), buffer[offset]);
    offset++;
    ASSERT_EQ(dto.getIdPlayer(), buffer[offset]);
    offset++;
    ASSERT_EQ(dto.getWeaponCurrent(), buffer[offset]);
    offset++;
    ASSERT_EQ(weapons.size(), buffer[offset]);
    offset++;
    for (size_t i = 0; i < weapons.size(); i++) {
        ASSERT_EQ(weapons[i].getOperationType(), buffer[offset]);
        offset++;
        ASSERT_EQ(weapons[i].getTypeWeapon(), buffer[offset]);
        offset++;
        ASSERT_EQ(weapons[i].getTypeMunition(), buffer[offset]);
        offset++;
        ASSERT_EQ(weapons[i].getMunition(), buffer[offset]);
        offset++;
    }
}
TEST(TEST_PROTOCOL_SERVER_SEND, sendWeaponSightDTO) {
    // Arrenge
    Socket skt;
    size_t offset = 0;
    uint16_t word;
    ServerProtocol protocol(skt);
    std::vector<char> buffer;
    WeaponSightDTO dto(NO_SHOW_SIGHT, 1, 0);
    // Act
    protocol.sendWeaponSightDTO(dto);
    // Assert
    buffer = skt.getBuffer();
    ASSERT_EQ(WEAPON_SIGHT, buffer[offset]);
    offset++;
    ASSERT_EQ(NO_SHOW_SIGHT, buffer[offset]);
    offset++;
    memcpy(&word, buffer.data()+offset, 2);
    word = ntohs(word);
    ASSERT_EQ(1, word);
    offset = offset + 2;
    memcpy(&word, buffer.data()+offset, 2);
    word = ntohs(word);
    ASSERT_EQ(0, word);
}
TEST(TEST_PROTOCOL_SERVER_SEND, sendProjectilesDTO) {
    // Arrenge
    Socket skt;
    size_t offset = 0;
    uint16_t word;
    ServerProtocol protocol(skt);
    std::vector<char> buffer;
    std::vector<ProjectileDTO> projectiles;
    projectiles.push_back(ProjectileDTO(BAZOOKA_PROJECTILE, 25, 33, NO_FOCUS, EXPLODE));
    projectiles.push_back(ProjectileDTO(NONE_PROJECTILE, 96, 123, FOCUS, NO_EXPLODE));
    projectiles.push_back(ProjectileDTO(AIR_ATTACK_MISSILE, 6582, 8743, FOCUS, EXPLODE));
    ProjectilesDTO dto(SHOW_PROJECTILES, projectiles);
    // Act
    protocol.sendProjectilesDTO(dto);
    // Assert
    buffer = skt.getBuffer();
    ASSERT_EQ(dto.getOperationType(), buffer[offset]);
    offset++;
    ASSERT_EQ(dto.getTypeShowProjectiles(), buffer[offset]);
    offset++;
    ASSERT_EQ(projectiles.size(), buffer[offset]);
    offset++;
    for (size_t i = 0; i < projectiles.size(); i++) {
        ASSERT_EQ(projectiles[i].getOperationType(), buffer[offset]);
        offset++;
        ASSERT_EQ(projectiles[i].getTypeProjectil(), buffer[offset]);
        offset++;
        memcpy(&word, buffer.data()+offset, 2);
        word = ntohs(word);
        ASSERT_EQ(projectiles[i].getPositionX(), word);
        offset = offset + 2;
        memcpy(&word, buffer.data()+offset, 2);
        word = ntohs(word);
        ASSERT_EQ(projectiles[i].getPositionY(), word);
        offset = offset + 2;
        ASSERT_EQ(projectiles[i].getTypeFocus(), buffer[offset]);
        offset++;
        ASSERT_EQ(projectiles[i].getTypeExplode(), buffer[offset]);
        offset++;
    }
}
TEST(TEST_PROTOCOL_SERVER_SEND, sendTurnDTO) {
    // Arrenge
    Socket skt;
    size_t offset = 0;
    uint16_t word;
    ServerProtocol protocol(skt);
    std::vector<char> buffer;
    TurnDTO dto(120, "texto", 10, 5, WIND_RIGHT);
    // Act
    protocol.sendTurnDTO(dto);
    // Assert
    buffer = skt.getBuffer();
    ASSERT_EQ(dto.getOperationType(), buffer[offset]);
    offset++;
    ASSERT_EQ(120, buffer[offset]);
    offset++;
    memcpy(&word, buffer.data()+offset, 2);
    word = ntohs(word);
    ASSERT_TRUE(dto.getTextTurn().size() == word);
    offset = offset + 2;
    std::string aux(buffer.data()+offset, word);
    ASSERT_TRUE(dto.getTextTurn() == aux);
    offset = offset + word;
    ASSERT_EQ(dto.getTimeLeft(), buffer[offset]);
    offset++;
    ASSERT_EQ(dto.getValueWind(), buffer[offset]);
    offset++;
    ASSERT_EQ(dto.getTypeWind(), buffer[offset]);
}
TEST(TEST_PROTOCOL_SERVER_SEND, sendAProvisionDTO) {
    // Arrenge
    Socket skt;
    size_t offset = 0;
    uint16_t word;
    ServerProtocol protocol(skt);
    std::vector<char> buffer;
    ProvisionDTO dto(23, 97, MEDICAL_KIT, CONTACT);
    // Act
    protocol.sendAProvisionDTO(dto);
    // Assert
    buffer = skt.getBuffer();
    ASSERT_EQ(PROVISION_DTO, buffer[offset]);
    offset++;
    memcpy(&word, buffer.data()+offset, 2);
    word = ntohs(word);
    ASSERT_EQ(23, word);
    offset = offset + 2;
    memcpy(&word, buffer.data()+offset, 2);
    word = ntohs(word);
    ASSERT_EQ(97, word);
    offset = offset + 2;
    ASSERT_EQ(MEDICAL_KIT, buffer[offset]);
    offset++;
    ASSERT_EQ(CONTACT, buffer[offset]);
}
TEST(TEST_PROTOCOL_SERVER_SEND, sendEndGameDTO) {
    // Arrenge
    Socket skt;
    size_t offset = 0;
    ServerProtocol protocol(skt);
    std::vector<char> buffer;
    EndGameDTO dto(113, WON_THE_GAME);
    // Act
    protocol.sendEndGameDTO(dto);
    // Assert
    buffer = skt.getBuffer();
    ASSERT_EQ(END_DTO, buffer[offset]);
    offset++;
    ASSERT_EQ(113, buffer[offset]);
    offset++;
    ASSERT_EQ(WON_THE_GAME, buffer[offset]);
}
TEST(TEST_PROTOCOL_SERVER_SEND, sendSnapShot_GAME_PROGRESS) {
    // Arrenge
    Socket skt;
    size_t offset = 0;
    ServerProtocol protocol(skt);
    std::vector<char> buffer;
    std::vector<WormDTO> worms;
    worms.push_back(WormDTO(50, 75, 69, 125, LEFT, NO_FOCUS, WALKING, RED_GRENADE));
    std::vector<PlayerDTO> player;
    player.push_back(PlayerDTO(15, "fede", NOT_IS_MY_TURN, 100));
    PlayersDTO players(player);
    std::vector<WeaponDTO> weapon;
    weapon.push_back(WeaponDTO(BANANA, NO_INFINITE, 100));
    WeaponsDTO weapons(12, weapon, BANANA);
    WeaponSightDTO sight(NO_SHOW_SIGHT, 1, 0);
    std::vector<ProjectileDTO> projectile;
    projectile.push_back(ProjectileDTO(BAZOOKA_PROJECTILE, 25, 33, NO_FOCUS, NO_EXPLODE));
    ProjectilesDTO projectiles(SHOW_PROJECTILES, projectile);
    TurnDTO turn(120, "texto", 10, 5, WIND_RIGHT);
    std::vector<ProvisionDTO> provisions;
    provisions.push_back(ProvisionDTO(23, 97, MEDICAL_KIT, NO_CONTACT));
    std::unique_ptr<SnapShot> dto = std::unique_ptr<SnapShot>
                (new SnapShot(worms, players, weapons, sight, projectiles, turn, provisions));
    // Act
    protocol.sendSnapShot(dto);
    // Assert
    buffer = skt.getBuffer();
    ASSERT_EQ(SNAP_SHOT, buffer[offset]);
    offset++;
    ASSERT_EQ(GAME_PROGRESS, buffer[offset]);
    offset++;
    ASSERT_EQ(1, buffer[offset]);
}
TEST(PROTOCOL_SERVER_RECV, recvInitialStateDTO_SCENARIO_LIST_REQUEST) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    InitialStateDTO dtoClient(SCENARIO_LIST_REQUEST, "name");
    // Act
    client.sendInitialStateDTO(dtoClient);
    InitialStateDTO dtoServer = server.recvInitialStateDTO();
    // Assert
    ASSERT_EQ(dtoClient, dtoServer);
}
TEST(PROTOCOL_SERVER_RECV, recvInitialStateDTO_ROOM_LIST_REQUEST) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    InitialStateDTO dtoClient(ROOM_LIST_REQUEST, "soy el jugador");
    // Act
    client.sendInitialStateDTO(dtoClient);
    InitialStateDTO dtoServer = server.recvInitialStateDTO();
    // Assert
    ASSERT_EQ(dtoClient, dtoServer);
}
TEST(PROTOCOL_SERVER_RECV, recvReponseInitialStateDTO_FINAL_CREATE_GAME) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    ResponseInitialStateDTO dtoClient(FINAL_CREATE_GAME, "partida a muerte", "mapa 1v1", 2);
    // Act
    client.sendResponseInitialStateDTO(dtoClient);
    ResponseInitialStateDTO dtoServer = server.recvReponseInitialStateDTO();
    // Assert
    ASSERT_EQ(dtoClient, dtoServer);
}
TEST(PROTOCOL_SERVER_RECV, recvReponseInitialStateDTO_FINAL_JOIN_GAME) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    ResponseInitialStateDTO dtoClient(FINAL_CREATE_GAME, "partida de chill");
    // Act
    client.sendResponseInitialStateDTO(dtoClient);
    ResponseInitialStateDTO dtoServer = server.recvReponseInitialStateDTO();
    // Assert
    ASSERT_EQ(dtoClient, dtoServer);
}
TEST(PROTOCOL_SERVER_RECV, recvCommandDTO) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    CommandDTO dtoClient;
    dtoClient.setTypeCommand(SELECT_BANANA);
    dtoClient.setX(42);
    dtoClient.setY(69);
    // Act
    client.sendCommandDTO(dtoClient);
    CommandDTO dtoServer = server.recvCommandDTO();
    // Assert
    ASSERT_EQ(dtoClient, dtoServer);
}
TEST(PROTOCOL_CLIENT_RECV, recvResolverInitialDTO_RESPONSE_INITIAL_CREATE_GAME) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    std::vector<std::string> scenarios;
    std::vector<size_t> maxPlayers;
    scenarios.push_back("Ruinas");
    maxPlayers.push_back(3);
    scenarios.push_back("Laboratorio");
    maxPlayers.push_back(8);
    scenarios.push_back("Cascadas");
    maxPlayers.push_back(14);
    scenarios.push_back("core");
    maxPlayers.push_back(5);
    ResolverInitialDTO dtoServer(RESPONSE_INITIAL_CREATE_GAME, scenarios, maxPlayers);
    // Act
    server.sendResolverInitialDTO(dtoServer);
    ResolverInitialDTO dtoClient = client.recvResolverInitialDTO();
    // Assert
    ASSERT_EQ(dtoClient, dtoServer);
}
TEST(PROTOCOL_CLIENT_RECV, recvResolverInitialDTO_RESPONSE_FINAL_CREATE_GAME) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    ResolverInitialDTO dtoServer(RESPONSE_FINAL_CREATE_GAME, 1);
    // Act
    server.sendResolverInitialDTO(dtoServer);
    ResolverInitialDTO dtoClient = client.recvResolverInitialDTO();
    // Assert
    ASSERT_EQ(dtoClient, dtoServer);
}
TEST(PROTOCOL_CLIENT_RECV, recvRoom) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    RoomDTO serverRoom("my partida", "super mapa divertido", 1, 4);
    // Act
    server.sendRoom(serverRoom);
    RoomDTO clientRoom = client.recvRoom();
    // Assert
    ASSERT_EQ(serverRoom, clientRoom);
}
TEST(PROTOCOL_CLIENT_RECV, recvResolverInitialDTO_RESPONSE_INITIAL_JOIN_GAME) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    ResolverInitialDTO dtoServer;
    dtoServer.setOperationType(RESPONSE_INITIAL_JOIN_GAME);
    std::vector<RoomDTO> games;
    std::vector<std::string> names;
    std::vector<std::string> scenarios;
    std::vector<size_t> currentPlayers;
    std::vector<size_t> maxPlayers;
    names.push_back("mi partida");
    names.push_back("partida adsgsdsd");
    scenarios.push_back("mapa pequeño");
    scenarios.push_back("mapa definitivo mortal xd");
    currentPlayers.push_back(1);
    currentPlayers.push_back(3);
    maxPlayers.push_back(5);
    maxPlayers.push_back(9);
    games.push_back(RoomDTO(names[0], scenarios[0], currentPlayers[0], maxPlayers[0]));
    games.push_back(RoomDTO(names[1], scenarios[1], currentPlayers[1], maxPlayers[1]));
    dtoServer.setGameRooms(games);
    // Act
    server.sendResolverInitialDTO(dtoServer);
    ResolverInitialDTO dtoClient = client.recvResolverInitialDTO();
    // Assert
    ASSERT_EQ(dtoClient, dtoServer);
}
TEST(PROTOCOL_CLIENT_RECV, recvResolverInitialDTO_RESPONSE_FINAL_JOIN_GAME) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    ResolverInitialDTO dtoServer(RESPONSE_FINAL_JOIN_GAME, 1);
    // Act
    server.sendResolverInitialDTO(dtoServer);
    ResolverInitialDTO dtoClient = client.recvResolverInitialDTO();
    // Assert
    ASSERT_EQ(dtoClient, dtoServer);
}
TEST(PROTOCOL_CLIENT_RECV, recvResolverInitialDTO_START_GAME) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    // Act
    server.sendANumberByte(START_GAME);
    ResolverInitialDTO dtoServer;
    dtoServer.setOperationType(START_GAME);
    ResolverInitialDTO dtoClient = client.recvResolverInitialDTO();
    // Assert
    ASSERT_EQ(dtoClient, dtoServer);
}
TEST(PROTOCOL_CLIENT_RECV, recvBeamDTO) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    BeamDTO dtoServer(SHORT_BEAM, 53, 69, 120, 78, 96);
    // Act
    server.sendBeamDTO(dtoServer);
    BeamDTO dtoClient = client.recvBeamDTO();
    // Assert
    ASSERT_EQ(dtoClient, dtoServer);
}
TEST(PROTOCOL_CLIENT_RECV, recvStageDTO) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    std::vector<BeamDTO> beams;
    beams.push_back(BeamDTO(SHORT_BEAM, 53, 69, 120, 78, 96));
    beams.push_back(BeamDTO(WATER_BEAM, 153, 169, 20, 178, 196));
    beams.push_back(BeamDTO(LONG_BEAM, 0, 0, 255, 255, 255));
    StageDTO dtoServer;
    dtoServer.setIdPlayer(2);
    dtoServer.setBeams(beams);
    // Act
    server.sendStage(dtoServer);
    StageDTO dtoClient = client.recvStageDTO();
    // Assert
    ASSERT_EQ(dtoClient, dtoServer);
}
TEST(PROTOCOL_CLIENT_RECV, recvAPlayerDTO) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    PlayerDTO dtoServer(27, "Sergio", MY_TURN, 125);
    // Act
    server.sendAPlayerDTO(dtoServer);
    PlayerDTO dtoClient = client.recvAPlayerDTO();
    // Assert
    ASSERT_EQ(dtoClient, dtoServer);
}
TEST(PROTOCOL_CLIENT_RECV, recvPlayersDTO) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    std::vector<PlayerDTO> players;
    players.push_back(PlayerDTO(15, "fede", MY_TURN, 100));
    players.push_back(PlayerDTO(42, "pepe", NOT_IS_MY_TURN, 125));
    PlayersDTO dtoServer(players);
    // Act
    server.sendPlayersDTO(dtoServer);
    PlayersDTO dtoClient = client.recvPlayersDTO();
    // Assert
    ASSERT_EQ(dtoClient, dtoServer);
}
TEST(PROTOCOL_CLIENT_RECV, recvAWormDTO) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    WormDTO dtoServer(50, 75, 69, 125, LEFT, NO_FOCUS, WALKING, RED_GRENADE);
    // Act
    server.sendAWormDTO(dtoServer);
    WormDTO dtoClient = client.recvAWormDTO();
    // Assert
    ASSERT_EQ(dtoClient, dtoServer);
}
TEST(PROTOCOL_CLIENT_RECV, recvAWeaponDTO) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    WeaponDTO dtoServer(BANANA, NO_INFINITE, 100);
    // Act
    server.sendAWeaponDTO(dtoServer);
    WeaponDTO dtoClient = client.recvAWeaponDTO();
    // Assert
    ASSERT_EQ(dtoClient, dtoServer);
}
TEST(PROTOCOL_CLIENT_RECV, recvWeaponsDTO) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    std::vector<WeaponDTO> weapons;
    weapons.push_back(WeaponDTO(BANANA, NO_INFINITE, 100));
    weapons.push_back(WeaponDTO(HOLY_GRENADE, NO_INFINITE, 5));
    weapons.push_back(WeaponDTO(MORTAR, NO_INFINITE, 1));
    WeaponsDTO dtoServer(25, weapons, BANANA);
    // Act
    server.sendWeaponsDTO(dtoServer);
    WeaponsDTO dtoClient = client.recvWeaponsDTO();
    // Assert
    ASSERT_EQ(dtoClient, dtoServer);
}
TEST(PROTOCOL_CLIENT_RECV, recvWeaponSightDTO) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    WeaponSightDTO dtoServer(NO_SHOW_SIGHT, 1, 0);
    // Act
    server.sendWeaponSightDTO(dtoServer);
    WeaponSightDTO dtoClient = client.recvWeaponSightDTO();
    // Assert
    ASSERT_EQ(dtoClient, dtoServer);
}
TEST(PROTOCOL_CLIENT_RECV, recvAProjectileDTO) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    ProjectileDTO dtoServer(BAZOOKA_PROJECTILE, 25, 33, NO_FOCUS, EXPLODE);
    // Act
    server.sendAProjectileDTO(dtoServer);
    ProjectileDTO dtoClient = client.recvAProjectileDTO();
    // Assert
    ASSERT_EQ(dtoClient, dtoServer);
}
TEST(PROTOCOL_CLIENT_RECV, recvProjectilesDTO) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    std::vector<ProjectileDTO> projectiles;
    projectiles.push_back(ProjectileDTO(BAZOOKA_PROJECTILE, 25, 33, NO_FOCUS, EXPLODE));
    projectiles.push_back(ProjectileDTO(NONE_PROJECTILE, 96, 123, FOCUS, NO_EXPLODE));
    projectiles.push_back(ProjectileDTO(AIR_ATTACK_MISSILE, 6582, 8743, FOCUS, EXPLODE));
    // Act
    ProjectilesDTO dtoServer(SHOW_PROJECTILES, projectiles);
    server.sendProjectilesDTO(dtoServer);
    ProjectilesDTO dtoClient = client.recvProjectilesDTO();
    // Assert
    ASSERT_EQ(dtoClient, dtoServer);
}
TEST(PROTOCOL_CLIENT_RECV, recvEndGameDTO) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    EndGameDTO dtoServer(113, WON_THE_GAME);
    // Act
    server.sendEndGameDTO(dtoServer);
    EndGameDTO dtoClient = client.recvEndGameDTO();
    // Assert
    ASSERT_EQ(dtoClient, dtoServer);
}
TEST(PROTOCOL_CLIENT_RECV, recvAProvisionDTO) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    ProvisionDTO dtoServer(23, 97, MEDICAL_KIT, CONTACT);
    // Act
    server.sendAProvisionDTO(dtoServer);
    ProvisionDTO dtoClient = client.recvAProvisionDTO();
    // Assert
    ASSERT_EQ(dtoClient, dtoServer);
}
TEST(PROTOCOL_CLIENT_RECV, recvSnapShot) {
    // Arrenge
    Socket skt;
    ClientProtocol client(skt);
    ServerProtocol server(skt);
    std::vector<WormDTO> worms;
    worms.push_back(WormDTO(50, 75, 69, 125, LEFT, NO_FOCUS, WALKING, RED_GRENADE));
    worms.push_back(WormDTO(125, 69, 75, 50, RIGHT, FOCUS, STANDING, AIR_ATTACK));
    std::vector<PlayerDTO> player;
    player.push_back(PlayerDTO(15, "fede", NOT_IS_MY_TURN, 100));
    player.push_back(PlayerDTO(51, "rodolfo", MY_TURN, 125));
    PlayersDTO players(player);
    std::vector<WeaponDTO> weapon;
    weapon.push_back(WeaponDTO(BANANA, NO_INFINITE, 100));
    weapon.push_back(WeaponDTO(BAZOOKA, NO_INFINITE, 100));
    weapon.push_back(WeaponDTO(BASEBALL_BAT, NO_INFINITE, 100));
    WeaponsDTO weapons(12, weapon, BANANA);
    WeaponSightDTO sight(NO_SHOW_SIGHT, 1, 0);
    std::vector<ProjectileDTO> projectile;
    projectile.push_back(ProjectileDTO(BAZOOKA_PROJECTILE, 25, 33, NO_FOCUS, NO_EXPLODE));
    projectile.push_back(ProjectileDTO(PROJ_BANANA, 33, 25, FOCUS, NO_EXPLODE));
    projectile.push_back(ProjectileDTO(PROJ_MORTAR, 100, 100, NO_FOCUS, NO_EXPLODE));
    ProjectilesDTO projectiles(SHOW_PROJECTILES, projectile);
    TurnDTO turn(120, "texto", 10, 5, WIND_RIGHT);
    std::vector<ProvisionDTO> provisions;
    provisions.push_back(ProvisionDTO(23, 97, MEDICAL_KIT, NO_CONTACT));
    provisions.push_back(ProvisionDTO(15, 96, MEDICAL_KIT, NO_CONTACT));
    provisions.push_back(ProvisionDTO(97, 23, MEDICAL_KIT, NO_CONTACT));
    std::unique_ptr<SnapShot> dtoServer = std::unique_ptr<SnapShot>
                (new SnapShot(worms, players, weapons, sight, projectiles, turn, provisions));
    // Act
    server.sendSnapShot(dtoServer);
    SnapShot dtoClient = client.recvSnapShot();
    // Assert
    ASSERT_EQ(dtoClient, *dtoServer);
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
