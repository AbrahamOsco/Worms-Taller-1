//
// Created by abraham on 13/11/23.
//

#include <iostream>
#include "GameContactListener.h"
#include "../Worm/Worm.h"
#include "../QueriesToWorld/SaveWormsInAreaQuery.h"
#include "../Scenario/Beam/Beam.h"
#include "../Provision/Provision.h"
#include "../Projectiles/AirAttackMissile.h"
#include "../Projectiles/Dynamite.h"
#include "../Projectiles/Grenades/Grenade/Grenade.h"

// Clase de colisiones el listener:
void wormCollidesWithBeam(GameObject* worm, GameObject* beam, GameParameters *gameParameters){
    std::cout << "Worm colisionar con el BEAM\n";
    Worm* unWorm = (Worm*) (worm);
    unWorm->assigOnABeam();
    Beam* unaBeam = (Beam*) (beam);
    if(unaBeam->getAngle() > 0.0f and unaBeam->getAngle() <= GameParameters::getBeamMinimumScalableAngle()){
        unWorm->activaeInclinedBeam();
    } else if ( unaBeam->getAngle() == 0 ){
        unWorm->disableInclinedBeam();
    }
    // calcualamos danio.
    float positionYInAirLast = unWorm->getPositionAir().second;
    float positionYCurrent = unWorm->getBody()->GetWorldCenter().y;
    float fallHeight = positionYInAirLast - positionYCurrent;
    float thresholdFall = gameParameters->getWormMaxResistanceToHeight();
    if (fallHeight > thresholdFall){
        fallHeight -= thresholdFall;
        int damageForFall = (int) std::min(fallHeight, gameParameters->getMaxFallDamage());
        unWorm->takeDamage(damageForFall);
    }
    //actualizamos la posicion en el aire gusano luego de caer.
    b2Vec2 positonWormInAir = worm->getBody()->GetWorldCenter();
    unWorm->savePositionInAir(positonWormInAir.x, positonWormInAir.y);
}

void beamCollidesWithWorm(GameObject* beam, GameObject* worm, GameParameters *gameParameters ){
    wormCollidesWithBeam(worm, beam, gameParameters);
}

void wormCollidesWithWater(GameObject* worm, GameObject* water, GameParameters *gameParameters){
    std::cout << "Worm colisionar con WATER\n";
    worm->destroyBody();
}
void waterCollidesWithWorm(GameObject* water, GameObject* worm, GameParameters *gameParameters){
    wormCollidesWithWater(worm, water, gameParameters);
}
void wormCollidesWithEdege(GameObject* worm, GameObject* edge, GameParameters *gameParameters){
    std::cout << "Worm collisiona con el edge\n";
    Worm* wormSelect = (Worm*) worm;
    wormSelect->aContactWithEdge();
}
void edgeCollidesWithWorm(GameObject* edge, GameObject* worm, GameParameters *gameParameters){
    std::cout << "Edge collisiona con el worm\n";
    wormCollidesWithEdege(worm, edge, gameParameters);
}

void wormCollidesWithWorm(GameObject* worm1, GameObject* worm2, GameParameters *gameParameters){
    Worm* aWorm1 = (Worm*) (worm1);
    Worm* aWorm2 = (Worm*) (worm2);
    aWorm1->assigNextToAWorm();
    aWorm2->assigNextToAWorm();
    if (aWorm1->getBody()->GetLinearVelocity().x > 0 ){
        std::cerr << "Worm 1 choco con velocidad a Worm 2 asi que le reducimos a cero para q no lo empuje\n";
        b2Vec2 velocity = aWorm1->getBody()->GetLinearVelocity();
        velocity.x = 0.0f;
        aWorm1->getBody()->SetLinearVelocity(velocity);
    } else if ( aWorm2->getBody()->GetLinearVelocity().x > 0 ){
        std::cerr << "Worm 2 choco con velocidad a Worm 1 asi que le reducimos a cero para q no lo empuje\n";
        b2Vec2 velocity = aWorm1->getBody()->GetLinearVelocity();
        velocity.x = 0.0f;
        aWorm2->getBody()->SetLinearVelocity(velocity);
    }
}

