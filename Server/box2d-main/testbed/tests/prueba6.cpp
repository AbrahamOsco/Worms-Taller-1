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
    ENTITY_GRENADE = 9,
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

enum Direction{
    RIGHT = 1, LEFT = 2
};

class MyFirstRayCastCallback : public b2RayCastCallback{
private:
    b2Body* body;
    b2Vec2 point;
    b2Vec2 normal;
    float fraction;
public:
    MyFirstRayCastCallback(){}

    float ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction) override{
        std::cout << "Entre a reportFixture Esto signfica que colisone con algo y hay que reportarlo \n";
        std::cout << "Colisiono a  un" << fraction*100 << " % de la trayectura total \n";
        GameObject* gameObject = (GameObject*) fixture->GetBody()->GetUserData().pointer;
        this->body = fixture->GetBody();
        this->point = point;
        this->normal = normal;
        this->fraction = fraction;
        return fraction;
    }
    b2Body* getBody(){
        return body;
    }
    float getFraction() const{
        return fraction;
    }
    void resetRayCast(){  //No olvidar invocar el resestRayCast luego de un rayCast.
        this->body = nullptr;
        this->fraction = 0.0f;
        this->point = this->normal = b2Vec2(0.0, 0.0f);
    }

    ~MyFirstRayCastCallback() = default;
};

class WeaponSight{
private:
    MyFirstRayCastCallback myRayCast;
    float rayLength;
    float rayAngle; // esta en grados.
    Direction direction; //posiblemnte elminarla ya que lo usamos dentro de un metodo y como que no mas por ej ataques

public:
    WeaponSight(float rayLength, float rayAngle) : rayLength(rayLength), rayAngle(rayAngle){
    }

    void resetRayCast() {
        this->myRayCast.resetRayCast();
    }

    void upMira() {
        rayAngle += 10.0f;
        if(rayAngle > 90.1f){
            rayAngle -= 10.0f;
        }
        std::cout << "Angle current Degree / Rad: : " << rayAngle << " / " <<  rayAngle * DEGRATORADIANS << " \n";
    }

    void downMira() {
        rayAngle -= 10.0f;
        if (rayAngle < -90.1f){
            rayAngle += 10.0f;
        }
        std::cout << "Angle current Degree / Rad: : " << rayAngle << " / " <<  rayAngle * DEGRATORADIANS << " \n";
    }

    // posiblemente sacarlo en un futuro  pasar directamnte la direccion al momento de hacer el raycast para obtener el curpo colisionado.
    void changeDirectiond(Direction direction) {
        this->direction = direction;
    }

    GameObject* getBodyCollidesWithRayCast(b2World *world, const b2Vec2& vec2, const Direction &directionCurrent) {
        b2Vec2 p1 = vec2;
        int factor = 1;
        this->direction = directionCurrent;
        if (this->direction == LEFT) factor = -1;
        b2Vec2 p2 = p1 + rayLength * b2Vec2(factor* cosf(rayAngle * DEGRATORADIANS), sinf(rayAngle * DEGRATORADIANS));
        world->RayCast(&myRayCast, p1, p2);
        std::cout << "myFirstRayCast->getFraction(): " << myRayCast.getFraction() << "\n";
        if ( myRayCast.getFraction() <= 0.001f ){
            std::cout << "Practicamente no colisione con nada ni recorri el 1% de la trayectoria asi que salgo\n";
            return nullptr;
        }
        GameObject* gameObject = (GameObject*) myRayCast.getBody()->GetUserData().pointer;
        if ( gameObject != nullptr and gameObject->getEntityType() == ENTITY_WORM){
            std::cout << "colisione con un gusano ahora le bajo la vida a punta de un golpe \n";
            return gameObject;
        }
        return nullptr;
    }

    // metodo de la clase weapon sight
    b2Vec2 getPositionP2RayCast(b2World *world, const b2Vec2& vec2, Direction direction) {
        b2Vec2 p1 = vec2;
        int factor = 1;
        this->direction = direction;
        if( direction == LEFT) {
            factor = -1;
        }
        b2Vec2 p2 = p1 + rayLength * b2Vec2( factor * cosf(rayAngle * DEGRATORADIANS), sinf(rayAngle * DEGRATORADIANS));
        std::cout << "Ray angle degr:" << rayAngle;
        std::cout << " |    p2.x : " << p2.x << " p2 .y : " << p2.y << " \n ";
        return p2;
    }

