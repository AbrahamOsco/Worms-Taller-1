#include <iostream>
#include <gtest/gtest.h>
#include "Mock_Socket.h"
#include <vector>
#include <gmock/gmock.h>
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
#include <cstring>
#include <arpa/inet.h>


TEST(TEST_MOCK_SOCKET,SEND_SOME){
    Socket skt;
    std::vector<char> data;
    bool closed;
    std::vector<char> buff;

    for(int i = 0;i<10;i++){
        data.push_back((char) i+60);
    }
    skt.sendall(data.data(),5,&closed);
    skt.sendall(data.data()+5,5,&closed);
    buff = skt.getBuffer();

    for(int i = 0;i<10;i++)    
        ASSERT_TRUE(data[i] == buff[i]);
}
TEST(TEST_MOCK_SOCKET,RECV_SOME){
    Socket skt;
    std::vector<char> data;
    bool closed;
    std::vector<char> read(10);

    for(int i = 0;i<10;i++){
        data.push_back((char) i);
    }
    skt.setBuffer(data);
    skt.recvall(read.data(),4,&closed);
    skt.recvall(read.data()+4,6,&closed);

    for(int i = 0;i<10;i++)    
        ASSERT_TRUE(data[i] == read[i]);
}
TEST(TEST_PROTOCOL_COMMON_SEND,sendANumberByte){
    Socket skt;
    Protocol protocol(skt);
    uint8_t byte = 54;
    std::vector<char> buff;

    protocol.sendANumberByte(byte);
    buff = skt.getBuffer();

    ASSERT_TRUE(byte == buff[0]);
}
TEST(TEST_PROTOCOL_COMMON_SEND,sendNum2Bytes){
    Socket skt;
    Protocol protocol(skt);
    uint16_t word = 2000;
    uint16_t sent;
    std::vector<char> buff;

    protocol.sendNum2Bytes(word);
    buff = skt.getBuffer();
    memcpy(&sent,buff.data(),2);
    sent = ntohs(sent);

    ASSERT_TRUE(sent == word);
}
TEST(TEST_PROTOCOL_COMMON_RECV,recvANumberByte){
    Socket skt;
    Protocol protocol(skt);
    uint8_t byte = 25;
    uint8_t read;

    protocol.sendANumberByte(byte);
    read = protocol.recvANumberByte();

    ASSERT_TRUE(read == byte);
}
TEST(TEST_PROTOCOL_COMMON_RECV,recvNum2Bytes){
    Socket skt;
    Protocol protocol(skt);
    std::vector<char> data;
    uint16_t word = 0x12AC;
    uint16_t read;

    protocol.sendNum2Bytes(word);
    read = protocol.recvNum2Bytes();

    ASSERT_TRUE(word == read);
}
TEST(TEST_PROTOCOL_CLIENT_SEND,sendInitialStateDTO){
    Socket skt;
    uint16_t size;
    size_t offset = 0;
    std::vector<char> buffer;
    ClientProtocol protocol(skt);
    std::string name("Pedro");
    InitialStateDTO dto(SCENARIO_LIST_REQUEST,name);
    protocol.sendInitialStateDTO(dto);
    buffer = skt.getBuffer();
    ASSERT_TRUE(SCENARIO_LIST_REQUEST == buffer[offset]);
    offset++;
    memcpy(&size,buffer.data()+offset,2);
    size = ntohs(size);
    ASSERT_TRUE(name.size() == size);
    offset = offset + 2;
    std::string aux(buffer.data()+offset,size);
    ASSERT_TRUE(name == aux);
}
TEST(TEST_PROTOCOL_CLIENT_SEND,sendResponseInitialStateDTO_Create_Game){
    Socket skt;
    uint16_t size;
    ClientProtocol protocol(skt);
    std::vector<char> buffer;
    size_t offset = 0;
    std::string gameName("Mostaza");
    std::string scenarioName("Ruinas");
    size_t playersNumber = 5;
    ResponseInitialStateDTO dto(FINAL_CREATE_GAME,gameName,scenarioName,playersNumber);
    protocol.sendResponseInitialStateDTO(dto);
    buffer = skt.getBuffer();
    ASSERT_TRUE(FINAL_CREATE_GAME == buffer[0]);
    offset++;
    memcpy(&size,buffer.data()+offset,2);
    size = ntohs(size);
    ASSERT_TRUE(gameName.size() == size);
    offset = offset+2;
    std::string aux(buffer.data()+offset,size);
    ASSERT_TRUE(gameName == aux);
    offset = offset + gameName.size();
    memcpy(&size,buffer.data()+offset,2);
    size = ntohs(size);
    ASSERT_TRUE(scenarioName.size() == size);
    offset = offset+2;
    std::string aux2(buffer.data()+offset,size);
    ASSERT_TRUE(scenarioName == aux2);
    offset = offset + scenarioName.size();
    ASSERT_TRUE(playersNumber == buffer[offset]);
}
TEST(TEST_PROTOCOL_CLIENT_SEND,sendResponseInitialStateDTO_Join_Game){
    Socket skt;
    uint16_t size;
    ClientProtocol protocol(skt);
    std::vector<char> buffer;
    std::string gameName("Mostaza");
    size_t offset = 0;
    ResponseInitialStateDTO dto(FINAL_JOIN_GAME,gameName);
    protocol.sendResponseInitialStateDTO(dto);
    buffer = skt.getBuffer();
    ASSERT_TRUE(FINAL_JOIN_GAME == buffer[0]);
    offset++;
    memcpy(&size,buffer.data()+offset,2);
    size = ntohs(size);
    ASSERT_TRUE(gameName.size() == size);
    offset = offset+2;
    std::string aux(buffer.data()+offset,size);
    ASSERT_TRUE(gameName == aux);
}
TEST(TEST_PROTOCOL_CLIENT_SEND,sendCommandDTO){
    Socket skt;
    int x,y;
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
    protocol.sendCommandDTO(dto);
    buff = skt.getBuffer();
    ASSERT_TRUE(COMMAND == buff[offset]);
    offset++;
    ASSERT_TRUE(SELECT_HOLY_GRENADE == buff[offset]);
    offset++;
    memcpy(&word,buff.data()+offset,2);
    word = ntohs(word);
    ASSERT_TRUE(x == word);
    offset = offset + 2;
    memcpy(&word,buff.data()+offset,2);
    word = ntohs(word);
    ASSERT_TRUE(y == word);
}
TEST(TEST_PROTOCOL_SERVER_SEND,sendResolverInitialDTO_RES_INI_CREATE_GAME){
    Socket skt;
    ServerProtocol protocol(skt);
    std::vector<std::string> scenarios;
    std::vector<size_t> maxPlayers;
    std::vector<char> buffer;
    size_t offset = 0;
    uint8_t amount = 0;
    uint16_t word;
    std::string aux;

    scenarios.push_back("Ruinas");
    maxPlayers.push_back(3);
    amount++;
    scenarios.push_back("Laboratorio");
    maxPlayers.push_back(8);
    amount++;
    scenarios.push_back("Cascadas");
    maxPlayers.push_back(14);
    amount++;
    
    ResolverInitialDTO dto(RESPONSE_INITIAL_CREATE_GAME,scenarios,maxPlayers);
    protocol.sendResolverInitialDTO(dto);
    buffer = skt.getBuffer();
    ASSERT_TRUE(RESPONSE_INITIAL_CREATE_GAME == buffer[offset]);
    offset++;
    ASSERT_TRUE(amount == buffer[offset]);
    offset++;
    for(int i = 0;i<amount;i++){
        memcpy(&word,buffer.data()+offset,2);
        word = htons(word);
        ASSERT_TRUE(scenarios[i].size() == word);
        offset = offset + 2;
        std::string aux(buffer.data()+offset,word);
        ASSERT_TRUE(scenarios[i] == aux);
        offset = offset + word;
    }
}
TEST(TEST_PROTOCOL_SERVER_SEND,sendResolverInitialDTO_RES_FIN_CREATE_GAME){
    Socket skt;
    ServerProtocol protocol(skt);
    std::vector<char> buffer;
    ResolverInitialDTO dto(RESPONSE_FINAL_CREATE_GAME,1);
    protocol.sendResolverInitialDTO(dto);
    buffer = skt.getBuffer();
    ASSERT_TRUE(RESPONSE_FINAL_CREATE_GAME == buffer[0]);
    ASSERT_TRUE(1 == buffer[1]);
}
TEST(TEST_PROTOCOL_SERVER_SEND,sendResolverInitialDTO_RES_INI_JOIN_GAME){
    
}
int main(int argc,char* argv[]){
    testing::InitGoogleTest(&argc,argv);

    return RUN_ALL_TESTS();
}