void projectileBazookaCollidesWithWorm(GameObject* projectileBazooka, GameObject* worm, GameParameters *gameParameters){
    std::cout << "projectileBazookaCollidesWithWorm\n";
    if(projectileBazooka == nullptr or worm == nullptr) return;
    b2Vec2 projectilePosition = projectileBazooka->getBody()->GetWorldCenter();

    ProjectileBazooka* projectilSelect = (ProjectileBazooka*)  projectileBazooka;
    projectilSelect->searchWormAndCollide(projectilePosition);

}

void wormCollidesWithProjectileBazooka(GameObject* worm1, GameObject* projectileBazooka, GameParameters *gameParameters){
    projectileBazookaCollidesWithWorm(projectileBazooka, worm1, gameParameters);
}

void projectileBazookaCollideWithBeam(GameObject* projectileBazooka, GameObject* beam, GameParameters *gameParameters){
    std::cout << "projectileBazookaCollideWithBeam\n";
    b2Vec2 projectilePosition = projectileBazooka->getBody()->GetWorldCenter();
    ProjectileBazooka* projectilSelect = (ProjectileBazooka*)  projectileBazooka;
    projectilSelect->searchWormAndCollide(projectilePosition);
}

void beamCollidesWithProjectileBazooka(GameObject* beam, GameObject* munitionBazooka, GameParameters *gameParameters){
    std::cout << "beamCollidesWithProjectileBazooka\n";
    projectileBazookaCollideWithBeam(munitionBazooka, beam, gameParameters);
}

void beamEndContactWithWorm(GameObject* beam, GameObject* worm, GameParameters *gameParameters){
    std::cout << "beamEndContactWithWorm\n";
    Worm* unWorm = (Worm*) (worm);
    unWorm->unAssingOnABeam();
    Beam* unaBeam = (Beam*) (beam);
    b2Vec2 positonWormInAir = worm->getBody()->GetWorldCenter();
    unWorm->savePositionInAir(positonWormInAir.x, positonWormInAir.y);
}

void wormEndContactWithBeam(GameObject* worm, GameObject* beam, GameParameters *gameParameters){
    beamEndContactWithWorm(beam, worm, gameParameters);
}

void wormEndContactWithWorm(GameObject* worm, GameObject* wormTwo, GameParameters *gameParameters){
    Worm* aWorm1 = (Worm*) (worm);
    Worm* aWorm2 = (Worm*) (wormTwo);
    aWorm1->unAssignNextToAWorm();
    aWorm2->unAssignNextToAWorm();
}

void projectileBazookaCollidesWithEdge(GameObject* projectileBazooka, GameObject* edge, GameParameters *gameParameters){
    std::cout << "projectileBazookaCollidesWithEdge\n";

    ProjectileBazooka* projectilSelect = (ProjectileBazooka*)  projectileBazooka;
    b2Vec2 projectilePosition = projectileBazooka->getBody()->GetWorldCenter();
    projectilSelect->searchWormAndCollide(projectilePosition);
}

void edgeCollidesWithProjectileBazooka(GameObject* edge, GameObject* projectileBazooka, GameParameters *gameParameters){
    std::cout << "edgeCollidesWithProjectileBazooka\n";
    projectileBazookaCollidesWithEdge(projectileBazooka, edge, gameParameters);
}

void projectileBazookaCollidesWithWater(GameObject* projectileBazooka, GameObject* water, GameParameters *gameParameters){
    std::cout << "projectileBazookaCollidesWithWater\n";
    projectileBazooka->destroyBody();
}

void waterCollidesWithProjectileBazooka(GameObject* water, GameObject* projectileBazooka, GameParameters *gameParameters){
    std::cout << "waterCollidesWithProjectileBazooka\n";
    projectileBazookaCollidesWithWater(projectileBazooka, water, gameParameters);
}

void wormCollidesWithProvision(GameObject* worm, GameObject* provision, GameParameters* gameParameters){
    std::cout << "wormCollidesWithProvision\n";
    Provision* provisionSelect = (Provision*) provision;
    Worm* wormSelect = (Worm*) worm;
    provisionSelect->applyEffect(wormSelect);
    provisionSelect->destroyBody();
}

