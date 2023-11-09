//
// Created by riclui on 09/11/23.
//

#include "PlayerInfo.h"

PlayerInfo::PlayerInfo(const LoaderParams &params, int id, const std::string &name, int totalLife) : GameObject(params),
                                                                                                     m_id(id),
                                                                                                     m_name(name),
                                                                                                     m_totalLife(
                                                                                                             totalLife) {}
