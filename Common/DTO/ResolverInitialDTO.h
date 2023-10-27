//
// Created by abraham on 26/10/23.
//

#ifndef WORMS_TALLER_1_RESOLVERINITIALDTO_H
#define WORMS_TALLER_1_RESOLVERINITIALDTO_H


#include <vector>
#include <string>
#include "DTO.h"
#include "RoomDTO.h"

class ResolverInitialDTO : public DTO {
private:
    std::vector<std::string> scenariosNames;
    size_t statusAnswer;
    std::vector<RoomDTO> gameRooms;

public:
    ResolverInitialDTO();

    ResolverInitialDTO(const OperationType& operationType, const std::vector<std::string>& aScenariosNames);

    ResolverInitialDTO(const OperationType& operationType, const std::vector<RoomDTO>& aGameRooms);

    ResolverInitialDTO(const OperationType& operationType, const size_t& aStatusAnswer);

    void setScenarioNames(const std::vector<std::string>& aScenariosNames);

    void setStatusAnswer(const size_t& aStatusAnswer);

    void setGameRooms(const std::vector<RoomDTO>& aGameRooms);

    std::vector<std::string> getScenariosNames() const;

    size_t getStatusAnswer() const;

    std::vector<RoomDTO> getGameRooms() const;
};


#endif //WORMS_TALLER_1_RESOLVERINITIALDTO_H