void provisionCollideWithProjectileBazooka(GameObject* provision, GameObject* projectileBazooka, GameParameters *gameParameters){
    std::cout << "provisionCollideWithProjectileBazooka\n";
    projectileBazooka->destroyBody();
}


void projectileBazookaCollidesWithProvision(GameObject* projectileBazooka, GameObject* provision, GameParameters *gameParameters){
    std::cout << "projectileBazookaCollidesWithProvision\n";
    provisionCollideWithProjectileBazooka(provision, projectileBazooka, gameParameters);
}



void provisionCollidesWithWorm(GameObject* provision, GameObject* worm, GameParameters* gameParameters){
    std::cout << "provisionCollidesWithWorm\n";
    wormCollidesWithProvision(worm, provision, gameParameters);
}



void wormEndContactWithEdge(GameObject* worm, GameObject* edge, GameParameters *gameParameters){
    std::cout << "wormEndContactWithEdge\n";
    Worm* wormSelect = (Worm*) worm;
    wormSelect->lessContactWithEdge();
}

void edgeEndContactWithWorm(GameObject* edge, GameObject* worm, GameParameters *gameParameters){
    std::cout << "edgeEndContactWithWorm\n";
    wormEndContactWithEdge(worm, edge, gameParameters);
}


// -- metodos para el airattack missile.  los 10 metodos.

void airAttackMissileCollidesWithEdge(GameObject* airAttackMissile, GameObject* edge, GameParameters *gameParameters){
    std::cout << "airAttackMissileCollidesWithEdge\n";
    //wormEndContactWithEdge(worm, edge, gameParameters);
    AirAttackMissile* missileSelect = (AirAttackMissile*) airAttackMissile;
    b2Vec2 missilePosition = missileSelect->getBody()->GetWorldCenter();
    missileSelect->searchWormAndCollide(missilePosition);
}

void edgeCollidesWithAirAttackMissile(GameObject* edge, GameObject* airAttackMissile, GameParameters *gameParameters){
    std::cout << "edgeCollidesWithAirAttackMissile\n";
    airAttackMissileCollidesWithEdge(airAttackMissile, edge, gameParameters);
}

void airAttackMissileCollidesWithWater(GameObject* airAttackMissile, GameObject* water, GameParameters *gameParameters){
    std::cout << "airAttackMissileCollidesWithWater\n";
    //wormEndContactWithEdge(worm, edge, gameParameters);
    AirAttackMissile* missileSelect = (AirAttackMissile*) airAttackMissile;
    b2Vec2 missilePosition = missileSelect->getBody()->GetWorldCenter();
    missileSelect->searchWormAndCollide(missilePosition);
}

void waterCollidesWithAirAttackMissile(GameObject* water, GameObject* airAttackMissile, GameParameters *gameParameters){
    std::cout << "waterCollidesWithAirAttackMissile\n";
    airAttackMissileCollidesWithWater(airAttackMissile, water, gameParameters);
}



void airAttackMissileCollidesWithProvision(GameObject* airAttackMissile, GameObject* provision, GameParameters *gameParameters){
    std::cout << "airAttackMissileCollidesWithProvision\n";

    AirAttackMissile* missileSelect = (AirAttackMissile*) airAttackMissile;
    b2Vec2 missilePosition = missileSelect->getBody()->GetWorldCenter();
    missileSelect->searchWormAndCollide(missilePosition);
}

void provisionCollideWithAirAttackMissile(GameObject* provision, GameObject* airAttackMissile, GameParameters *gameParameters){
    std::cout << "provisionCollideWithAirAttackMissile\n";
    airAttackMissileCollidesWithProvision(airAttackMissile, provision, gameParameters);
}


void airAttackMissileCollidesWithWorm(GameObject* airAttackMissile, GameObject* worm, GameParameters *gameParameters){
    std::cout << "airAttackMissileCollidesWithWorm\n";
    AirAttackMissile* missileSelect = (AirAttackMissile*) airAttackMissile;
    b2Vec2 missilePosition = missileSelect->getBody()->GetWorldCenter();
    missileSelect->searchWormAndCollide(missilePosition);
}

