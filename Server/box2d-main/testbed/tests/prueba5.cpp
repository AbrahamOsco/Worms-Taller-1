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
#include "../../../../Common/DTO/WeaponDTO.h"
#include "../../../GameParameters/GameParameters.h"

#include <GL/gl.h> // Incluir la biblioteca principal de OpenGL
//#include <GL/glu.h> // Incluir la biblioteca de utilidades de GLUT
#include <GLFW/glfw3.h> // Opcional: Incluir la biblioteca GLFW si estás utilizando GLFW para gestionar la ventana
#define DEGRATORADIANS (b2_pi/180.0f)
#define RADIANSTODEGREE (180/b2_pi)
const float SPEED_WORM = 6.5f;
#include <chrono>

#define FR 20

enum Entity{
    ENTITY_BEAM = 1,
    ENTITY_WATER = 2,
    ENTITY_EDGE = 3,
    ENTITY_WORM = 4,
    ENTITY_MUNITION_BAZOOKA = 6,
    ENTITY_AIR_ATTACK_MISSILE = 7,
    ENTITY_DYNAMITE = 8,
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

class Dynamite : public GameObject {
    float mainDamage = 50.0f;
    float maxRadio = 4.0f;
    float maxImpulseMagnitude = 2.0f;

    std::chrono::steady_clock::time_point startTime, time;
    std::chrono::duration<float> waitTime;
    bool exploded;

public:
    explicit Dynamite(const int &wait) : GameObject(ENTITY_DYNAMITE), waitTime(wait),
                                         exploded(false) {}

    void addToTheWorld(b2World* aWorld, b2Vec2 position) {
        startTime = std::chrono::steady_clock::now();
        b2BodyDef dynamiteDef;
        dynamiteDef.type = b2_dynamicBody;
        dynamiteDef.fixedRotation = true;
        dynamiteDef.position.Set(position.x, position.y );
        dynamiteDef.userData.pointer = (uintptr_t) this;
        this->body = aWorld->CreateBody(&dynamiteDef);
        b2CircleShape dynamiteForm;
        dynamiteForm.m_p.Set(0.0f, 0.0f); // offset de la posicion inicial va en (0,1) e 1 por q el radio de 1m empuja en 1 al origen de la circuferencia..
        dynamiteForm.m_radius = 0.1f;

        b2FixtureDef defFixDynamite;
        defFixDynamite.shape = &dynamiteForm;
        defFixDynamite.friction = 20.0f;
        defFixDynamite.density = 1.0f; // ver el tema del aire luego.
        this->body->CreateFixture(&defFixDynamite);
    }

    void passTime() {
        time = std::chrono::steady_clock::now();

        if (time - startTime >= waitTime && !exploded)
            explode();
    }

    void explode() {
        exploded = true;
        body->ApplyLinearImpulse(b2Vec2(0.0f,0.03f),body->GetWorldCenter(),true); // para que se despegue y vuelva a chocar con la viga.
    }

    bool hasExploded() const {
        return exploded;
    }

    b2AABB getAreaForSearch(const b2Vec2& positionDynamite) const {
        b2AABB searchArea;
        searchArea.lowerBound = positionDynamite - b2Vec2(maxRadio, maxRadio);
        searchArea.upperBound = positionDynamite+ b2Vec2(maxRadio, maxRadio);
        return searchArea;
    }

    b2Vec2 getImpulseForWorm(const b2Vec2 &positionWorm, const b2Vec2 &positionDynamite, float distanceWormToDynamite) {
        b2Vec2 impulseDirection = positionWorm - positionDynamite;
        impulseDirection.Normalize();
        std::cout << "distanceWormToMunition :" << distanceWormToDynamite << "\n";
        float impulseMagnitude = maxImpulseMagnitude * std::max(0.0f, 1.0f - sqrt(distanceWormToDynamite) / maxRadio );
        std::cout << "impulseMagnitude : " << impulseMagnitude;
        std::cout << " impulseDirection.x: " << impulseDirection.x << "impulseDirection.y" << impulseDirection.y << "\n ";
        b2Vec2 impulseWorm = impulseMagnitude * impulseDirection;
        impulseWorm.y = abs(impulseWorm.x) * 0.7;
        if(impulseDirection.x == 0){ // Si la normal en x es cero hizo un tiro a -90º sale volando para arriba.
            impulseWorm.y = maxImpulseMagnitude;
        }
        std::cout << "impulseWorm.x" << impulseWorm.x << "impulseWorm.y" << impulseWorm.y << "\n";
        return impulseWorm;
    }

