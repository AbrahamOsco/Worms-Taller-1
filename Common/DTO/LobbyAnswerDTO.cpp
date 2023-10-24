//
// Created by abraham on 24/10/23.
//

#include "LobbyAnswerDTO.h"

LobbyAnswerDTO::LobbyAnswerDTO() : DTO(INITIAL_STATE), gameName(""), selectedScenario("") {
}

void LobbyAnswerDTO::setGameName(const std::string &aGameName) {
    this->gameName = aGameName;
}

void LobbyAnswerDTO::setSelectScenario(const std::string &aSelectedScenario) {
    this->selectedScenario = aSelectedScenario;
}

std::string LobbyAnswerDTO::getGameName() const {
    return gameName;
}

std::string LobbyAnswerDTO::getSelectedScenario() const {
    return selectedScenario;
}