void wormCollidesWithAirAttackMissile(GameObject* worm, GameObject* airAttackMissile, GameParameters *gameParameters){
    std::cout << "wormCollidesWithAirAttackMissile\n";
    airAttackMissileCollidesWithWorm(airAttackMissile, worm, gameParameters);
}

void airAttackMissileCollideWithBeam(GameObject* airAttackMissile, GameObject* beam, GameParameters *gameParameters){
    std::cout << "airAttackMissileCollideWithBeam\n";
    AirAttackMissile* missileSelect = (AirAttackMissile*) airAttackMissile;
    b2Vec2 missilePosition = missileSelect->getBody()->GetWorldCenter();
    missileSelect->searchWormAndCollide(missilePosition);
}

void beamCollidesWithAirAttackMissile(GameObject* beam, GameObject* airAttackMissile, GameParameters *gameParameters){
    std::cout << "beamCollidesWithAirAttackMissile\n";
    airAttackMissileCollideWithBeam(airAttackMissile, beam, gameParameters);
}

void airAttackMissileCollidesWithAirAttackMissile(GameObject* airAttackMissile, GameObject* airAttackMissil2,  GameParameters *gameParameters){
    std::cout << "airAttackMissileCollidesWithAirAttackMissile\n";

    AirAttackMissile* missileSelect = (AirAttackMissile*) airAttackMissile;
    b2Vec2 missilePosition = missileSelect->getBody()->GetWorldCenter();
    missileSelect->searchWormAndCollide(missilePosition);

    AirAttackMissile* missileSelect2 = (AirAttackMissile*) airAttackMissil2;
    b2Vec2 missilePosition2 = missileSelect2->getBody()->GetWorldCenter();
    missileSelect->searchWormAndCollide(missilePosition2);
}

// ---- Dynamite metodos

void dynamiteCollidesWithEdge(GameObject* dynamite, GameObject* edge, GameParameters *gameParameters){
    std::cout << "dynamiteCollidesWithEdge\n";
}

void edgeCollidesWithDynamite(GameObject* edge, GameObject* dynamite, GameParameters *gameParameters){
    std::cout << "edgeCollidesWithDynamite\n";
    dynamiteCollidesWithEdge(dynamite, edge, gameParameters);
}

void dynamiteCollidesWithWater(GameObject* dynamite, GameObject* water, GameParameters *gameParameters){
    std::cout << "dynamiteCollidesWithWater\n";
}

void waterCollidesWithDynamite(GameObject* water, GameObject* dynamite, GameParameters *gameParameters){
    std::cout << "waterCollidesWithDynamite\n";
    dynamiteCollidesWithWater(dynamite, water, gameParameters);
}

void dynamiteCollidesWithProvision(GameObject* dynamite, GameObject* provision, GameParameters *gameParameters){
    std::cout << "dynamiteCollidesWithProvision\n";
}

void provisionCollideWithDynamite(GameObject* provision, GameObject* dynamite, GameParameters *gameParameters){
    std::cout << "provisionCollideWithDynamite\n";
    dynamiteCollidesWithProvision(dynamite, provision, gameParameters);
}

void dynamiteCollidesWithWorm(GameObject* dynamite, GameObject* worm, GameParameters *gameParameters){
    std::cout << "dynamiteCollidesWithWorm\n";
}

void wormCollidesWithDynamite(GameObject* worm, GameObject* dynamite, GameParameters *gameParameters){
    std::cout << "wormCollidesWithDynamite\n";
    dynamiteCollidesWithWorm(dynamite, worm, gameParameters);
}

void dynamiteCollideWithBeam(GameObject* dynamite, GameObject* beam, GameParameters *gameParameters){
    std::cout << "dynamiteCollideWithBeam\n";
}

void beamCollidesWithDynamite(GameObject* beam, GameObject* dynamite, GameParameters *gameParameters){
    std::cout << "beamCollidesWithDynamite\n";
    dynamiteCollideWithBeam(dynamite, beam, gameParameters);
}

