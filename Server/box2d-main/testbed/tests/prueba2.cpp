#include "test.h"
#include <box2d/b2_math.h>
#include <box2d/box2d.h>
#include <box2d/b2_body.h>
#include <cmath>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <yaml-cpp/yaml.h>
#include <cstdlib>
#include <linux/limits.h>

#define MITAD_TAMANIO_GUSANO 1.0f

enum EntityType {WATER_ENTITY, EDGE_ENTITY, WORM_ENTITY, BEAM_ENTITY};
enum Direction {LEFT, RIGHT};

class Entity {
protected:
    EntityType type;
    b2Body* body;
    bool destroyed;
public:
    explicit Entity(EntityType type) : type(type), body(nullptr), destroyed(false) {}
    EntityType getEntityType() { return type; }
    b2Body* getEntityBody() { return body; }
    void destroy() { destroyed = true; }
    bool isDead() const { return destroyed; }
    virtual ~Entity() = default;
};

class EntityWorm : public Entity {
    b2World* world;
    Direction isLooking;
public:
    EntityWorm(b2World* world, b2Vec2 initialPos) : Entity(WORM_ENTITY), world(world), isLooking(RIGHT) {
        b2PolygonShape shapeWorm;
        shapeWorm.SetAsBox(MITAD_TAMANIO_GUSANO, MITAD_TAMANIO_GUSANO, b2Vec2(2.0f, 1.450f), 0.0f);

        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position.Set(initialPos.x,initialPos.y);
        bd.fixedRotation = true;
        bd.userData.pointer = (uintptr_t) this;

        body = world->CreateBody(&bd);
        body->CreateFixture(&shapeWorm, 1.0f);
    }

    void walk(Direction dir) {
        if(abs(body->GetLinearVelocity().x) < 2.0f && abs(body->GetLinearVelocity().y) < 2.0f) {
            isLooking = dir;
            float acceleration = 2.3f * 10.0f; // aceleracion es la froz = u.N , las masas se cancelan queda mu * g.
            float speed = sqrt(2.0f * acceleration * 0.2f); // la velocidad la sacamos como 2 * aceleracion * distancia.
            float impulse = body->GetMass() * speed;
            if (dir == LEFT) {
                impulse = -impulse;
            }
            b2Vec2 impulseSpeed(impulse, 0.0f); //  por la gravedad
            body->ApplyLinearImpulse(impulseSpeed, body->GetWorldCenter(), true);
        }
    }

    void jumpForwards() {
        if(abs(body->GetLinearVelocity().x) < 2.0f && abs(body->GetLinearVelocity().y) < 2.0f) {
            float angleTita, initialSpeed;

            angleTita = atan(4.0f *0.5f/1.0f);       //  (4 *hmax)/distMaxHorizontal.
            initialSpeed = sqrt( 1.0f*10/(sin(2*angleTita)) ); // el 1.0f hace referencia distancia horizontal de 1.0m;
            float speedX = initialSpeed* cos(angleTita);
            float speedY = initialSpeed * sin(angleTita);

            float impulseX = body->GetMass() * speedX;
            float impulseY = body->GetMass() * speedY;
            if (isLooking == LEFT) {
                impulseX = -impulseX;
            }
            b2Vec2 impulse(impulseX, impulseY); //  por la gravedad
            body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
        }
    }

    void jumpBackwards() {
        if(abs(body->GetLinearVelocity().x) < 2.0f && abs(body->GetLinearVelocity().y) < 2.0f) {
            float angleTita, initialSpeed;

            angleTita = atan(4.0f * 1.2f / 0.2f);  //  (4 *hmax)/distMaxHorizontal.
            initialSpeed = sqrt(0.2f * 10 / (sin(2 * angleTita))); // el 0.2f hace referencia distancia horizontal de 0.2m;
            float speedX = initialSpeed * cos(angleTita);
            float speedY = initialSpeed * sin(angleTita);

            float impulseX = body->GetMass() * speedX;
            float impulseY = body->GetMass() * speedY;

            if (isLooking == LEFT) {
                impulseX = -impulseX;
                isLooking = RIGHT;       // cambia donde mira al hacer el salto?
            } else { isLooking = LEFT; } // ^

            b2Vec2 impulse(impulseX, impulseY); //  por la gravedad
            body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
        }
    }

    ~EntityWorm() override = default;
};

class EntityEdges : public Entity {
    b2World* world;
public:
    EntityEdges(b2World* world, float height, float width) : Entity(EDGE_ENTITY), world(world) {
        b2BodyDef bd;
        bd.userData.pointer = (uintptr_t) this;
        body = world->CreateBody(&bd);

        b2EdgeShape shape;
        shape.SetTwoSided(b2Vec2(0.0f, 0.0f), b2Vec2(width, 0.0f));
        body->CreateFixture(&shape, 0.0f);

        shape.SetTwoSided(b2Vec2(0.0f, 0.0f), b2Vec2(0.0f, -height));
        body->CreateFixture(&shape, 0.0f);

        shape.SetTwoSided(b2Vec2(width, 0.0f), b2Vec2(width, -height));
        body->CreateFixture(&shape, 0.0f);
    }
    ~EntityEdges() override = default;
};

class EntityWater : public Entity {
    b2World* world;
public:
    EntityWater(b2World* world, float height, float width) : Entity(WATER_ENTITY), world(world) {
        b2BodyDef bd;
        bd.userData.pointer = (uintptr_t) this;
        body = world->CreateBody(&bd);

        b2EdgeShape shape;
        shape.SetTwoSided(b2Vec2(0.0, -height), b2Vec2(width, -height));
        body->CreateFixture(&shape, 0.0f);
    }
    ~EntityWater() override = default;
};

