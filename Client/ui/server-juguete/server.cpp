#include <iostream>
#include <string>
#include "socket.h"
#include <string>
#include <vector>
#include <fstream>


void map_list(Socket& skt,bool& closed){
    std::vector<std::string> maps;
    std::string map;
    std::fstream mapsfile("mapas.txt",std::fstream::in);
    while(std::getline(mapsfile,map))
        maps.push_back(map);
    uint8_t lenght = maps.size();
    uint8_t code = 0;
    skt.sendall(&code,1,&closed);
    skt.sendall(&lenght,1,&closed);
    for(uint i = 0;i<maps.size();i++){
        lenght = maps[i].size();
        skt.sendall(&lenght,1,&closed);
        skt.sendall(maps[i].data(),lenght,&closed);
    } 
}
void game_list(Socket& skt,bool& closed){}
void game_info(Socket& skt,bool& closed){}
void create_game(Socket& skt,bool& closed){}
void join_game(Socket& skt,bool& closed){}

int main(int args,char* argv[]){
    bool closed = false;
    uint8_t code;
    Socket socket(argv[1]);
    Socket skt = socket.accept();
    while(!closed){
        skt.recvall(&code,1,&closed);
        std::cout << "code: " << (int) code << std::endl;
        switch(code){
            case(0):
                map_list(skt,closed);
                break;
            case(1):
                game_list(skt,closed);
                break;
            case(2):
                game_info(skt,closed);
                break;
            case(3):
                create_game(skt,closed);
                break;
            case(4):
                join_game(skt,closed);
                break;
        }
    }
}