//--------------------- metodos grenade:

void grenadeCollidesWithEdge(GameObject* grenade, GameObject* edge, GameParameters *gameParameters){
    std::cout << "grenadeCollidesWithEdge\n";
    Grenade* grenadeSelect = (Grenade*) grenade;
    grenadeSelect->collide();
}

void edgeCollidesWithGrenade(GameObject* edge, GameObject* grenade, GameParameters *gameParameters){
    std::cout << "edgeCollidesWithGrenade\n";
    grenadeCollidesWithEdge(grenade, edge, gameParameters);
}


void grenadeCollidesWithWater(GameObject* grenade, GameObject* water, GameParameters *gameParameters){
    std::cout << "grenadeCollidesWithWater\n";
    Grenade* grenadeSelect = (Grenade*) grenade;
    grenadeSelect->collide();
}

void waterCollidesWithGrenade(GameObject* water, GameObject* grenade, GameParameters *gameParameters){
    std::cout << "waterCollidesWithGrenade\n";
    grenadeCollidesWithWater(grenade, water, gameParameters);
}

void grenadeCollidesWithProvision(GameObject* grenade, GameObject* provision, GameParameters *gameParameters){
    std::cout << "grenadeCollidesWithProvision\n";
    Grenade* grenadeSelect = (Grenade*) grenade;
    grenadeSelect->collide();
}

void provisionCollideWithGrenade(GameObject* provision, GameObject* grenade, GameParameters *gameParameters){
    std::cout << "provisionCollideWithGrenade\n";
    grenadeCollidesWithProvision(grenade, provision, gameParameters);
}


void grenadeCollidesWithWorm(GameObject* grenade, GameObject* worm, GameParameters *gameParameters){
    std::cout << "grenadeCollidesWithWorm\n";
    Grenade* grenadeSelect = (Grenade*) grenade;
    grenadeSelect->collide();
}

void wormCollidesWithGrenade(GameObject* worm, GameObject* grenade, GameParameters *gameParameters){
    std::cout << "wormCollidesWithGrenade\n";
    grenadeCollidesWithWorm(grenade, worm, gameParameters);
}


void grenadeCollideWithBeam(GameObject* grenade, GameObject* beam, GameParameters *gameParameters){
    std::cout << "grenadeCollideWithBeam\n";
    Grenade* grenadeSelect = (Grenade*) grenade;
    grenadeSelect->collide();
}

void beamCollidesWithGrenade(GameObject* beam, GameObject* grenade, GameParameters *gameParameters){
    std::cout << "beamCollidesWithGrenade\n";
    grenadeCollideWithBeam(grenade, beam, gameParameters);
}




