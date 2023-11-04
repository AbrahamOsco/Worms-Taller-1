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

enum Entity{
    ENTITY_BEAM = 1,
    ENTITY_WATER = 2,
    ENTITY_EDGE = 3,
    ENTITY_WORM = 4
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
        std::cout << "Angle Act:" << angle << "Friciton: " << beamFriction << "\n";
        defFixtureBeam.friction = beamFriction;
        this->body->CreateFixture(&defFixtureBeam);
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
            idPosInitialWorms[idWorm] = std::pair<float, float>{posInitialX, posInitialY};
            idWorm++;
        }
        std::cerr << "Luego dle for del YamlParser  \n";

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

//add
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
    std::pair<float, float> jumpForward;
    std::pair<float, float> jumpBack;
    size_t numberContacts;

public:
    Worm(const size_t &idWorm, const float &posIniX, const float &posIniY) : GameObject(ENTITY_WORM), positionInitialX(posIniX), positionInitialY(posIniY) {
        this->idWorm = idWorm;
        hp = 100.0f;
        dragSpeed = 0.2f;
        directionLook = Direction::RIGHT;
        jumpForward = std::pair<float,float>{1.0f, 0.5f};
        jumpBack = std::pair<float,float>{0.2f, 1.2f};
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
        wormShape.m_p.Set(10.0f, 10.0f);
        wormShape.m_radius = 1.0f;

        b2FixtureDef defFixtureWorm;
        defFixtureWorm.shape = &wormShape;
        defFixtureWorm.friction = 4.0f;
        defFixtureWorm.density = 1.0f;
        this->body->CreateFixture(&defFixtureWorm);
    }

    void jumpBackwards() {
        float angleTita, initialSpeed;
        angleTita = atan(4.0f * jumpBack.second / jumpBack.first);       //  (4 *hmax)/distMaxHorizontal.
        initialSpeed = sqrt(jumpBack.first * 10.0f / (sin(2 * angleTita))); // el 1.0f hace referencia distancia horizontal de 1.0m;
        float speedX = initialSpeed * cos(angleTita);
        float speedY = initialSpeed * sin(angleTita);

        float impulseX = body->GetMass() * speedX;
        float impulseY = body->GetMass() * speedY;

        if (directionLook == RIGHT) {
            impulseX = -impulseX;
            directionLook = LEFT;       // Gusano "Da una vuelta hacia atras" mira al lado opuesto esta OK.
        } else if (directionLook == LEFT) {
            directionLook = RIGHT;   //MIRAMOS LADO OPUESTO AL Saltar hacia atras.
        } // ^

        b2Vec2 impulse(impulseX, impulseY); //  por la gravedad
        body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
    }
    void jumpForwards() {
        if(this->body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f)){
            float angleTita, initialSpeed;
            angleTita = atan(4.0f * jumpForward.second / jumpForward.first);       //  (4 *hmax)/distMaxHorizontal.
            initialSpeed = sqrt(jumpForward.first * 10.0f /
                                (sin(2 * angleTita))); // el 1.0f hace referencia distancia horizontal de 1.0m;
            float speedX = initialSpeed * cos(angleTita);
            float speedY = initialSpeed * sin(angleTita);

            float impulseX = body->GetMass() * speedX;
            float impulseY = body->GetMass() * speedY;
            if (directionLook == LEFT) {
                impulseX = -impulseX;
            }
            b2Vec2 impulse(impulseX, impulseY); //  por la gravedad
            body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
        }
    }
    void walk(Direction aDirection) {
        if(abs(body->GetLinearVelocity().x) < 2.0f && abs(body->GetLinearVelocity().y) < 2.0f) {
            directionLook = aDirection;
            float acceleration = getBody()->GetFixtureList()[0].GetFriction() * 10.0f; // aceleracion es la froz = u.N , las masas se cancelan queda mu * g.
            float speed = sqrt(2.0f * acceleration * dragSpeed); // la velocidad la sacamos como 2 * aceleracion * distancia.
            float impulse = body->GetMass() * speed;
            if (directionLook == Direction::LEFT ) {
                impulse = -impulse;
            }
            b2Vec2 impulseSpeed(impulse, 0.0f); //  por la gravedad
            body->ApplyLinearImpulse(impulseSpeed, body->GetWorldCenter(), true);
        }
    }

    void startContact(){
        numberContacts++;
    }
    void endContact(){
        numberContacts--;
    }

    void render(){
        if(numberContacts > 0 ){
            std::cout << "Hay contacnto  jejeje\n";
        } else {
            std::cout << "No hay contacto aun\n";
        }
    }

};

// Clase de colisiones el listener:
void wormCollidesWithBeam(GameObject* worm, GameObject* beam){
    std::cout << "Worm colisionar con el beam\n";
    Worm* unWorm = (Worm*) (worm);
    Beam* unaBeam = (Beam*) (beam);
    unWorm->startContact();
}

