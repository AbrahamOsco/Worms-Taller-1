#include <iostream>
#include <box2d/b2_math.h>
#include <box2d/box2d.h>
#include <box2d/b2_body.h>
#include <box2d/b2_time_of_impact.h>
#include <box2d/b2_distance.h>
#include <iomanip>
#include <algorithm>
#include <map>
#include "src/Modelo/Gusano.h"
#include "src/server_queue.h"
#include "string"


int main(int argc, char* argv[]) {
    Gusano gusano(Posicion(20, 20), 0.2f, 1.0f, 300);
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);
    b2BodyDef bodyGusDef;
    bodyGusDef.fixedRotation = true; // Impedimos que el gusano gire. solo  podra gira a izq a derecha a mano.
    bodyGusDef.type = b2_dynamicBody;
    bodyGusDef.position.Set(20.0f, 20.0f);
    world.CreateBody(&bodyGusDef);
}