    b2Vec2 getImpulse(Direction direction, std::pair<float, float> impulse){
        int factor = 1, factorAngle = 1;
        if ( direction == LEFT){
            factor = -1;
        }
        // este if solo para la bazooka porque hace mov parabolico el misil. para darle efecto parabolico cuando los angulos son negativos nada mas
        if (rayAngle < 0.0f){
            factorAngle = -1; // OK !
        }
        return b2Vec2(factor * impulse.first , impulse.second * factorAngle);
    }
};


class Grenade : public GameObject {
protected:
    float mainDamage;
    float maxRadio;
    float restitution;
    bool fixedRotation;
    float maxImpulseMagnitude = 2.0f;

    std::chrono::steady_clock::time_point startTime, time;
    std::chrono::duration<float> waitTime;
    bool collided;
    bool exploded;

public:
    explicit Grenade(int wait) : GameObject(ENTITY_GRENADE), waitTime(wait),
                                    exploded(false), collided(false) {}

    b2AABB getAreaForSearch(const b2Vec2& positionMunition) const {
        b2AABB searchArea;
        searchArea.lowerBound = positionMunition - b2Vec2(maxRadio, maxRadio);
        searchArea.upperBound = positionMunition + b2Vec2(maxRadio, maxRadio);
        return searchArea;
    }

    void addToTheWorld(b2World* aWorld, b2Vec2 positionOrigen, b2Vec2 impulseGrenade){

        b2BodyDef grenadeDef;
        grenadeDef.type = b2_dynamicBody;
        grenadeDef.fixedRotation = fixedRotation;
        grenadeDef.position.Set(positionOrigen.x, positionOrigen.y );
        grenadeDef.userData.pointer = (uintptr_t) this;
        this->body = aWorld->CreateBody(&grenadeDef);
        b2CircleShape grenadeForm;
        grenadeForm.m_p.Set(0.0f, 0.0f); // offset de la posicion inicial va en (0,1) e 1 por q el radio de 1m empuja en 1 al origen de la circuferencia..
        grenadeForm.m_radius = 0.1f;

        b2FixtureDef defFixGrenade;
        defFixGrenade.shape = &grenadeForm;
        defFixGrenade.density = 1.0f; // ver el tema del aire luego.
        defFixGrenade.restitution = restitution;
        this->body->CreateFixture(&defFixGrenade);
        body->ApplyLinearImpulse( impulseGrenade, body->GetWorldCenter(), true);
    }

    b2Vec2 getImpulseForWorm(const b2Vec2 &positionWorm, const b2Vec2 &positionGrenade, float distanceWormToGrenade) {
        b2Vec2 impulseDirection = positionWorm - positionGrenade;
        impulseDirection.Normalize();
        float impulseMagnitude = maxImpulseMagnitude * std::max(0.0f, 1.0f - sqrt(distanceWormToGrenade) / maxRadio );
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

    float getDamageForWorm(const float &wormDistance) {
        float damageForWorm = mainDamage * std::max(0.0f, 1.0f - sqrt(wormDistance) / maxRadio);
        return damageForWorm;
    }

    void collide() {
        if (!collided) {
            collided = true;
            startTime = std::chrono::steady_clock::now();
        }
    }

    void passTime() {
        if (collided) {
            time = std::chrono::steady_clock::now();

            if (time - startTime >= waitTime && !exploded)
                explode();
        }
    }

    void explode() {
        exploded = true;
        body->ApplyLinearImpulse(b2Vec2(0.0f,0.03f),body->GetWorldCenter(),true); // para que se despegue y vuelva a chocar con la viga.
    }

    bool hasExploded() const {
        return exploded;
    }

    virtual void throwFragments(std::vector<std::unique_ptr<Grenade>>* grenades) {}

    virtual ~Grenade() = default;

};

class GrenadeFragment : public Grenade {
public:
    GrenadeFragment(float radio, float damage) : Grenade(0) {
        maxRadio = radio;
        mainDamage = damage;
        fixedRotation = true;
        restitution = 0.0f;
    }

