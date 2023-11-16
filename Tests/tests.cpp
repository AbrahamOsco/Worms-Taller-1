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


TEST(TESTMOCKSOCKET,SENDSOME){
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
TEST(TESTMOCKSOCKET,RECVSOME){
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
TEST(TESTPROTOCOLCLIENT,sendInitialStateDTO){
    Socket skt;
    ClientProtocol protocol(skt);
    std::vector<char> data;
    std::string name("Pedro");
    InitialStateDTO send(SCENARIO_LIST_REQUEST,name);
    protocol.sendInitialStateDTO(send);
    std::vector<char> buffer = skt.getBuffer();
    uint16_t size;
    memcpy(&size,buffer.data()+1,2);
    size = ntohs(size);
    ASSERT_TRUE(SCENARIO_LIST_REQUEST == buffer[0]);
    ASSERT_TRUE(5 == size);
    for(size_t i = 0;i< name.size();i++){
        ASSERT_TRUE(name[i] == buffer[i+3]);
    }
}

int main(int argc,char* argv[]){
    testing::InitGoogleTest(&argc,argv);

    return RUN_ALL_TESTS();
}