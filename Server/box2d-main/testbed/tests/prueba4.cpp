#include "test.h"
#include "box2d/box2d.h"

#include <cmath>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <yaml-cpp/yaml.h>
#include <cstdlib>
#include <linux/limits.h>
#include "imgui/imgui.h"

#include <GL/gl.h> // Incluir la biblioteca principal de OpenGL
//#include <GL/glu.h> // Incluir la biblioteca de utilidades de GLUT
#include <GLFW/glfw3.h> // Opcional: Incluir la biblioteca GLFW si estás utilizando GLFW para gestionar la ventana
#define DEGRATORADIANS (b2_pi/180.0f)
#define RADIANSTODEGREE (180/b2_pi)
const float SPEED_WORM = 6.5f;

enum Entity{
    ENTITY_BEAM = 1,
    ENTITY_WATER = 2,
    ENTITY_EDGE = 3,
    ENTITY_WORM = 4,
    ENTITY_MUNITION_BAZOOKA = 6,
    ENTITY_AIR_ATTACK_MISSILE = 7,
};
#define GRAVITY_GAME 10.0f  // AGREGAR

class GameObject {
protected:
    Entity typeEntity;
    b2Body* body;
    bool isDestroyed;

public:
    explicit GameObject(const Entity &aTpeEntity): typeEntity(aTpeEntity), body(nullptr) , isDestroyed(false) {
    }

    Entity getEntityType() const {
        return typeEntity;
    }

    b2Body* getBody(){
        return body;
    }

    void destroyBody(){
        isDestroyed = true;
    }

    bool isDestroyedBody() {
        return this->isDestroyed;
    }

    virtual ~GameObject() = default;
};

enum TypeBeam {
    SHORT_BEAM = 3 , LONG_BEAM = 6, WATER_BEAM = 1500
};


class Beam : public GameObject {
private:
    TypeBeam typeBeam;
    float xCenter;
    float yCenter;
    float length;
    float height;
    float angle;
    b2World* aWorld;
public:
    Beam() : GameObject(ENTITY_BEAM){
    }

    Beam(const TypeBeam &aTypeBeam, const float &aXcenter, const float &aYCenter, const float &aLength, const float &aHeight, const float &aAngle)
            : GameObject(ENTITY_BEAM) , typeBeam(aTypeBeam), xCenter(aXcenter), yCenter(aYCenter), length(aLength), height(aHeight), angle(aAngle) {
    }
    float getAngle(){
        return angle;
    }

    void addToTheWorld(b2World *world) {
        b2BodyDef defBeam;
        defBeam.type = b2_staticBody;
        defBeam.position.Set(xCenter, yCenter);
        defBeam.userData.pointer = (uintptr_t) this;
        this->body = world->CreateBody(&defBeam);

        float angleRandians = this->angle/180.0f * b2_pi;
        b2PolygonShape shapeBeam;
        shapeBeam.SetAsBox(length/2.0f, height/2.0f, b2Vec2(0.0f, 0.0f), angleRandians );

        b2FixtureDef defFixtureBeam;
        defFixtureBeam.shape = &shapeBeam;
        float beamFriction = 5.0f; // antes era 1.5f
        if(angle > 45.0f && angle <= 170.0f ){
            beamFriction = 0.0f;
        }
        defFixtureBeam.friction = beamFriction;
        this->body->CreateFixture(&defFixtureBeam);
        this->aWorld = world;
    }

    b2World* getWorld(){
        return this->aWorld;
    }
};

class YamlParser{

public:
    YamlParser(){}

    static void loadDataStage(const std::string &aStageName, float &height, float &length, std::vector<Beam> &aBeams,
                              std::map<size_t, std::pair<float, float>> &idPosWorms) {
        char startPathC[PATH_MAX];
        realpath("../../", startPathC);
        std::string startPath(startPathC);
        std::string stgNamNoSpace = aStageName;
        stgNamNoSpace.erase(std::remove(stgNamNoSpace.begin(), stgNamNoSpace.end(), ' '), stgNamNoSpace.end());
        std::string fullPath(startPath + "/Stages/"+ stgNamNoSpace + ".yaml");
        YAML::Node node = YAML::LoadFile(fullPath);
        std::map<size_t, std::pair<float, float>> idPosInitialWorms;
        YAML::Node wormsNode = node["worms"];
        size_t idWorm = 0;
        for (const auto& posWorm : node["worms"]) {
            float posInitialX = posWorm["positionX"].as<float>();
            float posInitialY = posWorm["positionY"].as<float>();
            idPosInitialWorms[idWorm] = std::make_pair(posInitialX, posInitialY);
            idWorm++;
        }
        height = node["height"].as<float>();
        length = node["width"].as<float>();
        aBeams = getBeams(node["beams"]);
        idPosWorms = idPosInitialWorms;
    }