    void throwFragments(std::vector<std::unique_ptr<Grenade>>* grenades) override {}

    ~GrenadeFragment() override = default;
};

class GreenGrenade : public Grenade {
public:
    explicit GreenGrenade(int wait) : Grenade(wait) {
        maxRadio = 2.0f;
        mainDamage = 30.0f;
        fixedRotation = true;
        restitution = 0.0f;
    }

    void throwFragments(std::vector<std::unique_ptr<Grenade>>* grenades) override {}

    ~GreenGrenade() override = default;
};

class RedGrenade : public Grenade {
    std::vector<b2Vec2> fragmentImpulses;
    std::vector<b2Vec2> fragmentPosOffset;
public:
    explicit RedGrenade(int wait) : Grenade(wait),
    fragmentImpulses({b2Vec2(-0.1f,0.1f), b2Vec2(-0.137f,0.027f), b2Vec2(0.137f,0.027f),
                      b2Vec2(0.1f,0.1f), b2Vec2(0.027f,0.137f), b2Vec2(-0.027f,0.137f)}) {
        maxRadio = 2.0f;
        mainDamage = 30.0f;
        fixedRotation = true;
        restitution = 0.0f;
    }

    void throwFragments(std::vector<std::unique_ptr<Grenade>>* grenades) override {
        for (auto & impulse : fragmentImpulses) {
            std::unique_ptr<Grenade> grenade{new GrenadeFragment(2.0f,10.0f)};
            grenade->addToTheWorld(body->GetWorld(),
                                   body->GetWorldCenter() + impulse, impulse);
            grenades->push_back(std::move(grenade));
        }
    }

    ~RedGrenade() override = default;
};

class Banana : public Grenade {
public:
    explicit Banana(int wait) : Grenade(wait) {
        maxRadio = 4.0f;
        mainDamage = 70.0f;
        fixedRotation = false;
        restitution = 0.9f;
    }

    void throwFragments(std::vector<std::unique_ptr<Grenade>>* grenades) override {}

    ~Banana() override = default;
};

class SaintGrenade : public Grenade {
public:
    explicit SaintGrenade(int wait) : Grenade(wait) {
        maxRadio = 8.0f;
        mainDamage = 110.0f;
        fixedRotation = true;
        restitution = 0.0f;
    }

    void throwFragments(std::vector<std::unique_ptr<Grenade>>* grenades) override {}

    ~SaintGrenade() override = default;
};


class GrenadeHolder {
    std::pair<float, float> impulseWeapon; // impulse x, impulse y
    WeaponSight weaponSight;
    std::vector<std::unique_ptr<Grenade>> grenades;

public:
    GrenadeHolder() : weaponSight(0.5f, 0.0) {
        impulseWeapon.first = 0.1f;
        impulseWeapon.second = 0.1f;
    }

    void resetRayCast() {
        weaponSight.resetRayCast();
    }

    void upMira() {
        weaponSight.upMira();
    }

    void downMira() {
        weaponSight.downMira();
    }

    void throwGreenGrenade(b2World *world, int wait, b2Vec2 pos, Direction direction) {
        b2Vec2 p2 = weaponSight.getPositionP2RayCast(world, pos, direction);
        b2Vec2 impulse = weaponSight.getImpulse(direction, impulseWeapon);

        std::unique_ptr<Grenade> grenade{new GreenGrenade(wait)};
        grenade->addToTheWorld(world, p2, impulse);
        grenades.push_back(std::move(grenade));
    }

    void throwRedGrenade(b2World *world, int wait, b2Vec2 pos, Direction direction) {
        b2Vec2 p2 = weaponSight.getPositionP2RayCast(world, pos, direction);
        b2Vec2 impulse = weaponSight.getImpulse(direction, impulseWeapon);

        std::unique_ptr<Grenade> grenade{new RedGrenade(wait)};
        grenade->addToTheWorld(world, p2, impulse);
        grenades.push_back(std::move(grenade));
    }

    void throwBanana(b2World *world, int wait, b2Vec2 pos, Direction direction) {
        b2Vec2 p2 = weaponSight.getPositionP2RayCast(world, pos, direction);
        b2Vec2 impulse = weaponSight.getImpulse(direction, impulseWeapon);

        std::unique_ptr<Grenade> grenade{new Banana(wait)};
        grenade->addToTheWorld(world, p2, impulse);
        grenades.push_back(std::move(grenade));
    }