void beamCollideWithWorm(GameObject* beam, GameObject* worm){
    std::cout << "BEAM colisionar con el WORM\n";
    wormCollidesWithBeam(worm, beam);
}

void wormCollidesWithWater(GameObject* worm, GameObject* water){
    std::cout << "Worm colisionar con WATER\n";
    worm->destroyBody();
}
void waterCollidesWithWorm(GameObject* water, GameObject* worm){
    std::cout << "Water colisionar con el Worm\n";
    wormCollidesWithWater(worm, water);
}
void wormCollidesWithEdege(GameObject* worm, GameObject* edge){
    std::cout << "Worm collisiona con el edge\n";
}
void edgeCollidesWithWorm(GameObject* edge, GameObject* worm){
    std::cout << "Edge collisiona con el worm\n";
}


class MyContactListener : public b2ContactListener {
private:
    typedef void (*HitFunctionPtr)(GameObject *, GameObject *);

    std::map<std::pair<Entity, Entity>, HitFunctionPtr> collisionsMap;

public:
    MyContactListener(b2World *world) {
        world->SetContactListener(this);
        collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_BEAM)] = &wormCollidesWithBeam;
        collisionsMap[std::make_pair(ENTITY_BEAM, ENTITY_WORM)] = &beamCollideWithWorm;
        collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_WATER)] = &wormCollidesWithWater;
        collisionsMap[std::make_pair(ENTITY_WATER, ENTITY_WORM)] = &waterCollidesWithWorm;
        collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_EDGE)] = &wormCollidesWithEdege;
        collisionsMap[std::make_pair(ENTITY_EDGE, ENTITY_WORM)] = &edgeCollidesWithWorm;
    }

    void BeginContact(b2Contact* contact) override{
        GameObject* gameObject = (GameObject*) contact->GetFixtureA()->GetBody()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
        GameObject* otroGameObject = (GameObject*) contact->GetFixtureB()->GetBody()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
        if(gameObject == nullptr || otroGameObject == nullptr) return;
        auto iteratorElement =  collisionsMap.find( std::make_pair(gameObject->getEntityType(), otroGameObject->getEntityType())); // nos retorna un iterador
        std::cout << "gameObject->getEntityType()" << gameObject->getEntityType() << "\n";
        std::cout << "otroGameObject->getEntityType()" << otroGameObject->getEntityType() << "\n";
        if(iteratorElement != collisionsMap.end() ){
            std::cout << "iteratorElement != collisionsMap.end()\n";
            auto hitFunction = iteratorElement->second;
            if(hitFunction){
                hitFunction(gameObject, otroGameObject);
            }
        }
    }

};

class Prueba3 : public Test{
public:
    std::unique_ptr<Stage>  stage;
    std::unique_ptr<Worm> aWorm;
    std::unique_ptr<MyContactListener> myContactListener;
    Prueba3() {
        // Todo variable q esta aca dentro y queramos que perdure debemos usar el heap .
        stage = std::unique_ptr<Stage>{new Stage("Jaula Maldita")};
        stage->addToTheWorld(m_world);
        aWorm = std::unique_ptr<Worm>{new Worm(0, 5.0f, 20.0f) };
        aWorm->addToTheWorld(m_world);
        myContactListener = std::unique_ptr<MyContactListener>{new MyContactListener(m_world)};
    }

    void Keyboard(int key) override{
        if ( key == GLFW_KEY_I){
            aWorm->jumpForwards();
        }
        else if (key == GLFW_KEY_Y){
            aWorm->jumpBackwards();
        }
        else if (key == GLFW_KEY_K){
            aWorm->walk(RIGHT);
        }
        else if (key == GLFW_KEY_H ){
            aWorm->walk(LEFT);
        }
    }

    void update() {
        if(aWorm != nullptr && aWorm->isDestroyedBody()){
            m_world->DestroyBody(aWorm->getBody());
            aWorm = nullptr;
        }

    }

    void Step(Settings &settings) override {
        Test::Step(settings);
        g_debugDraw.DrawString(5, m_textLine, "Keys: (d) dynamic, (s) static, (k) kinematic");
        m_textLine += m_textIncrement;
        if(aWorm != nullptr){
            b2Vec2 posicion = aWorm->getBody()->GetWorldCenter();
            std::string posWorm = "X: " + std::to_string(posicion.x)  + " Y: " + std::to_string(posicion.y) + "  Masa: " + std::to_string( aWorm->getBody()->GetMass() ) + "\n";
            g_debugDraw.DrawString(5, m_textLine, posWorm.data());
            update();
        }
    }

    static Test* Create(){
        return new Prueba3;
    }

    ~Prueba3() override = default;
};

static int testIndex = RegisterTest("Examples", "Prueba 3", Prueba3::Create);