class EntityBeam : public Entity {
    float length;
    float angle;
    b2Vec2 position;
public:
    EntityBeam(float length, float angle, b2Vec2 position) :
        Entity(BEAM_ENTITY), length(length), angle(angle), position(position) {}

    void addToWorld(b2World* world) {
        float angleR = angle/180.0f * b2_pi;
        b2PolygonShape shapeBeam;
        shapeBeam.SetAsBox(length/2, 0.4f, b2Vec2(0.0f, 0.0f), angleR ); // viga larga de 6m y 0.8 m de ancho

        b2BodyDef bd;
        bd.type = b2_staticBody;
        bd.position.Set(position.x,position.y);
        bd.userData.pointer = (uintptr_t) this;

        body = world->CreateBody(&bd);
        body->CreateFixture(&shapeBeam,0.0f);

        b2FixtureDef beamFriction;
        beamFriction.shape = &shapeBeam;
        float beamFrictionValue = 3.0f;
        if(angle > 45 && angle<= 90){
            beamFrictionValue = 0.2f;
        }
        beamFriction.friction = beamFrictionValue;
        body->CreateFixture(&beamFriction);
    }

    ~EntityBeam() override = default;
};

class Stage {
    float height;
    float width;
    EntityEdges* edges;
    EntityWater* water;
    std::vector<EntityBeam*> beams;
public:
    Stage(float height, float width, std::vector<EntityBeam*>&& beams) :
        edges(nullptr), water(nullptr), beams(std::move(beams)), height(height), width(width) {}

    void addToWorld (b2World* world) {
        edges = new EntityEdges(world,height,width);
        water = new EntityWater(world,height,width);
        for (auto & beam : beams) {
            beam->addToWorld(world);
        }
    }
    ~Stage(){
        for (auto & beam : beams){
            delete beam;
        }
    }
};

class contactListener : public b2ContactListener {
public:
    explicit contactListener(b2World* world) {
        world->SetContactListener(this);
    }

    void BeginContact(b2Contact *contact) override {
        auto* object1 = (Entity*) contact->GetFixtureA()->GetBody()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
        auto* object2 = (Entity*) contact->GetFixtureB()->GetBody()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
        if (object1 != nullptr && object2 != nullptr){
            if (object1->getEntityType() == EntityType::WORM_ENTITY
            && object2->getEntityType() == EntityType::WATER_ENTITY) {
                object1->destroy();
            } else if (object1->getEntityType() == EntityType::WATER_ENTITY
            && object2->getEntityType() == EntityType::WORM_ENTITY) {
                object2->destroy();
            }
        }
    }
};

class StageLoader {

    static std::vector<EntityBeam*> getBeams(const YAML::Node& beamsNode) {
        std::vector<EntityBeam*> beams;
        for (YAML::const_iterator it = beamsNode.begin(); it != beamsNode.end(); ++it) {
            const YAML::Node& beamNode = *it;
            auto length = beamNode["length"].as<float>();
            auto angle = beamNode["angle"].as<float>();
            auto posX = beamNode["x"].as<float>();
            auto posY = beamNode["y"].as<float>();

            auto* beam = new EntityBeam(length, angle,b2Vec2(posX,posY));
            beams.push_back(beam);
        }
        return beams;
    }

public:
    StageLoader() = default;
    
    static Stage* getStage(const std::string& aStageName) {
        // busco el path del archivo
        // hay que cambiarlo para la implementacion de verdad
        char startPathC[PATH_MAX];
        realpath("../../", startPathC);
        std::string startPath(startPathC);
        std::string toErase("/Server/box2d-main");
        unsigned long startPos = startPath.find(toErase);
        startPath.erase(startPos,toErase.length());
        std::string fullPath(startPath + "/Stages/"+ aStageName + ".yaml");

        YAML::Node node = YAML::LoadFile(fullPath);

        std::vector<EntityBeam*> beams = getBeams(node["beams"]);

        auto height = node["height"].as<float>();
        auto width = node["width"].as<float>();

        auto* stage = new Stage(height, width, std::move(beams));
        return stage;
    }
};

class Prueba2 : public Test{
    EntityWorm* worm;
    Stage* stage;
    contactListener cl;
public:
    Prueba2() : worm(nullptr), stage(nullptr), cl(m_world) {

        // Stage
        stage = StageLoader::getStage("JaulaMaldita");
        stage->addToWorld(m_world);

        // Worm
        b2Vec2 initialPos(15,-5);
        worm = new EntityWorm(m_world,initialPos);


        m_world->SetContactListener(&cl);
    }

    void Keyboard(int key) override{
        if ( key == GLFW_KEY_I){
            worm->jumpForwards();
        }
        else if (key == GLFW_KEY_Y){
            worm->jumpBackwards();
        }
        else if (key == GLFW_KEY_D){
            worm->walk(RIGHT);
        }
        else if (key == GLFW_KEY_A ){
            worm->walk(LEFT);
        }
    }

    void update() {
        if (worm != nullptr && worm->isDead()){
            m_world->DestroyBody(worm->getEntityBody());
            worm = nullptr;
        }
    }

    void Step(Settings &settings) override {
        Test::Step(settings);
        update();
    }

    static Test* Create(){
        return new Prueba2;
    }

    ~Prueba2() override = default;
};

static int testIndex = RegisterTest("Examples", "Prueba 2", Prueba2::Create);