    float getDamageForWorm(const float &wormDistance) const {
        float damageForWorm = mainDamage * std::max(0.0f, 1.0f - sqrt(wormDistance) / maxRadio);
        return damageForWorm;
    }

};

class DynamiteHolder {
    std::vector<std::unique_ptr<Dynamite>> dynamites;

public:
    DynamiteHolder(){

    }

     void placeDynamite(const int &waitTime, const b2Vec2 &positionDynamite, b2World *world) {
        std::unique_ptr<Dynamite> dynamite{new Dynamite(waitTime)};
        dynamite->addToTheWorld(world, positionDynamite);
        dynamites.push_back(std::move(dynamite));
    }

    std::vector<std::unique_ptr<Dynamite>>* getDynamites(){
        return &dynamites;
    }

};

enum Direction{
    RIGHT = 1, LEFT = 2
};

class Worm : public GameObject {
    size_t idWorm;
    Direction directionLook;
    float  hp;
    float dragSpeed;
    float positionInitialX;
    float positionInitialY;
    b2World* world;
    DynamiteHolder dynamiteHolder;
    int waitTime;

public:
    Worm(const size_t &idWorm, const float &posIniX, const float &posIniY) : GameObject(ENTITY_WORM), positionInitialX(posIniX),
                                                                             positionInitialY(posIniY){
        this->idWorm = idWorm;
        directionLook = Direction::RIGHT;
        hp = 100.0f;
        dragSpeed = 0.2f;
        waitTime = 5;
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

    void walk(Direction aDirection) {
        if( not isInContactWithAnotherWorm() and  body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f) ){
            directionLook = aDirection;
            float acceleration = getBody()->GetFixtureList()[0].GetFriction() * 10.0f; // aceleracion es la froz = u.N , las masas se cancelan queda mu * g.
            float speed = sqrt(2.0f * acceleration * dragSpeed); // la velocidad la sacamos como 2 * aceleracion * distancia.
            float impulseX = body->GetMass() * speed ;
            float impulseY = 0;
            if (directionLook == Direction::LEFT ) {
                impulseX *=-1;
            }
            std::cout << "Impulse x: " << impulseX << " Impulse y:  " << impulseY << "\n";
            b2Vec2 impulseSpeed(impulseX, impulseY); //  por la gravedad
            body->ApplyLinearImpulse(impulseSpeed, body->GetWorldCenter(), true);
        }
    }

