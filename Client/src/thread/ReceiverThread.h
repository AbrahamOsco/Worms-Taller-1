//
// Created by riclui on 31/10/23.
//

#ifndef WORMS_TALLER_1_RECEIVERTHREAD_H
#define WORMS_TALLER_1_RECEIVERTHREAD_H

#include <memory>
#include <vector>
#include "../../../Common/Thread/Thread.h"
#include "../gameObject/GameObject.h"
#include "../protocol/ClientProtocol.h"
#include "../../../Common/Queue/Queue.h"
#include "../gameObject/worm/Worm.h"

class ReceiverThread : public Thread {
 private:
    Queue<std::vector<std::unique_ptr<GameObject>>>& m_queue;
    ClientProtocol& m_protocol;
    std::atomic<bool>& m_running;

 public:
    ReceiverThread(ClientProtocol &protocol, Queue<std::vector<std::unique_ptr<GameObject>>> &queue,
                    std::atomic<bool>& running);
    void run() override;
    void stop() override;

    void
    processGameProgressSnapshot(const SnapShot &snapShot,
            std::vector<std::unique_ptr<GameObject>> &gameObjects, size_t pastCountWorm, size_t currentCountWorm);

    void processNonGameProgressSnapshot(const SnapShot &snapShot,
                                        std::vector<std::unique_ptr<GameObject>> &gameObjects) const;

    void processWorms(const SnapShot &snapShot, bool isMyTurn,
                      std::vector<std::unique_ptr<GameObject>> &gameObjects);

    std::unique_ptr<Worm> createWormObject(const WormDTO &wormDto, const WeaponSightDTO &weaponSightDto, bool isMyTurn);

    void
    processProjectiles(const ProjectilesDTO &projectilesDto, std::vector<std::unique_ptr<GameObject>> &gameObjects);

    void
    processProvisions(const std::vector<ProvisionDTO> &provisions,
                      std::vector<std::unique_ptr<GameObject>> &gameObjects);

    void processGameInfo(const SnapShot &snapShot, std::vector<std::unique_ptr<GameObject>> &gameObjects,
                         bool deathWorm);
};


#endif  // WORMS_TALLER_1_RECEIVERTHREAD_H
