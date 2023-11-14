#include <iostream>
#include <gtest/gtest.h>
#include "Mock_Socket.h"
#include <vector>
#include <gmock/gmock.h> 

TEST(TESTPROTOCOL,SENDSOME){
    MockSocket skt;
    std::vector<char> data;
    for(int i = 0;i<10;i++){
        data.push_back((char) i);
    }
    bool closed;
    skt.sendall(data.data(),5,&closed);
    skt.sendall(data.data()+5,5,&closed);
    //skt.sendall(data.data()+1,9,&closed);
    std::vector<char> buff = skt.getBuffer();
    for(int i = 0;i<10;i++)    
        ASSERT_TRUE(data[i] == buff[i]);
}
TEST(TESTPROTOCOL,RECVSOME){
    MockSocket skt;
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


int main(int argc,char* argv[]){
    testing::InitGoogleTest(&argc,argv);

    return RUN_ALL_TESTS();
}