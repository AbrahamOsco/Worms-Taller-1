
// Prueba 1 con box2d preuba de concepto hacer esto hasta no poder.
#include "test.h"
#include "math.h"
#include <iostream>
#define MITAD_TAMANIO_GUSANO 1.0f

enum ESTADO_MOV { MOVER_IZQUIERDA, MOVER_DERECHA, STOP };


b2Body* crearNuevaViga(b2Vec2 posGlobal, b2Vec2 dimensiones, float angulo, b2World* m_world){
    // Hacemos una Viga. rotada 45º
    b2BodyDef defViga;
    defViga.type = b2_staticBody;
    defViga.position.Set(posGlobal.x, posGlobal.y);
    b2Body* unaViga = m_world->CreateBody(&defViga);

    float anguloRadianes = angulo/180.0f * b2_pi;
    b2PolygonShape formaViga;
    formaViga.SetAsBox(dimensiones.x, dimensiones.y, b2Vec2(0.0f, 0.0f), anguloRadianes ); // viga larga de 6m y 0.8 m de ancho
    b2FixtureDef defFixtViga;
    defFixtViga.shape = &formaViga;

    float friccionPorViga = 2.0f; // antes era 1.5f
    if(angulo > 45 && angulo <= 90){
        friccionPorViga = 0.2f;
    }
    defFixtViga.friction = friccionPorViga;
    b2Fixture* vigaFixture = unaViga->CreateFixture(&defFixtViga);
    return unaViga;
}

b2Body* crearGusano(b2World* m_world, float positionY){
    b2BodyDef defGusanoBody;
    defGusanoBody.position.Set(0.0f, positionY);
    defGusanoBody.type = b2_dynamicBody;
    defGusanoBody.fixedRotation = true;  // PARA evitar "girar" al recibir impactos los gusasnos,  solo debe desplazarse de los lados.
    b2Body* gusanoBody = m_world->CreateBody(&defGusanoBody);
    b2PolygonShape shapeGusano;
    shapeGusano.SetAsBox(MITAD_TAMANIO_GUSANO, MITAD_TAMANIO_GUSANO, b2Vec2(2.0f, 1.450f), 0.0f);
    b2FixtureDef defFixtGusano;
    defFixtGusano.shape = &shapeGusano;
    defFixtGusano.friction = 2.0f;
    defFixtGusano.density = 2.0f;
    gusanoBody->CreateFixture(&defFixtGusano);
    return gusanoBody;
}



class Prueba1 : public Test{

public:
    b2Body* gusanos[3];
    bool fuerzaON;
    float maxAlturaY;
    float maxRangoX;
    bool estanEnElAire;
    ESTADO_MOV estadoMov;

    Prueba1(){
        maxAlturaY = 0.0f;
        maxRangoX = 0.0f;
        fuerzaON = false;
        estadoMov = ESTADO_MOV::STOP;
        // Creamos una la def y el body  de una linea de ancho infinitesimal.
        // Creamos una la def y el body  de una linea de ancho infinitesimal.
        b2Body* vigaSuelo1, *vigaSuelo2, *vigaSuelo3, *vigaSuelo4, *vigaSuelo5, *vigaSuelo6, *vigaSuelo7, *vigaSuelo8, *vigaSuelo9;
        b2Body* viga1, *viga2, *viga3, *viga4, *viga5, *viga6, *viga7, *viga8;
        float tamanio = 30.0f;
        vigaSuelo1 = crearNuevaViga(b2Vec2(tamanio/2, 0.0f), b2Vec2(tamanio/2, 0.4f), 0, m_world);
        vigaSuelo2 = crearNuevaViga(b2Vec2(0, tamanio/2), b2Vec2(tamanio/2, 0.4f), 90, m_world);
        vigaSuelo3 = crearNuevaViga(b2Vec2(tamanio, tamanio/2), b2Vec2(tamanio/2, 0.4f), 90, m_world);
        vigaSuelo4 = crearNuevaViga(b2Vec2(tamanio/2, tamanio), b2Vec2(tamanio/2, 0.4f), 0, m_world);

        /*
        viga1 = crearNuevaViga(b2Vec2(-5.0f, 5.0f), b2Vec2(3.0f, 0.4f), 45, m_world);
        viga2 = crearNuevaViga(b2Vec2(0.0f, 5.0f), b2Vec2(1.5f, 0.4f), 0, m_world);
        viga3 = crearNuevaViga(b2Vec2(5.0f, 12.0f), b2Vec2(3.0f, 0.4f), 30, m_world);
        viga4 = crearNuevaViga(b2Vec2(8.0f, 15.0f), b2Vec2(1.5f, 0.4f), 0, m_world);
        viga5 = crearNuevaViga(b2Vec2(2.0f, 3.0f), b2Vec2(1.5f, 0.4f), 0, m_world);
        viga6 = crearNuevaViga(b2Vec2(9.0f, 8.0f), b2Vec2(3.0f, 0.4f), 0, m_world);
        viga7 = crearNuevaViga(b2Vec2(-15.0f, 5.0f), b2Vec2(3.0f, 0.4f), 46, m_world);
        viga8 = crearNuevaViga(b2Vec2(-24.0f, 5.0f), b2Vec2(3.0f, 0.4f), 90, m_world);
        */

        //creamos un payload que luego sera un gusano
        gusanos[0] = crearGusano(m_world, 0.0f);
        //gusanos[1] = crearGusano(m_world, 20.0f);

        //gusanos[2] = crearGusano(m_world, 25.0f);
    }