    bool isInContactWithAnotherWorm(){
        for(b2ContactEdge* ce = body->GetContactList(); ce; ce = ce->next){ // iterar sobre todos los contactos de un cuerpo:
            GameObject* aGameObj = (GameObject*) ce->contact->GetFixtureA()->GetBody()->GetUserData().pointer;
            GameObject* aOtherGamObj = (GameObject*) ce->contact->GetFixtureB()->GetBody()->GetUserData().pointer;
            if ( aGameObj->getEntityType() == ENTITY_WORM and aOtherGamObj->getEntityType() == ENTITY_WORM ){
                return true;
            }
        }
        return false;
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

    void placeDynamite(){
        float posY = body->GetWorldCenter().y;
        float posX = body->GetWorldCenter().x;
        if (directionLook == LEFT)
            posX -= 0.5f;
        else
            posX += 0.5f;
        dynamiteHolder.placeDynamite(waitTime, b2Vec2(posX, posY), world);
        waitTime = 5; // back to default
    }

    b2World* getWorld(){
        return world;
    }

    std::vector<std::unique_ptr<Dynamite>>* getDynamites(){
        return this->dynamiteHolder.getDynamites();
    }

    void setWaitTime(int time) {
        waitTime = time;
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

void dynamiteCollideWithBeam(GameObject* dynamite, GameObject* beam){
    std::cout << "dynamiteCollideWithBeam\n";
    b2Vec2 dynamitePosition = dynamite->getBody()->GetWorldCenter();

    Dynamite* dynamiteSelect = (Dynamite*)  dynamite;

    if (dynamiteSelect->hasExploded()) {
        std::cout << "boom\n";
        SaveWormsInAreaQueryTest savWormsinArea(
                dynamitePosition);     // Función de devolución de llamada para la búsqueda
        Beam *beamSelected = (Beam *) beam;
        beamSelected->getWorld()->QueryAABB(&savWormsinArea, dynamiteSelect->getAreaForSearch(dynamitePosition));
        for (auto &aElement: savWormsinArea.getWormsAndDistSquar()) {
            Worm *aWormToTakeDamage = (Worm *) (aElement.first);
            b2Vec2 impulseForWorm = dynamiteSelect->getImpulseForWorm(aWormToTakeDamage->getBody()->GetWorldCenter(),
                                                                      dynamitePosition, aElement.second);
            float damageForWorm = dynamiteSelect->getDamageForWorm(aElement.second);
            aWormToTakeDamage->getBody()->ApplyLinearImpulse(impulseForWorm,
                                                             aWormToTakeDamage->getBody()->GetWorldCenter(), true);
            aWormToTakeDamage->takeDamage(damageForWorm);
        }
        dynamiteSelect->destroyBody();
    }
}

void beamCollidesWithDynamite(GameObject* beam, GameObject* dynamite){
    std::cout << "beamCollidesWithDynamite\n";
    dynamiteCollideWithBeam(dynamite, beam);
}


void dynamiteCollidesWithWorm(GameObject* dynamite, GameObject* worm){
    std::cout << "dynamiteCollidesWithWorm\n";
}

void wormCollidesWithDynamite(GameObject* worm1, GameObject* missile){
    std::cout << "wormCollidesWithDynamite\n";
}

class MyContactListener : public b2ContactListener {

private:
    typedef void (*HitFunctionPtr)(GameObject *, GameObject *);

    std::map<std::pair<Entity, Entity>, HitFunctionPtr> collisionsMap;

public:
    MyContactListener(b2World *world) {
        world->SetContactListener(this);
        collisionsMap[std::make_pair(ENTITY_DYNAMITE, ENTITY_BEAM)] = &dynamiteCollideWithBeam;
        collisionsMap[std::make_pair(ENTITY_BEAM, ENTITY_DYNAMITE )] = &beamCollidesWithDynamite;
        collisionsMap[std::make_pair(ENTITY_DYNAMITE, ENTITY_WORM)] = &dynamiteCollidesWithWorm;
        collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_DYNAMITE)] = &wormCollidesWithDynamite;
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


class Prueba5 : public Test{
public:
    std::unique_ptr<Stage>  stage;
    std::vector<std::unique_ptr<Worm>> vecWorms;
    std::unique_ptr<MyContactListener> myContactListener;

    Prueba5() {
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
        if (key == GLFW_KEY_0){
            vecWorms[0]->placeDynamite();
        } else if (key == GLFW_KEY_1){
            vecWorms[0]->setWaitTime(1);
        } else if (key == GLFW_KEY_2){
            vecWorms[0]->setWaitTime(2);
        } else if (key == GLFW_KEY_3){
            vecWorms[0]->setWaitTime(3);
        } else if (key == GLFW_KEY_4){
            vecWorms[0]->setWaitTime(4);
        } else if (key == GLFW_KEY_5){
            vecWorms[0]->setWaitTime(5);
        } else if (key == GLFW_KEY_K){
            vecWorms[0]->walk(RIGHT);
        } else if (key == GLFW_KEY_H ){
            vecWorms[0]->walk(LEFT);
        }
    }

    void update() {
        std::vector<std::unique_ptr<Dynamite>>* dynamites = vecWorms[0]->getDynamites();
        auto it = dynamites->begin();
        while (it != dynamites->end()) {
            if ((*it)->isDestroyedBody()) {
                m_world->DestroyBody((*it)->getBody()); // Destruimos el cuerpo
                it = dynamites->erase(it);       // Eliminar el elemento del vector usando el iterador
            } else {
                (*it)->passTime();
                ++it;                 // Avanzar al siguiente elemento si no se elimina
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
        return new Prueba5;
    }

    ~Prueba5() override = default;
};

static int testIndex = RegisterTest("Examples", "Prueba 5", Prueba5::Create);
