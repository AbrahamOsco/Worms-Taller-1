#include "test.h"
#include <box2d/b2_math.h>
#include <box2d/box2d.h>
#include <box2d/b2_body.h>
#include "math.h"
#include <iostream>

#define MITAD_TAMANIO_GUSANO 1.0f

enum ESTADO_MOV { MOVER_IZQUIERDA, MOVER_DERECHA, STOP };
enum ENTITY { ORIGEN, GUSANO, VIGA };
enum DIR_MOVE { IZQUIERDA, DERECHA};
enum JUMP_TYPE {SALTO_ADELANTE, SALTO_ATRAS};

class GameObject{
private:
    ENTITY tipoEntidad;

public:
    GameObject(ENTITY unaEntidad) : tipoEntidad(unaEntidad) {}

    virtual ENTITY getTypeEntity() {
        return tipoEntidad;
    }
    virtual ~GameObject() = default;
};

class Beam : public GameObject {
private:
    b2Body* body;
public:
    Beam(b2World* world, b2Vec2 coordWorld, b2Vec2 dimensions, float angulo) : GameObject(ENTITY::VIGA)  {
        b2BodyDef defViga;
        defViga.type = b2_staticBody;
        defViga.position.Set(coordWorld.x, coordWorld.y);
        defViga.userData.pointer = (uintptr_t) this;
        this->body = world->CreateBody(&defViga);

        float anguloRadianes = angulo/180.0f * b2_pi;
        b2PolygonShape formaViga;
        formaViga.SetAsBox(dimensions.x, dimensions.y, b2Vec2(0.0f, 0.0f), anguloRadianes ); // viga larga de 6m y 0.8 m de ancho
        b2FixtureDef defFixtViga;
        defFixtViga.shape = &formaViga;

        float friccionPorViga = 2.0f; // antes era 1.5f
        if(angulo > 45 && angulo <= 90){
            friccionPorViga = 0.2f;
        }
        defFixtViga.friction = friccionPorViga;
        this->body->CreateFixture(&defFixtViga);
    }
    ~Beam() = default;
};

class Worm : GameObject {
private:
    b2Body* body;
    size_t idPlayer;
    bool hayContacto;
public:
    Worm(b2World* world, float positionYOrig, size_t idPlayer) : GameObject(ENTITY::GUSANO), idPlayer(idPlayer), hayContacto(false) {
        b2BodyDef defGusano;
        defGusano.type = b2_dynamicBody;
        defGusano.position.Set(0.0f, positionYOrig);
        defGusano.fixedRotation = true;  // PARA evitar "girar" al recibir impactos los gusasnos,  solo debe desplazarse de los lados.
        defGusano.userData.pointer = (uintptr_t) this;

        this->body = world->CreateBody(&defGusano);

        b2PolygonShape shapeGusano;
        shapeGusano.SetAsBox(MITAD_TAMANIO_GUSANO, MITAD_TAMANIO_GUSANO, b2Vec2(2.0f, 1.450f), 0.0f);

        b2FixtureDef defFixtGusano;
        defFixtGusano.shape = &shapeGusano;
        defFixtGusano.friction = 2.0f;
        defFixtGusano.density = 1.0f;
        this->body->CreateFixture(&defFixtGusano);
    }

    b2Body* getWorm() const{
        return body;
    }

    void move(DIR_MOVE aDirection){
        // le sume 0.3 al rozamiento para considerar tambien el rozamiendo del a viga con el gusano ajuste magico.
        float aceleracion = 2.3f * 10.0f; // aceleracion es la froz = u.N , las masas se cancelan queda mu * g.
        float velocidad = sqrt(2.0f * aceleracion * 0.2f); // la velocidad la sacamos como 2 * aceleracion * distancia.
        float impulso = body->GetMass() * velocidad;
        if(aDirection == DIR_MOVE::IZQUIERDA){
            b2Vec2 impulsoVelocidad(-impulso, 0.0f); //  por la gravedad
            body->ApplyLinearImpulse(impulsoVelocidad, body->GetWorldCenter(), true);
        } else if ( aDirection == DIR_MOVE::DERECHA){
            b2Vec2 impulsoVelocidad(impulso, 0.0f); //  por la gravedad
            body->ApplyLinearImpulse(impulsoVelocidad, body->GetWorldCenter(), true);
        }
    }
    void jump(JUMP_TYPE tipoSalto){
        float anguloTita, velocidadInicial, factorDirecion = 1.0f;

        if(tipoSalto == JUMP_TYPE::SALTO_ADELANTE){   // Movimiento parabolio en y = 0,5m de altura y en e x = 1m.
            anguloTita = atan(4.0f *0.5f/1.0f);       //  (4 *hmax)/distMaxHorizontal.
            velocidadInicial = sqrt( 1.0f*10/(sin(2*anguloTita)) ); // el 1.0f hace referencia distancia horizontal de 1.0m;
        } else if (tipoSalto == JUMP_TYPE::SALTO_ATRAS){ // Salto hacia atras retrocede 0,2m en x y arriba se desplaza 1.2m
            anguloTita = atan(4.0f *1.2f/0.2f);  //  (4 *hmax)/distMaxHorizontal.
            velocidadInicial = sqrt( 0.2f*10/(sin(2*anguloTita)) ); // el 0.2f hace referencia distancia horizontal de 0.2m;
            factorDirecion = -1.0f;
        }
        float velocidadX = velocidadInicial* cos(anguloTita);
        float velocidadY = velocidadInicial * sin(anguloTita);

        float impulsoX = body->GetMass() * velocidadX * factorDirecion;
        float impulsoY = body->GetMass() * velocidadY;
        b2Vec2 impulsoAAplicar(impulsoX, impulsoY); //  por la gravedad
        body->ApplyLinearImpulse(impulsoAAplicar, body->GetWorldCenter(), true);
    }

