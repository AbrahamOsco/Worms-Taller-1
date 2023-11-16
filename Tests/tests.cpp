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
    for(int i = 0;i<10;i++){
        data.push_back((char) i+60);
    }
    bool closed;
    skt.sendall(data.data(),5,&closed);
    skt.sendall(data.data()+5,5,&closed);
    std::vector<char> buff = skt.getBuffer();
    for(int i = 0;i<10;i++)    
        ASSERT_TRUE(data[i] == buff[i]);
}
TEST(TEST_MOCK_SOCKET,RECV_SOME){
    Socket skt;
    std::vector<char> data;
    for(int i = 0;i<10;i++){
        data.push_back((char) i);
    }
    skt.setBuffer(data);
    bool closed;
    std::vector<char> read(10);
    skt.recvall(read.data(),4,&closed);
    skt.recvall(read.data()+4,6,&closed);
    for(int i = 0;i<10;i++)    
        ASSERT_TRUE(data[i] == read[i]);
}
TEST(TEST_PROTOCOL_CLIENT,sendInitialStateDTO){
    Socket skt;
    ClientProtocol protocol(skt);
    std::string name("Pedro");
    InitialStateDTO dto(SCENARIO_LIST_REQUEST,name);
    protocol.sendInitialStateDTO(dto);
    std::vector<char> buffer = skt.getBuffer();
    uint16_t size;
    size_t offset = 0;
    ASSERT_TRUE(SCENARIO_LIST_REQUEST == buffer[offset]);
    offset++;
    memcpy(&size,buffer.data()+offset,2);
    size = ntohs(size);
    ASSERT_TRUE(name.size() == size);
    offset = offset + 2;
    for(size_t i = 0;i< name.size();i++){
        ASSERT_TRUE(name[i] == buffer[i+offset]);
    }
}
TEST(TEST_PROTOCOL_CLIENT,sendResponseInitialStateDTO_Create_Game){
    Socket skt;
    ClientProtocol protocol(skt);
    std::string gameName("Mostaza");
    std::string scenarioName("Ruinas");
    size_t playersNumber = 5;
    ResponseInitialStateDTO dto(FINAL_CREATE_GAME,gameName,scenarioName,playersNumber);
    protocol.sendResponseInitialStateDTO(dto);
    std::vector<char> buffer = skt.getBuffer();
    size_t offset = 0;
    ASSERT_TRUE(FINAL_CREATE_GAME == buffer[0]);
    offset++;
    uint16_t size;
    memcpy(&size,buffer.data()+offset,2);
    size = ntohs(size);
    ASSERT_TRUE(gameName.size() == size);
    offset = offset+2;
    for(size_t i = 0;i< gameName.size();i++){
        ASSERT_TRUE(gameName[i] == buffer[i+offset]);
    }
    offset = offset + gameName.size();
    memcpy(&size,buffer.data()+offset,2);
    size = ntohs(size);
    ASSERT_TRUE(scenarioName.size() == size);
    offset = offset+2;
    for(size_t i = 0;i< scenarioName.size();i++){
        ASSERT_TRUE(scenarioName[i] == buffer[i+offset]);
    }
    offset = offset + scenarioName.size();
    ASSERT_TRUE(playersNumber == buffer[offset]);
}
TEST(TEST_PROTOCOL_CLIENT,sendResponseInitialStateDTO_Join_Game){
    Socket skt;
    ClientProtocol protocol(skt);
    std::string gameName("Mostaza");
    size_t offset = 0;
    ResponseInitialStateDTO dto(FINAL_JOIN_GAME,gameName);
    protocol.sendResponseInitialStateDTO(dto);
    std::vector<char> buffer = skt.getBuffer();
    ASSERT_TRUE(FINAL_JOIN_GAME == buffer[0]);
    offset++;
    uint16_t size;
    memcpy(&size,buffer.data()+offset,2);
    size = ntohs(size);
    ASSERT_TRUE(gameName.size() == size);
    offset = offset+2;
    for(size_t i = 0;i< gameName.size();i++){
        ASSERT_TRUE(gameName[i] == buffer[i+offset]);
    }
}

int main(int argc,char* argv[]){
    testing::InitGoogleTest(&argc,argv);

    return RUN_ALL_TESTS();
}