GameContactListener::GameContactListener(b2World *world, GameParameters *gameParameters) {
    world->SetContactListener(this);
    this->gameParameters = (GameParameters *) gameParameters;
    collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_BEAM)] = &wormCollidesWithBeam;
    collisionsMap[std::make_pair(ENTITY_BEAM, ENTITY_WORM)] = &beamCollidesWithWorm;
    collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_WATER)] = &wormCollidesWithWater;
    collisionsMap[std::make_pair(ENTITY_WATER, ENTITY_WORM)] = &waterCollidesWithWorm;
    collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_EDGE)] = &wormCollidesWithEdege;
    collisionsMap[std::make_pair(ENTITY_EDGE, ENTITY_WORM)] = &edgeCollidesWithWorm;
    collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_WORM)] = &wormCollidesWithWorm;


    // ProjectileBazooka Estos 10 obligatorio crear para todo tipo de proyectiles @todo bordes/water/provisiones worm/beam
    collisionsMap[std::make_pair(ENTITY_BAZOOKA_PROJECTILE, ENTITY_EDGE)] = &projectileBazookaCollidesWithEdge;
    collisionsMap[std::make_pair(ENTITY_EDGE, ENTITY_BAZOOKA_PROJECTILE )] = &edgeCollidesWithProjectileBazooka;

    collisionsMap[std::make_pair(ENTITY_BAZOOKA_PROJECTILE, ENTITY_WATER)] = &projectileBazookaCollidesWithWater;
    collisionsMap[std::make_pair(ENTITY_WATER, ENTITY_BAZOOKA_PROJECTILE )] = &waterCollidesWithProjectileBazooka;

    collisionsMap[std::make_pair(ENTITY_PROVISION, ENTITY_BAZOOKA_PROJECTILE)] = &provisionCollideWithProjectileBazooka;
    collisionsMap[std::make_pair(ENTITY_BAZOOKA_PROJECTILE, ENTITY_PROVISION )] = &projectileBazookaCollidesWithProvision;

    collisionsMap[std::make_pair(ENTITY_BAZOOKA_PROJECTILE, ENTITY_WORM )] = &projectileBazookaCollidesWithWorm;
    collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_BAZOOKA_PROJECTILE)] = &wormCollidesWithProjectileBazooka;

    collisionsMap[std::make_pair(ENTITY_BAZOOKA_PROJECTILE, ENTITY_BEAM)] = &projectileBazookaCollideWithBeam;
    collisionsMap[std::make_pair(ENTITY_BEAM, ENTITY_BAZOOKA_PROJECTILE )] = &beamCollidesWithProjectileBazooka;

    // Air Attack Missile.
    collisionsMap[std::make_pair(ENTITY_AIR_ATTACK_MISSILE, ENTITY_EDGE)] = &airAttackMissileCollidesWithEdge;
    collisionsMap[std::make_pair(ENTITY_EDGE, ENTITY_AIR_ATTACK_MISSILE)] = &edgeCollidesWithAirAttackMissile;

    collisionsMap[std::make_pair(ENTITY_AIR_ATTACK_MISSILE, ENTITY_WATER)] = &airAttackMissileCollidesWithWater;
    collisionsMap[std::make_pair(ENTITY_WATER, ENTITY_AIR_ATTACK_MISSILE )] = &waterCollidesWithAirAttackMissile;

    collisionsMap[std::make_pair(ENTITY_AIR_ATTACK_MISSILE, ENTITY_AIR_ATTACK_MISSILE)] = &airAttackMissileCollidesWithAirAttackMissile;

    collisionsMap[std::make_pair(ENTITY_PROVISION, ENTITY_AIR_ATTACK_MISSILE)] = &provisionCollideWithAirAttackMissile;
    collisionsMap[std::make_pair(ENTITY_AIR_ATTACK_MISSILE, ENTITY_PROVISION )] = &airAttackMissileCollidesWithProvision;

    collisionsMap[std::make_pair(ENTITY_AIR_ATTACK_MISSILE, ENTITY_WORM )] = &airAttackMissileCollidesWithWorm;
    collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_AIR_ATTACK_MISSILE)] = &wormCollidesWithAirAttackMissile;

    collisionsMap[std::make_pair(ENTITY_AIR_ATTACK_MISSILE, ENTITY_BEAM)] = &airAttackMissileCollideWithBeam;
    collisionsMap[std::make_pair(ENTITY_BEAM, ENTITY_AIR_ATTACK_MISSILE )] = &beamCollidesWithAirAttackMissile;

    // Dynamite collisions
    collisionsMap[std::make_pair(ENTITY_DYNAMITE, ENTITY_EDGE)] = &dynamiteCollidesWithEdge;
    collisionsMap[std::make_pair(ENTITY_EDGE, ENTITY_DYNAMITE)] = &edgeCollidesWithDynamite;

    collisionsMap[std::make_pair(ENTITY_DYNAMITE, ENTITY_WATER)] = &dynamiteCollidesWithWater;
    collisionsMap[std::make_pair(ENTITY_WATER, ENTITY_DYNAMITE )] = &waterCollidesWithDynamite;

    collisionsMap[std::make_pair(ENTITY_DYNAMITE, ENTITY_PROVISION )] = &dynamiteCollidesWithProvision;
    collisionsMap[std::make_pair(ENTITY_PROVISION, ENTITY_DYNAMITE)] = &provisionCollideWithDynamite;

    collisionsMap[std::make_pair(ENTITY_DYNAMITE, ENTITY_WORM )] = &dynamiteCollidesWithWorm;
    collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_DYNAMITE)] = &wormCollidesWithDynamite;

    collisionsMap[std::make_pair(ENTITY_DYNAMITE, ENTITY_BEAM)] = &dynamiteCollideWithBeam;
    collisionsMap[std::make_pair(ENTITY_BEAM, ENTITY_DYNAMITE )] = &beamCollidesWithDynamite;

    // Granada collisions creo que son genericos para cualquier tipo de granada.

    collisionsMap[std::make_pair(ENTITY_GRENADE, ENTITY_EDGE)] = &grenadeCollidesWithEdge;
    collisionsMap[std::make_pair(ENTITY_EDGE, ENTITY_GRENADE)] = &edgeCollidesWithGrenade;

    collisionsMap[std::make_pair(ENTITY_GRENADE, ENTITY_WATER)] = &grenadeCollidesWithWater;
    collisionsMap[std::make_pair(ENTITY_WATER, ENTITY_GRENADE )] = &waterCollidesWithGrenade;

    collisionsMap[std::make_pair(ENTITY_GRENADE, ENTITY_PROVISION )] = &grenadeCollidesWithProvision;
    collisionsMap[std::make_pair(ENTITY_PROVISION, ENTITY_GRENADE)] = &provisionCollideWithGrenade;

    collisionsMap[std::make_pair(ENTITY_GRENADE, ENTITY_WORM )] = &grenadeCollidesWithWorm;
    collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_GRENADE)] = &wormCollidesWithGrenade;

    collisionsMap[std::make_pair(ENTITY_GRENADE, ENTITY_BEAM)] = &grenadeCollideWithBeam;
    collisionsMap[std::make_pair(ENTITY_BEAM, ENTITY_GRENADE )] = &beamCollidesWithGrenade;



    //Colisiones con las provisiones Worms:
    collisionsMap[std::make_pair(ENTITY_PROVISION, ENTITY_WORM)] = &provisionCollidesWithWorm;
    collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_PROVISION )] = &wormCollidesWithProvision;

    endContactMap[std::make_pair(ENTITY_BEAM, ENTITY_WORM) ] = &beamEndContactWithWorm;
    endContactMap[std::make_pair(ENTITY_WORM, ENTITY_BEAM) ] = &wormEndContactWithBeam;
    endContactMap[std::make_pair(ENTITY_WORM, ENTITY_WORM) ] = &wormEndContactWithWorm;

    endContactMap[std::make_pair(ENTITY_WORM, ENTITY_EDGE) ] = &wormEndContactWithEdge;
    endContactMap[std::make_pair(ENTITY_EDGE, ENTITY_WORM) ] = &edgeEndContactWithWorm;
}