    static std::vector<Beam> getBeams(const YAML::Node &beamsNode) {
        std::vector<Beam> beams;
        for (YAML::const_iterator it = beamsNode.begin(); it != beamsNode.end(); ++it) {
            const YAML::Node& beamNode = *it;
            float length = beamNode["length"].as<float>();
            float angle = beamNode["angle"].as<float>();
            float xCenter = beamNode["x"].as<float>();
            float yCenter = beamNode["y"].as<float>();
            float height = 0.4;
            TypeBeam typeBeam;
            if(length == 3.0){
                typeBeam = TypeBeam::SHORT_BEAM;
            } else if ( length == 6.0){
                typeBeam = TypeBeam::LONG_BEAM;
            } else if (length == 1500.0){
                typeBeam = TypeBeam::WATER_BEAM;
            }
            Beam beam(typeBeam, xCenter, yCenter, length, height, angle);
            beams.push_back(beam);
        }
        return beams;
    }


    static std::vector<std::string> getScenarioNames() {
        std::vector<std::string> scenarioNames;

        char startPathC[PATH_MAX];
        realpath("../../", startPathC);
        std::string startPath(startPathC);
        std::string fullPath(startPath +"/Stages/"+ "StageNames" + ".yaml");
        try{
            YAML::Node config = YAML::LoadFile(fullPath);
            for (const auto& scenario : config["namesScenarios"]) {
                auto name = scenario["name"].as<std::string>();
                scenarioNames.push_back(name);
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        return scenarioNames;
    }
};

class Edges : public GameObject {
private:

public:
    Edges(b2World *world, const float &height, const float &width) : GameObject(ENTITY_EDGE) {
        // deberian ser 4 bodys y cada uno con su fixture probarlo y ver q onda porq q aca un body tiene 4 fixture
        // esta ok pero falta ver q tanta complejidad aggrega con las colisiones.
        b2BodyDef bd;
        bd.userData.pointer = (uintptr_t) this;
        body = world->CreateBody(&bd);

        b2EdgeShape shape;
        shape.SetTwoSided(b2Vec2(0.0f, height), b2Vec2(width, height));
        body->CreateFixture(&shape, 0.0f);

        shape.SetTwoSided(b2Vec2(0.0f, 0.0f), b2Vec2(0.0f, height));
        body->CreateFixture(&shape, 0.0f);

        shape.SetTwoSided(b2Vec2(width, 0.0f), b2Vec2(width, height));
        body->CreateFixture(&shape, 0.0f);
    }

    Edges() : GameObject(ENTITY_EDGE) {
    }
};

class Water : public GameObject{
private:

public:
    Water() : GameObject(ENTITY_WATER) {
    }

    Water(b2World *world, const float &height, const float &width) : GameObject(ENTITY_WATER)  {
        b2BodyDef bd;
        bd.userData.pointer = (uintptr_t) this;
        body = world->CreateBody(&bd);

        b2EdgeShape shape;
        shape.SetTwoSided(b2Vec2(0.0f, 0.0f), b2Vec2(width, 0.0f));
        body->CreateFixture(&shape, 0.0f);
    }
};


class Stage{
private:
    std::string name;
    float height;
    float length;
    std::vector<Beam> beams;
    std::map<size_t, std::pair<float, float>> idsAndPositionsWorms;
    std::unique_ptr<Edges> edges;
    std::unique_ptr<Water> water;
public:
    Stage(){
    }

    Stage(const std::string &name) {
        YamlParser::loadDataStage(name, height, length, beams, idsAndPositionsWorms);
    }


    std::map<size_t, std::pair<float, float>> getIdsAndPositionsWorms() const {
        return this->idsAndPositionsWorms;
    }

    void addToTheWorld(b2World *world) {
        this->edges = std::unique_ptr<Edges>{new Edges(world, height, length)};
        this->water = std::unique_ptr<Water>{new Water(world, height, length)};
        for(auto& aBeam : beams){
            aBeam.addToTheWorld(world);
        }
    }
};

class AirAttackMissile : public GameObject {
    float mainDamage = 40.0f;
    float maxRadio = 2.0f;

public:
    AirAttackMissile() : GameObject(ENTITY_AIR_ATTACK_MISSILE) {}

    void addToTheWorld(b2World* aWorld, b2Vec2 startPosition){
        b2BodyDef airAttackMissileDef;
        airAttackMissileDef.type = b2_dynamicBody;
        airAttackMissileDef.fixedRotation = true;
        airAttackMissileDef.position.Set(startPosition.x, startPosition.y );
        airAttackMissileDef.userData.pointer = (uintptr_t) this;
        this->body = aWorld->CreateBody(&airAttackMissileDef);
        b2CircleShape airAttackMissileForm;
        airAttackMissileForm.m_p.Set(0.0f, 0.0f); // offset de la posicion inicial va en (0,1) e 1 por q el radio de 1m empuja en 1 al origen de la circuferencia..
        airAttackMissileForm.m_radius = 0.1f;

        b2FixtureDef defFixAirAttackMis;
        defFixAirAttackMis.shape = &airAttackMissileForm;
        defFixAirAttackMis.density = 1.0f; // ver el tema del aire luego.
        this->body->CreateFixture(&defFixAirAttackMis);
    }

    b2AABB getAreaForSearch(const b2Vec2& positionMissile) const {
        b2AABB searchArea;
        searchArea.lowerBound = positionMissile - b2Vec2(2.0f, 2.0f);
        searchArea.upperBound = positionMissile + b2Vec2(2.0f, 2.0f);
        return searchArea;
    }

    float getDamageForWorm(const float &wormDistance) const {
        float damageForWorm = mainDamage * std::max(0.0f, 1.0f - sqrt(wormDistance) / maxRadio);
        return damageForWorm;
    }

};

class AirAttackDetonator {
    std::vector<std::unique_ptr<AirAttackMissile>> missiles;
    std::vector<float> offsets;

public:
    AirAttackDetonator() : offsets({-0.5f,0.5f,-1.5f,1.5f,-2.5f,2.5f}){}

    void detonate(b2World *world, float posXAttack, float posYAttack) {
        for (auto & offset : offsets) {
            std::unique_ptr<AirAttackMissile> missile{new AirAttackMissile};
            missile->addToTheWorld(world, b2Vec2(posXAttack + offset, posYAttack));
            missiles.push_back(std::move(missile));
        }
    }

    std::vector<std::unique_ptr<AirAttackMissile>>* getAirAttackMissiles(){
        return &missiles;
    }

};

class Worm : public GameObject {
    size_t idWorm;
    float  hp;
    float positionInitialX;
    float positionInitialY;
    b2World* world;
    AirAttackDetonator detonator;

public:
    Worm(const size_t &idWorm, const float &posIniX, const float &posIniY) : GameObject(ENTITY_WORM), positionInitialX(posIniX),
        positionInitialY(posIniY) {
        this->idWorm = idWorm;
        hp = 100.0f;
    }

    void assignBonusLife() {
        hp += 25.0f;
    }

    void addToTheWorld(b2World *world) {
        b2BodyDef wormDef;
        wormDef.type = b2_dynamicBody;
        wormDef.fixedRotation = true;
        wormDef.position.Set(positionInitialX, positionInitialY);
        wormDef.userData.pointer = (uintptr_t) this;
        this->body = world->CreateBody(&wormDef);

        //  creamos la forma del gusano.
        b2CircleShape wormShape;
        wormShape.m_p.Set(0.0f, 1.0f); // offset de la posicion inicial va en (0,1) e 1 por q el radio de 1m empuja en 1 al origen de la circuferencia..
        wormShape.m_radius = 0.2f;

        b2FixtureDef defFixtureWorm;
        defFixtureWorm.shape = &wormShape;
        defFixtureWorm.friction = 1.0f;
        defFixtureWorm.density = 1.0f;
        this->body->CreateFixture(&defFixtureWorm);
        this->world = world;
    }

    float getHp(){
        return hp;
    }

    void takeDamage(const float &aDamage){
        std::cout << "gusano recibe daño\n";
        std::cout << "antes: " << hp << "\n";
        this->hp -=aDamage;
        if(hp <= 0.0f){
            this->destroyBody();
        }
        std::cout << "despues: " << hp << "\n";

    }

    void airAttack(float posXAttack, float posYAttack){
        detonator.detonate(world,posXAttack,posYAttack);
    }

    b2World* getWorld(){
        return world;
    }

    std::vector<std::unique_ptr<AirAttackMissile>>* getAirAttackMissiles(){
        return this->detonator.getAirAttackMissiles();
    }

};

class SaveWormsInAreaQueryTest : public b2QueryCallback{
private:
    std::map<GameObject*, float> wormAndDistanceSquar;
    b2Vec2 munitionPosition;
public:
    explicit SaveWormsInAreaQueryTest(const b2Vec2 &munitionPosition) : munitionPosition(munitionPosition){
    }

    bool ReportFixture(b2Fixture* fixture) override {
        std::cout << "En SaveWormsInAreaQuery entre a reportFixture tengo que reportar que encontre un objeto en el intervalo del cuadrado\n";
        GameObject* obj = (GameObject*) (fixture->GetBody()->GetUserData().pointer);
        if (obj && obj->getEntityType() == ENTITY_WORM) {
            std::cout << "Ese objeto es un worm entro al report fiture de query\n";
            float distanceSquared = b2DistanceSquared(munitionPosition, fixture->GetBody()->GetWorldCenter()); // sacamos la distancia al cuadrado
            // es decir distancia = c.c -> c = (a-b) = (x1-x2; y1-y2) -> c.c = (x1-x2)² + (y1-y2)²
            std::cout << "obj" << obj << "\n";
            wormAndDistanceSquar[obj] = distanceSquared;
        }
        return true; // Continuar con la búsqueda
    }
    std::map<GameObject*, float>  getWormsAndDistSquar(){
        return this->wormAndDistanceSquar;
    };
};

void airAttackMissileCollideWithBeam(GameObject* missile, GameObject* beam){
    std::cout << "airAttackMissileCollideWithBeam\n";
    b2Vec2 missilePosition = missile->getBody()->GetWorldCenter();

    AirAttackMissile* missileSelect = (AirAttackMissile*)  missile;

    SaveWormsInAreaQueryTest savWormsinArea(missilePosition);     // Función de devolución de llamada para la búsqueda

    Beam * beamSelected = (Beam*) beam;
    beamSelected->getWorld()->QueryAABB(&savWormsinArea, missileSelect->getAreaForSearch(missilePosition));
    for(auto& aElement : savWormsinArea.getWormsAndDistSquar() ){
        Worm* aWormToTakeDamage = (Worm*)(aElement.first);
        float damageForWorm = missileSelect->getDamageForWorm(aElement.second);
        aWormToTakeDamage->takeDamage(damageForWorm);
    }
    missileSelect->destroyBody();
}

void beamCollidesWithAirAttackMissile(GameObject* beam, GameObject* missile){
    std::cout << "beamCollidesWithAirAttackMissile\n";
    airAttackMissileCollideWithBeam(missile, beam);
}


void airAttackMissileCollidesWithWorm(GameObject* missile, GameObject* worm){
    std::cout << "munitionBazookaCollidesWithWorm\n";
    if(missile == nullptr or worm == nullptr) return;
    b2Vec2 missilePosition = missile->getBody()->GetWorldCenter();

    AirAttackMissile* missileSelect = (AirAttackMissile*)  missile;
    Worm* wormSelect = (Worm*) (worm);

    SaveWormsInAreaQueryTest savWormsinArea(missilePosition);     // Función de devolución de llamada para la búsqueda

    wormSelect->getWorld()->QueryAABB(&savWormsinArea, missileSelect->getAreaForSearch(missilePosition));
    for(auto& aElement : savWormsinArea.getWormsAndDistSquar() ){
        Worm* aWormToTakeDamage = (Worm*)(aElement.first);
        if (aWormToTakeDamage != wormSelect) {
            float damageForWorm = missileSelect->getDamageForWorm(aElement.second);
            aWormToTakeDamage->takeDamage(damageForWorm);
        }
    }

    missile->destroyBody();
    wormSelect->takeDamage(40.0f);
}

void wormCollidesWithAirAttackMissile(GameObject* worm1, GameObject* missile){
    std::cout << "wormCollidesWithMunitionBazooka\n";
    airAttackMissileCollidesWithWorm(missile, worm1);
}

class MyContactListener : public b2ContactListener {

private:
    typedef void (*HitFunctionPtr)(GameObject *, GameObject *);

    std::map<std::pair<Entity, Entity>, HitFunctionPtr> collisionsMap;

public:
    MyContactListener(b2World *world) {
        world->SetContactListener(this);
        collisionsMap[std::make_pair(ENTITY_AIR_ATTACK_MISSILE, ENTITY_BEAM)] = &airAttackMissileCollideWithBeam;
        collisionsMap[std::make_pair(ENTITY_BEAM, ENTITY_AIR_ATTACK_MISSILE )] = &beamCollidesWithAirAttackMissile;
        collisionsMap[std::make_pair(ENTITY_AIR_ATTACK_MISSILE, ENTITY_WORM)] = &airAttackMissileCollidesWithWorm;
        collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_AIR_ATTACK_MISSILE )] = &wormCollidesWithAirAttackMissile;
    }