    void Keyboard(int key) override{

        if ( key == GLFW_KEY_I){
            // Movimiento parabolio en y = 0,5m de altura y en e x = 1m.
            float anguloTita = atan(4.0f *0.5f/1.0f);  //  (4 *hmax)/distMaxHorizontal.
            float velocidadInicial = sqrt( 1.0f*10/(sin(2*anguloTita)) ); // el 1.0f hace referencia distancia horizontal de 1.0m;
            float velocidadX = velocidadInicial* cos(anguloTita);
            float velocidadY = velocidadInicial * sin(anguloTita);

            float impulsoX = gusanos[0]->GetMass() * velocidadX;
            float impulsoY = gusanos[0]->GetMass() * velocidadY;
            b2Vec2 impusloAdelante(impulsoX, impulsoY); //  por la gravedad
            gusanos[0]->ApplyLinearImpulse(impusloAdelante, gusanos[0]->GetWorldCenter(), true);
        }
        else if (key == GLFW_KEY_Y){
            // Salto hacia atras retrocede 0,2m en x y arriba se desplaza 1.2m
            float anguloTita = atan(4.0f *1.2f/0.2f);  //  (4 *hmax)/distMaxHorizontal.
            float velocidadInicial = sqrt( 0.2f*10/(sin(2*anguloTita)) ); // el 0.2f hace referencia distancia horizontal de 0.2m;
            float velocidadX = velocidadInicial* cos(anguloTita);
            float velocidadY = velocidadInicial * sin(anguloTita);

            float impulsoX = - gusanos[0]->GetMass() * velocidadX;
            float impulsoY = (gusanos[0]->GetMass() * velocidadY);
            b2Vec2 impusloAdelante(impulsoX, impulsoY); //  por la gravedad
            gusanos[0]->ApplyLinearImpulse(impusloAdelante, gusanos[0]->GetWorldCenter(), true);
        }
        else if (key == GLFW_KEY_K){
            estadoMov = ESTADO_MOV::MOVER_DERECHA;  // le sume 0.3 al rozamiento para considerar tambien el rozamiendo del a viga con el gusano ajuste magico.
            float aceleracion = 2.3 * 10; // aceleracion es la froz = u.N , las masas se cancelan queda mu * g.
            float velocidad = sqrt(2 * aceleracion * 0.2); // la velocidad la sacamos como 2 * aceleracion * distancia.
            float impulso = gusanos[0]->GetMass() * velocidad;
            b2Vec2 impulsoVelocidad(impulso, 0.0f); //  por la gravedad
            gusanos[0]->ApplyLinearImpulse(impulsoVelocidad, gusanos[0]->GetWorldCenter(), true);
        }
        else if (key == GLFW_KEY_H ){
            estadoMov = ESTADO_MOV::MOVER_IZQUIERDA; // NO OLVIDAR FUERZA DE ROZAMIENTO PUTAMADRE
            float aceleracion = 2.3 * 10; // aceleracion es la froz = u.N , las masas se cancelan queda mu * g.
            float velocidad = sqrt(2 * aceleracion * 0.2); // la velocidad la sacamos como 2 * aceleracion * distancia.
            float impulso = gusanos[0]->GetMass() * velocidad;
            b2Vec2 impulsoVelocidad(-impulso, 0.0f); //  por la gravedad
            gusanos[0]->ApplyLinearImpulse(impulsoVelocidad, gusanos[0]->GetWorldCenter(), true);        }
    }

/*
             float aceleracion = 0.2f/0.5f;  // xf = Vo*1m + 0.5*g*t²
            float impulso = gusanos[0]->GetMass() * aceleracion;
            b2Vec2 impulsoVelocidad(impulso, 0.0f); //  por la gravedad
            gusanos[0]->ApplyLinearImpulse(impulsoVelocidad, gusanos[0]->GetWorldCenter(), true);
 */
    void Step(Settings& settings) override{
        Test::Step(settings);
        g_debugDraw.DrawString(5, m_textLine, "Keys: (d) dynamic, (s) static, (k) kinematic");
        m_textLine += m_textIncrement;

        b2Vec2 posicion = gusanos[0]->GetWorldCenter();
        if( posicion.y > maxAlturaY) maxAlturaY = posicion.y;
        if (posicion.x > maxRangoX)  maxRangoX = posicion.x;
        std::string posicionGusano = "X: " + std::to_string(posicion.x)  + " Y: " + std::to_string(posicion.y) + "  Masa: " + std::to_string( gusanos[0]->GetMass() ) + "\n";
        std::string estadisticas = posicionGusano + "MaxAltura Y: " +  std::to_string(maxAlturaY) + "  Max DistX: " + std::to_string(maxRangoX);
        g_debugDraw.DrawString(5, m_textLine, estadisticas.data());
    }

    static Test* Create()
    {
        return new Prueba1;
    }

};

static int testIndex = RegisterTest("Examples", "Prueba 1", Prueba1::Create);