    void throwSaintGrenade(b2World *world, int wait, b2Vec2 pos, Direction direction) {
        b2Vec2 p2 = weaponSight.getPositionP2RayCast(world, pos, direction);
        b2Vec2 impulse = weaponSight.getImpulse(direction, impulseWeapon);

        std::unique_ptr<Grenade> grenade{new SaintGrenade(wait)};
        grenade->addToTheWorld(world, p2, impulse);
        grenades.push_back(std::move(grenade));
    }

    std::vector<std::unique_ptr<Grenade>>* getGrenades(){
        return &grenades;
    }

};

class Worm : public GameObject {
    size_t idWorm;
    Direction directionLook;
    float  hp;
    float dragSpeed;
    float positionInitialX;
    float positionInitialY;
    b2World* world;
    GrenadeHolder grenadeHolder;
    int waitTime;

public:
    Worm(const size_t &idWorm, const float &posIniX, const float &posIniY) : GameObject(ENTITY_WORM), positionInitialX(posIniX),
        positionInitialY(posIniY) {
        this->idWorm = idWorm;
        directionLook = Direction::RIGHT;
        hp = 100.0f;
        dragSpeed = 0.2f;
        waitTime = 1;  // Supuesto: si el usuario no presiona nada el tiempo de espera
                       // predeterminado es 1s.
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

    void upMira(){
        grenadeHolder.upMira();
    }

    void downMira(){
        grenadeHolder.downMira();
    }

    void throwGreenGrenade(){
        grenadeHolder.throwGreenGrenade(world,waitTime,body->GetWorldCenter(),directionLook);
        grenadeHolder.resetRayCast();
    }

    void throwRedGrenade(){
        grenadeHolder.throwRedGrenade(world,waitTime,body->GetWorldCenter(),directionLook);
        grenadeHolder.resetRayCast();
    }

    void throwBanana(){
        grenadeHolder.throwBanana(world,waitTime,body->GetWorldCenter(),directionLook);
        grenadeHolder.resetRayCast();
    }

    void throwSaintGrenade(){
        grenadeHolder.throwSaintGrenade(world,waitTime,body->GetWorldCenter(),directionLook);
        grenadeHolder.resetRayCast();
    }

    b2World* getWorld(){
        return world;
    }

    std::vector<std::unique_ptr<Grenade>>* getGrenades(){
        return this->grenadeHolder.getGrenades();
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

void grenadeCollideWithBeam(GameObject* grenade, GameObject* beam){
    std::cout << "grenadeCollideWithBeam\n";
    b2Vec2 grenadePosition = grenade->getBody()->GetWorldCenter();
    Beam *beamSelected = (Beam *) beam;

    Grenade* grenadeSelect = (Grenade*)  grenade;

    grenadeSelect->collide();
    if (grenadeSelect->hasExploded()) {
        std::cout << "boom\n";
        SaveWormsInAreaQueryTest savWormsinArea(grenadePosition);     // Función de devolución de llamada para la búsqueda
        beamSelected->getWorld()->QueryAABB(&savWormsinArea, grenadeSelect->getAreaForSearch(grenadePosition));
        for (auto &aElement: savWormsinArea.getWormsAndDistSquar()) {
            Worm *aWormToTakeDamage = (Worm *) (aElement.first);
            b2Vec2 impulseForWorm = grenadeSelect->getImpulseForWorm(aWormToTakeDamage->getBody()->GetWorldCenter(),
                                                                      grenadePosition, aElement.second);
            float damageForWorm = grenadeSelect->getDamageForWorm(aElement.second);
            aWormToTakeDamage->getBody()->ApplyLinearImpulse(impulseForWorm,
                                                             aWormToTakeDamage->getBody()->GetWorldCenter(), true);
            aWormToTakeDamage->takeDamage(damageForWorm);
        }
        grenadeSelect->destroyBody();
    }
}

void beamCollidesWithGrenade(GameObject* beam, GameObject* grenade){
    std::cout << "beamCollidesWithGrenade\n";
    grenadeCollideWithBeam(grenade, beam);
}


void grenadeCollidesWithWorm(GameObject* grenade, GameObject* worm){
    std::cout << "grenadeCollidesWithWorm\n";
    b2Vec2 grenadePosition = grenade->getBody()->GetWorldCenter();
    Worm* wormSelect = (Worm*) worm;

    Grenade* grenadeSelect = (Grenade*)  grenade;

    grenadeSelect->collide();
    if (grenadeSelect->hasExploded()) {
        std::cout << "boom\n";
        SaveWormsInAreaQueryTest savWormsinArea(grenadePosition);     // Función de devolución de llamada para la búsqueda
        wormSelect->getWorld()->QueryAABB(&savWormsinArea, grenadeSelect->getAreaForSearch(grenadePosition));
        for (auto &aElement: savWormsinArea.getWormsAndDistSquar()) {
            Worm *aWormToTakeDamage = (Worm *) (aElement.first);
            b2Vec2 impulseForWorm = grenadeSelect->getImpulseForWorm(aWormToTakeDamage->getBody()->GetWorldCenter(),
                                                                     grenadePosition, aElement.second);
            float damageForWorm = grenadeSelect->getDamageForWorm(aElement.second);
            aWormToTakeDamage->getBody()->ApplyLinearImpulse(impulseForWorm,
                                                             aWormToTakeDamage->getBody()->GetWorldCenter(), true);
            aWormToTakeDamage->takeDamage(damageForWorm);
        }
        grenadeSelect->destroyBody();
    }
}

void wormCollidesWithGrenade(GameObject* worm1, GameObject* grenade){
    std::cout << "wormCollidesWithGrenade\n";
    grenadeCollidesWithWorm(grenade,worm1);
}

class MyContactListener : public b2ContactListener {

private:
    typedef void (*HitFunctionPtr)(GameObject *, GameObject *);

    std::map<std::pair<Entity, Entity>, HitFunctionPtr> collisionsMap;

public:
    MyContactListener(b2World *world) {
        world->SetContactListener(this);
        collisionsMap[std::make_pair(ENTITY_GRENADE, ENTITY_BEAM)] = &grenadeCollideWithBeam;
        collisionsMap[std::make_pair(ENTITY_BEAM, ENTITY_GRENADE )] = &beamCollidesWithGrenade;
        collisionsMap[std::make_pair(ENTITY_GRENADE, ENTITY_WORM)] = &grenadeCollidesWithWorm;
        collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_GRENADE)] = &wormCollidesWithGrenade;
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
        if (key == GLFW_KEY_8){
            vecWorms[0]->throwGreenGrenade();
        } else if (key == GLFW_KEY_9){
            vecWorms[0]->throwRedGrenade();
        } else if (key == GLFW_KEY_7){
            vecWorms[0]->throwBanana();
        } else if (key == GLFW_KEY_6){
            vecWorms[0]->throwSaintGrenade();
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
        } else if (key == GLFW_KEY_T){
            vecWorms[0]->upMira();
        } else if (key == GLFW_KEY_G){
            vecWorms[0]->downMira();
        }
    }

    void update() {
        std::vector<std::unique_ptr<Grenade>>* grenades = vecWorms[0]->getGrenades();
        std::vector<std::unique_ptr<Grenade>> fragments;
        auto it = grenades->begin();
        while (it != grenades->end()) {
            if ((*it)->isDestroyedBody()) {
                (*it)->throwFragments(&fragments);
                m_world->DestroyBody((*it)->getBody()); // Destruimos el cuerpo
                it = grenades->erase(it);       // Eliminar el elemento del vector usando el iterador
            } else {
                (*it)->passTime();
                ++it;                 // Avanzar al siguiente elemento si no se elimina
            }
        }
        for (auto & fragment : fragments) {
            grenades->push_back(std::move(fragment));
        }
    }

    void Step(Settings &settings) override {
        Test::Step(settings);
        g_debugDraw.DrawString(5, m_textLine, "Keys: (d) dynamic, (s) static, (k) kinematic");
        m_textLine += m_textIncrement;
        if(vecWorms[0] != nullptr){
            update();
        }
    }

    static Test* Create(){
        return new Prueba4;
    }

    ~Prueba4() override = default;
};

static int testIndex = RegisterTest("Examples", "Prueba 4", Prueba4::Create);