    void BeginContact(b2Contact* contact) override{
        GameObject* gameObject = (GameObject*) contact->GetFixtureA()->GetBody()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
        GameObject* otroGameObject = (GameObject*) contact->GetFixtureB()->GetBody()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
        if(gameObject == nullptr || otroGameObject == nullptr) return;
        auto iteratorElement =  collisionsMap.find( std::make_pair(gameObject->getEntityType(), otroGameObject->getEntityType())); // nos retorna un iterador
        std::cout << "Collision detected between " << gameObject->getEntityType() << " and " << otroGameObject->getEntityType() << "\n";
        if(iteratorElement != collisionsMap.end() ){
            auto hitFunction = iteratorElement->second;
            if(hitFunction){
                hitFunction(gameObject, otroGameObject);
            }
        }
    }
};


class Prueba4 : public Test{
public:
    std::unique_ptr<Stage>  stage;
    std::vector<std::unique_ptr<Worm>> vecWorms;
    std::unique_ptr<MyContactListener> myContactListener;

    Prueba4() {
         // Todo variable q esta aca dentro y queramos que perdure debemos usar el heap .
        stage = std::unique_ptr<Stage>{new Stage("Jaula Maldita")};
        stage->addToTheWorld(m_world);
        //    std::map<size_t, std::pair<float, float>> idsAndPositionsWorms;
        for(auto& aElement : stage->getIdsAndPositionsWorms()){
            vecWorms.push_back(std::unique_ptr<Worm>{ new Worm(aElement.first, aElement.second.first, aElement.second.second) });
            vecWorms.back()->addToTheWorld(m_world);
        }
        myContactListener = std::unique_ptr<MyContactListener>{new MyContactListener(m_world)};
    }