void GameContactListener::BeginContact(b2Contact *contact) {
    GameObject* gameObject = (GameObject*) contact->GetFixtureA()->GetBody()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
    GameObject* otroGameObject = (GameObject*) contact->GetFixtureB()->GetBody()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
    if(gameObject == nullptr || otroGameObject == nullptr) return;
    auto iteratorElement =  collisionsMap.find( std::make_pair(gameObject->getEntityType(), otroGameObject->getEntityType())); // nos retorna un iterador
    if(iteratorElement != collisionsMap.end() ){
        auto hitFunction = iteratorElement->second;
        if(hitFunction){
            hitFunction(gameObject, otroGameObject, gameParameters);
        }
    }
}

void GameContactListener::EndContact(b2Contact *contact) {
    GameObject* gameObject = (GameObject*) contact->GetFixtureA()->GetBody()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
    GameObject* otroGameObject = (GameObject*) contact->GetFixtureB()->GetBody()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
    if(gameObject == nullptr || otroGameObject == nullptr) return;
    auto iteratorElement =  endContactMap.find( std::make_pair(gameObject->getEntityType(), otroGameObject->getEntityType())); // nos retorna un iterador
    if(iteratorElement != endContactMap.end() ){
        auto hitFunction = iteratorElement->second;
        if(hitFunction){
            hitFunction(gameObject, otroGameObject, gameParameters);
        }
    }
}