    void startContact(){
        hayContacto = true;
    }
    void endContact(){
        hayContacto = false;
    }

    void render(){
        if(hayContacto){
            std::cout << "Hay contacnto  jejeje\n";
        } else {
            std::cout << "No hay contacto aun\n";
        }
    }

    ~Worm() = default;

};
/*
        if(gameObject->getTypeEntity() == ENTITY::GUSANO){
            std::cout << "Entre aca ENTTITY-1\n";
            Worm* unWorm = (Worm*) gameObject;
            unWorm->startContact();
        } else if (otroGameObject->getTypeEntity() == ENTITY::GUSANO){
            std::cout << "Entre aca ENTTITY-2\n";
            Worm* unWorm = (Worm*) otroGameObject;
            unWorm->startContact();
        }
 */
class MyContactListener : public b2ContactListener{

    void BeginContact(b2Contact* contact) override{
        GameObject* gameObject = (GameObject*) contact->GetFixtureA()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
        std::cout << "Luego del primer casteo\n";
        GameObject* otroGameObject = (GameObject*) contact->GetFixtureB()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
        std::cout << "Luego del segundo casteo\n";
        if(gameObject->getTypeEntity() == ENTITY::GUSANO){
            std::cout << "Entre aca ENTTITY-1\n";

        } else if (otroGameObject->getTypeEntity() == ENTITY::GUSANO){
            std::cout << "Entre aca ENTTITY-2\n";
        }
    }

    void EndContact(b2Contact* contact) {
        GameObject* gameObject = (GameObject*)contact->GetFixtureA()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
        GameObject* otroGameObject = (GameObject*)contact->GetFixtureB()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
        if(gameObject->getTypeEntity() == ENTITY::GUSANO){
            std::cout << "Entre aca ENTTITY-1 END-CONTACT \n";

        } else if (otroGameObject->getTypeEntity() == ENTITY::GUSANO){
            std::cout << "Entre aca ENTTITY-2 ENC CONTACT \n";
        }
    }
};
MyContactListener myContactListener;

class Prueba1 : public Test{

public:
    float maxAlturaY;
    float maxRangoX;
    bool estaEnContacto;
    Worm unGusano;
    Prueba1() : unGusano(m_world, 3.450f, 1) {
        maxAlturaY = 0.0f;
        maxRangoX = 0.0f;
        estaEnContacto = false;
        float tamanio = 30.0f;
        m_world->SetContactListener(&myContactListener);
        Beam beam1(m_world, b2Vec2(tamanio/2, 0.0f), b2Vec2(tamanio/2, 0.4f), 0 );
        Beam beam2(m_world, b2Vec2(0, tamanio/2), b2Vec2(tamanio/2, 0.4f), 90 );
        Beam beam3(m_world, b2Vec2(tamanio, tamanio/2), b2Vec2(tamanio/2, 0.4f), 90);
        Beam beam4(m_world, b2Vec2(tamanio/2, tamanio), b2Vec2(tamanio/2, 0.4f), 0);
    }
    void startContact(){
        estaEnContacto = true;
    }
    void endContact(){
        estaEnContacto = false;
    }

    void Keyboard(int key) override{
        if ( key == GLFW_KEY_I){
            unGusano.jump(JUMP_TYPE::SALTO_ADELANTE);
        }
        else if (key == GLFW_KEY_Y){
            unGusano.jump(JUMP_TYPE::SALTO_ATRAS);
        }
        else if (key == GLFW_KEY_K){
            unGusano.move(DIR_MOVE::DERECHA);
        }
        else if (key == GLFW_KEY_H ){
            unGusano.move(DIR_MOVE::IZQUIERDA);
        }
    }

    void Step(Settings& settings) override{
        Test::Step(settings);
        g_debugDraw.DrawString(5, m_textLine, "Keys: (d) dynamic, (s) static, (k) kinematic");
        m_textLine += m_textIncrement;
        b2Vec2 posicion = unGusano.getWorm()->GetWorldCenter();
        if( posicion.y > maxAlturaY) maxAlturaY = posicion.y;
        if (posicion.x > maxRangoX)  maxRangoX = posicion.x;
        std::string posicionGusano = "X: " + std::to_string(posicion.x)  + " Y: " + std::to_string(posicion.y) + "  Masa: " + std::to_string( unGusano.getWorm()->GetMass() ) + "\n";
        std::string estadisticas = posicionGusano + "MaxAltura Y: " +  std::to_string(maxAlturaY) + "  Max DistX: " + std::to_string(maxRangoX) + "\n";
        g_debugDraw.DrawString(5, m_textLine, estadisticas.data());
    }

    static Test* Create(){
        return new Prueba1;
    }

};

static int testIndex = RegisterTest("Examples", "Prueba 1", Prueba1::Create);