    void Keyboard(int key) override{
        if (key == GLFW_KEY_9){
            vecWorms[0]->airAttack(7.5f,18.0f); // 18 es la altura del escenario
        }
    }

    void update() {
        std::vector<std::unique_ptr<AirAttackMissile>>* airAttackMissiles = vecWorms[0]->getAirAttackMissiles();
        auto itMissiles = airAttackMissiles->begin();
        while (itMissiles != airAttackMissiles->end()) {
            if ((*itMissiles)->isDestroyedBody()) {
                m_world->DestroyBody((*itMissiles)->getBody()); // Destruimos el cuerpo
                itMissiles = airAttackMissiles->erase(itMissiles);       // Eliminar el elemento del vector usando el iterador
            } else {
                ++itMissiles;                 // Avanzar al siguiente elemento si no se elimina
            }
        }
    }

    void Step(Settings &settings) override {
        Test::Step(settings);
        g_debugDraw.DrawString(5, m_textLine, "Keys: (d) dynamic, (s) static, (k) kinematic");
        m_textLine += m_textIncrement;
        if(vecWorms[0] != nullptr){
            b2Vec2 posicion = vecWorms[0]->getBody()->GetWorldCenter();
            b2Vec2 posicion2 = vecWorms[1]->getBody()->GetWorldCenter();
            std::string dateGusano1 = "X: " + std::to_string(posicion.x)  + " Y: " + std::to_string(posicion.y) +" HP: " +  std::to_string(vecWorms[0]->getHp()) + " \n";
            std::string dateGusano2 = "\nX: " + std::to_string(posicion2.x)  + " Y: " + std::to_string(posicion2.y) +" HP: " +  std::to_string(vecWorms[1]->getHp()) + " \n";
            std::string textFinal =  "\n" + dateGusano1 + "\n" + dateGusano2 + "\n";
            g_debugDraw.DrawString(5, m_textLine, textFinal.data());
            update();
        }
    }

    static Test* Create(){
        return new Prueba4;
    }

    ~Prueba4() override = default;
};

static int testIndex = RegisterTest("Examples", "Prueba 4", Prueba4::Create);
