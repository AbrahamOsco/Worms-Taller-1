#ifndef WORMS_TALLER_1_SERVERPROTOCOL_H
#define WORMS_TALLER_1_SERVERPROTOCOL_H

#include <memory>
#include "../../../Common/Protocol/Protocol.h"
#include "../../../Common/Socket/Socket.h"
#include "../../../Common/DTO/ResolverInitialDTO.h"
#include "../../../Common/DTO/InitialStateDTO.h"
#include "../../../Common/DTO/ResponseInitialStateDTO.h"
#include "../../../Common/DTO/StageDTO.h"
#include "../../../Common/DTO/PlayerDTO.h"
#include "../../../Common/DTO/PlayersDTO.h"
#include "../../../Common/DTO/CommandDTO.h"
#include "../../../Common/DTO/SnapShot.h"

#define BYTE_DISCONNECT 0
#define STATUS_ERROR 2

class ServerProtocol : public Protocol {

public:
    explicit ServerProtocol(Socket& skt);

    InitialStateDTO recvInitialStateDTO();

    ResponseInitialStateDTO recvReponseInitialStateDTO();

    void sendResolverInitialDTO(const ResolverInitialDTO& resolverInitial);

    void sendRoom(const RoomDTO &aRoomDTO);

    void sendStage(const StageDTO& stageDTO);

    void sendBeam(const BeamDTO& beamDTO);

    ~ServerProtocol() = default;


    CommandDTO recvCommandDTO();

    void sendPlayersDTO(const PlayersDTO &aPlayersDTO);

    void sendAPlayerDTO(const PlayerDTO &playerDTO);

    //void sendAWormIniDTO(const WormDTO &aWormDTO);

    void sendSnapShot(const std::unique_ptr<SnapShot> &aSnapShot);

    void sendAWormDTO(const WormDTO &aWormDTO);
};


#endif //WORMS_TALLER_1_SERVERPROTOCOL_H
