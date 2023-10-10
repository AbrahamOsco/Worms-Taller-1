#include <iostream>
#include <box2d/b2_math.h>
#include <box2d/box2d.h>
#include <box2d/b2_body.h>
#include <box2d/b2_time_of_impact.h>
#include <box2d/b2_distance.h>
#include <iomanip>
#include <algorithm>


// GUIA DE BOX2D .
class MyActor{
private:
    size_t id;
    std::string nombre;
    b2Body* body;  // No queda de otra deben ser punteros box2D
public:
    MyActor(const size_t &unId, const std::string &unNombre)
            : id(unId), nombre(unNombre), body(nullptr) {};

    void setBody(b2Body* unBody){
        body = unBody;
    }

    size_t getId(){
        return id;
    }
    std::string getNombre(){
        return nombre;
    }
};

class FixtureData{
public:
    FixtureData(){}

};
// Las articulaciones y los elementos fijos se destruyen cuando se destruye el cuerpo asociado. Implemente este oyente para que pueda anular
// las referencias a estas uniones y formas.
class MyDestructionListener : public b2DestructionListener{
    virtual void SayGoodbye(b2Joint* joint){

    }

    virtual void SayGoodbye(b2Fixture* fixture){

    }
};



void tutoBox2DParte1(){
    b2Vec2 gravity(0.0f, -10.0f);       //  1) Definimos el vector de gravedad. (en X, en Y) ojo q el signo (-) indica q apunta hacia abajo.
    b2World world(gravity);             //  Creamos un mundo, BOX2D implementa los cuerpos rigidios y estos tienen 3 tipos : staticBODY, kinematicBOdy, dinamicBody
    /* Cuerpos Dinámicos (b2_dynamicBody): Estos cuerpos pueden moverse y responder a fuerzas. Tienen una masa positiva y la simulación de física
    afectará su movimiento en función de las fuerzas aplicadas y su inercia.*/

    // Para crear un cuerpo ESTATICO Necesitamos primero la definicion de un cuerpo: mantiene la data necesaria
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f); // Le seteamos la posicion (coordX, coordY)
    b2Body* groundBody = world.CreateBody(&groundBodyDef);  //  2) Pasamos una ref del defBody al objeto world para crear un cuerpo rigido.

    //  3) Definimos fixures como forma, friccion, densidad, etc. En este caso  hacemos un shape.
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    // 4)Le damos forma de caja centrada en el cuerpo original, le pasamos siempre la MITAD de ancho y alto. ( anchoFinal = 100m, hFinal = 20m) en MKS centrada en el (0,0)

    groundBody->CreateFixture(&groundBox, 0.0f);
    // Ahora al cuerpo ( lo q nos escupe el world) se le setea el fixture shape y densidad 0. (Por q esto es un cuerpo estatico, y los cuerpos estaticos no tienen masa por def.
    // por q estos simulan el suelo o paredes de un juego y no interactuan con fuerzas.
    //  Cada fixture debe tener un padre body. (podes enchufarle todos los fixture al body).
    //  Cuando el cuerpo se mueva (groundBody tambien se movera la forma (shape) la transformacion del fixture se hereda del body principal.
    //  No se mueve/modifica una forma sobre un cuerpo, el groundBody es un cuerpo rigidio y se sigue sus leyes.

    // Creamos ahora un cuerpo dinamico que interactuara con las fuerzas.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;  //  Le seteamos el tipo a dynamicBody, para q el cuerpo se mueva en respuesta a fuerzas.
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body* bodyDinamico = world.CreateBody(&bodyDef);

    // Creamos un fixture shape para el bodyDinamic con forma de caja
    b2PolygonShape formaCaja;
    formaCaja.SetAsBox(1.0f, 1.0f);  // Se crea una caja de 2m de ancho, 2 m alto y centrada en el (0,0)
    // Creamos un fixture def y le seteamos la forma, densidad y friccion
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &formaCaja;
    fixtureDef.density = 1.0f; // Un cuerpo dinamico debe tener almenos un fixture con densidad !=0.
    fixtureDef.friction = 0.3f;
    bodyDinamico->CreateFixture(&fixtureDef); // Podemos agregar tantos fixture como quieras al cuerpo, cada uno contribuye a su masa total.

    float timeStep = 1.0f / 60.0f; //  Eligimos un paso del tiempo para box2D  va de la mano con el frameRate del gameLoop.
    // Existe una entidad Solucionar de restricciones (SDR) resuelve todas las restricciones  ->se debe iterar sobre todas las restricciones varias veces.
    //  hay dos fases en el SDR:  una fase de velocidad y una fase de posicion cada fase tiene su recuento de iteraciones. Iteracion del SDR paso unico sobre todas las restricciones.
    int velocityIter = 6;
    int positiIter = 2;
    for(int i = 0; i < 60; i++){
        world.Step(timeStep, velocityIter, positiIter);
        b2Vec2 posicion = bodyDinamico->GetPosition(); // Obtenemos la posicion de un Body
        float angle = bodyDinamico->GetAngle();  // da en agulo en readianes: 3,41, 4.30  // ej ->3.14 = 180º
        std::cout << std::fixed << std::setprecision(2); // fixed para asegurar notacion decimal y setPrecision printeamoas 2 decimales.
        std::cout <<  " ( " << posicion.x << ", " << posicion.y << ", " << angle << ")\n";
    }
};

void tutoBox2DParte2(){
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);
    // Creamos la forma de un circulo
    b2CircleShape circleShape;
    circleShape.m_p.Set(2.0f, 3.0f); // centro de la forma circular en las coordenadas (2, 3)
    circleShape.m_radius = 0.5f;
    //  Formas poligonales los atributos son publicos,  podemos crear el poligono pasandole un array de vertices. max-defaul es 8; Son todos solidos nunca huecos  3 o mas vertices.
    int cantVertices = 3;
    b2Vec2 vertices[cantVertices]; // Cada vertice es representando por un b2Vec2
    vertices[0].Set(0.0f, 0.0f);
    vertices[1].Set(1.0f, 0.0f);
    vertices[2].Set(0.0f, 1.0f);
    b2PolygonShape polygon;  //  creamos la forma de un poligono
    polygon.Set(vertices, cantVertices); // Insertamos el array la cantidad de vertices.
    // Usamos las formas poligonales para modelar, obstaculos, terrenos irregulares, personajes de juego.
    // EL ULTIMO vertice que definamos se va a conectar automaticamente con el priemr vertice para fomrar una envolvente convexa.
    b2PolygonShape boxShape;
    boxShape.SetAsBox(2.0f, 3.0f, b2Vec2(5.0f, 6.0f), 45.0f * (b2_pi /180.0f) ); // todos los angulos en BOX2D son en RADIANES Y NO GRADOS.
    // Creamos una caja de 4m de ancho, 6 m de alto centrado  en x = 5m e y = 6m y rotada 45º
    boxShape.m_radius = 3.0;
    // Piel de poligono, radio q cree una piel alrededor del poligono, podemos establecer radio y si es mayor a cero ,la figura se esnacha y las colisiones, se detectaran antes
    // que los vertices de la forma entren en contacto. (generando una colision mas suave).

    // Formas de borde: Son segementos de linea, o bordes SON RECTOS SIEMPRE, son unidimensionales, solo tienen longitud, no tienen volumen, ancho = 0.
    // Util para representar, paredes, suelo,etc. Chochan con otros ciruclos y poligonos pero no con otras formas de borde (no tienen volumen)
    // Cuidado con las colisiones fantasmas, poligono choca con un vertice interno formando una colision normal.
    b2Vec2 unVer0(1.7f, 0.0f);
    b2Vec2 unVer1(1.0f, 0.25f);
    b2Vec2 unVer2(0.0f, 0.0f);
    b2Vec2 unVer3(-1.7f, 0.4f);

    b2EdgeShape otroBorde;
    // Este metodo es para una secuencia de vertice q forma una unica direccion, nos da un mov suave, colision unilateral, solo se detecta colisiones en una direccion especifica.
    otroBorde.SetOneSided(unVer0, unVer1, unVer2, unVer3); // normal del borde apunta a la derecha de v1 hasta v2
    otroBorde.SetTwoSided(unVer1, unVer2);  //  borde aislado, colission bidireccional, no hay mov suave.

    // FORMAS  DE CADENA: Sirve para representar objetos lineales pero estos pueden tener curvas, y segementos interconectados.
    // Colisiones bilaterales: un objeto puede interactuar con una forma de cadena tanto en el exterior como el interiro de la cadena.
    // Podemos crear formas de cadena aislada: (Es decir no estan conectados para formar una forma cerrada o continua).
    b2Vec2 verticesFC[4];
    verticesFC[0].Set(1.7f, 0.0f);
    verticesFC[1].Set(1.0f, 0.25f);
    verticesFC[2].Set(0.0f, 0.0f);
    verticesFC[3].Set(-1.7f, 0.4f);
    b2ChainShape formaCadena;
    formaCadena.CreateChain(verticesFC, 4, verticesFC[3], verticesFC[0]); // vertices, cantidad, vertice previo para conectarse al start, sgt vertice de la cadena q conecta al final.
    b2ChainShape fcLoopChain; // Nos conecta el ultimo vertice al primero de forma automatica.
    fcLoopChain.CreateLoop(verticesFC, 4);
    // Podemos visitar a cada uno de los hijos (por su indice), asi obtenemos el segemento individual en el indice i
    // y almacenarlo en la variable edge. Luego se puede realizar operaciones, en este segmento individual.
    for (int i = 0; i < fcLoopChain.GetChildCount(); ++i){
        b2EdgeShape edge; // Se utiliza cada para representar cada uno de los segementos de linea individuales. (hijos) de la cadena cerrada.
        fcLoopChain.GetChildEdge(&edge, i);
    }
    // Primer segmento de linea con indice:  i = 0 , conectara verticesFC[0] con verticesFC[1]
    // Primer segmento de linea con indice: i = 1 , conectara verticesFC[1] con verticesFC[2]
    // Primer segmento de linea con indice: i = 2 , conectara verticesFC[2] con verticesFC[3]
    // Primer segmento de linea con indice: i = 3 , conectara verticesFC[3] con verticesFC[0]
}

void tutoBox2DParte3(){
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);
    // Unary Geometric Queue : consultas geomtricas como si un punto esta dentro de una forma, si dos formas se superponen,etc.
    // Share point test: si un punto del world esta dentro de una forma dada.
    b2PolygonShape unaFormaRect;   // Creamos una forma rectangulo. centrada en el origen
    unaFormaRect.SetAsBox(50.0f, 10.0f);

    b2Transform transform; // creamos una transformacion para la consulta representa la pos, orientacion y escala.
    transform.SetIdentity();    // para q la forma no tenga ninguna transformacion adicional y se encuentra en su pos oriignal en el mundo.
    b2Vec2 point(5.0f, 2.0f);  //  defnimos el punto para probar si esta dentro de una forma.
    bool hit = unaFormaRect.TestPoint(transform, point); // unaFormRect: forma para probar, point: punto a verificar, shape:transformacion
    if(hit){
        std::cout << "El punto (5,2) esta dentro de la forma del rectangulo\n";
    }
    // retorna true si point esta dentro de unaFormaRect, false sino.
    // Cuando se quiere chequear si un punto esta en una Forma de borde o Forma de cadena devolvera siempre false.

    //  SHAPE RAY CASTING: Tenica donde se lanza un rayod desde un input.p1 hasta un input.p2 y determina si esta rayo intersecta con unaForma. Si lo hay obtendremos
    //  informacion sobre el punto de interseccion y el vector normal en el punto de interseccion.
    b2Transform otraTransform; //  creo una trasnformacion
    transform.SetIdentity();  //  le seteo la identidad
    b2RayCastInput input;       //  creo RayCast
    input.p1.Set(0.0f, 0.0f);   // punto de inicio
    input.p2.Set(1.0f, 0.0f);   // punto de destino del rayo.
    input.maxFraction = 1.0f;   // se establece en 1.0f -> signif q se rastreara hasta el pto de partida no importa la distancia. (dist max a la q se rastreara el rayo).
    int childIndex = 0;        // para las formas de cadenas el indice del hijo.
    b2RayCastOutput output;
    bool otroHit = unaFormaRect.RayCast(&output, input, transform, childIndex);
    if (otroHit){   // Si retorna true entonces el rayo intersecto la forma y se puede obtener info de la interseccion.
        b2Vec2 hitPoint = input.p1 + output.fraction * (input.p2 - input.p1); // sobrecargo e operador resta y * :O
        std::cout << "rayo intersecta con la forma rectangular\n";
    }
}

void tutoBox2DParte4(){
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);
    // FUNCIONES BINARIAS: Funciones q toman un par de formas y calcula un resultado.
    // son superposicion, colectadores de contacto, distancia, momento de impacto.
    b2PolygonShape formaRect; //Creo una forma rectangular
    formaRect.SetAsBox(1.0f, 1.0f);

    b2ChainShape formaCadena;
    b2Vec2 vertices[4] = { b2Vec2(3.0f, -3.0f), b2Vec2(8.0f, 5.30f) , b2Vec2(12.0f, 2.30f) , b2Vec2(18.0f, 25.0f)};
    formaCadena.CreateLoop(vertices, 4);

    b2Transform xfa, xfb; // Necesarias para ver si existe suerposicion.
    xfa.SetIdentity(); // formas estan su posicion y orientacion determinadas.
    xfb.SetIdentity();

    bool bSuperposcion = b2TestOverlap(&formaRect, 0, &formaCadena, 1, xfa, xfb);
    //  le pasamos la forma rectangular y  el indice 0 :por q no tiene hijos y queremos referinos a la unica forma rectan de ese cuerpo.
    //  En el caso de la cadena si tenemos multiples hijos ( en este caso tenemos 4 hijos el indice va de 0 a 3). seleccionamos el segundo segmenento de la cadena.
    // nos retorna un bool true si hubo suerposicon, false sino.
    if(bSuperposcion){
        std::cout << "Correcto  la forma  rectangular y la forma de cadena se superonen\n";
    }

    // Colectores de contactos ( Contact Manifolds)
    //  CIRCULO - CIRCULO | CIRCULO-POLIGONO | : 1 solo punto de contacto y una unica normal
    //  POLIGONO -POLIGONO | : Podemos obtener 2 puntos, comparten la misma normal.

    b2PolygonShape formaPrueba1;
    formaPrueba1.SetAsBox(1, 1, b2Vec2(3,3), 0); // EN EL Plano cartesiano creo en el 3,3 un rectangulo de vertices (3,3), (4,3), (3,2), (4,2);
    //  Creo la forma de circulo
    b2CircleShape unCirculo;
    unCirculo.m_p.Set(20.0f, 20.0f); // creo un circulo centrado en X=5, Y=5
    unCirculo.m_radius = 1.0f;     // de radio 1.

    b2Manifold unManiFold, otroManiFold;   // Estructura para almacenar informacion informacion de los puntos de contactos, incluye un vector normal y hasta 2 ptos de contacto.
    b2WorldManifold worldManifold; // para trabajar en puntos de contacto con coordenadas mundiales
    //  Creo la forma rectangulo
    worldManifold.Initialize(&unManiFold, xfa, formaPrueba1.m_radius, xfb, unCirculo.m_radius);
    for(int i = 0; i < unManiFold.pointCount; i ++){
        b2Vec2 point = worldManifold.points[i];
        //  esto no imprimira nada obvio por q falta definir los defCuerpos, cuerpos y realizar el mov (simulacion fisica) luego lo probaremos.
        std::cout << "Punto de contacto " << i << ": x=" << point.x << ", y=" << point.y << std::endl; // no imprimira esto por lo de arriba.
    }
    // Podemos agregar o quitar puntos durante la simulacion lo detectamos usando b2GetPointsStates.
    b2PointState state1[2], state2[2];  //  Usado para deteminar el estado de los puntos de contacto.
    b2GetPointStates(state1, state2, &unManiFold, &otroManiFold);  //  verifiicamos si se agrego o elimino ptos de cntacto en los manifolds en un paso de simulacion.
    // luego de invocar el b2GetPoints.. examinamos los estados de los puntos si se ha producido algun cambio en los ptos de contacto.
    if( state1[0] == b2_removeState){
        // Significa q el primer punto de contacto se ha eliminado en el paso de la simulacion actual.
        // process eventos o realizamos acciones.
    }
    // Distancia: (Distance)  : Se usa para calcular la distancia mas corta entre dos formas (shapes) para utilizar esta funcion ambas formas deben convertirse en
    //  b2DistanceProx.
    b2DistanceProxy distProx1, distProx2;   //Necesitamos include  #include <box2d/b2_distance.h>
    distProx1.Set(&formaPrueba1, 0);  //  Segundo argumento es el indice de la forma como no tiene indice le ponemos 0 al rectangulo
    distProx2.Set(&unCirculo, 0);
    b2SimplexCache cache;
    cache.count = 0;
    b2DistanceInput inputDist;
    inputDist.proxyA = distProx1;
    inputDist.proxyB = distProx2;
    inputDist.transformA = xfa;
    inputDist.transformB = xfb;
    b2DistanceOutput outputDist;
    b2Distance(&outputDist, &cache, &inputDist); // calcula la distancia entre las formas admite cualquier combinacion CircleShape,PolygonSHape,EdgeShape.
    std::cout << "Distancia : "  << outputDist.distance;  // Su distancia es raiz de 2 = 1,414

    //  Time of impact: (TOI)  tiempo en q dos OBJETOS colisionaran en el futuro debido a sus movimientos acutales util para prevenir tuneling.
    b2BodyDef defCuerpo1, defCuerpo2;
    defCuerpo1.type = b2_dynamicBody;
    defCuerpo2.type = b2_dynamicBody;

    b2Body* cuerpo1 = world.CreateBody(&defCuerpo1);
    cuerpo1->CreateFixture(&formaRect, 1.0);

    b2Body* cuerpo2 = world.CreateBody(&defCuerpo2);
    cuerpo2->CreateFixture(&unCirculo, 1.0);

    b2TOIInput toiInput;  // para usarlo incluir :  #include <box2d/b2_time_of_impact.h>
    toiInput.proxyA.Set(cuerpo1->GetFixtureList()->GetShape(), 0);
    toiInput.proxyB.Set(cuerpo2->GetFixtureList()->GetShape(), 0);

    toiInput.sweepA.c0 = cuerpo1->GetTransform().p; // Posición inicial del cuerpo 1;
    toiInput.sweepA.c = cuerpo1->GetTransform().p;   // Posicion actual del cuerpo 1;
    toiInput.sweepA.a0 = cuerpo1->GetTransform().q.GetAngle();  // Ángulo inicial del cuerpo 1
    toiInput.sweepA.a = cuerpo1->GetTransform().q.GetAngle();  // Ángulo actual del cuerpo 1

    toiInput.sweepB.c0 = cuerpo2->GetTransform().p; // Posición inicial del cuerpo 2
    toiInput.sweepB.c = cuerpo2->GetTransform().p;   // Posicion actual del cuerpo 2;
    toiInput.sweepB.a0 = cuerpo2->GetTransform().q.GetAngle();  // Ángulo inicial del cuerpo 2
    toiInput.sweepB.a = cuerpo2->GetTransform().q.GetAngle();  // Ángulo actual del cuerpo 2

    toiInput.tMax = 1.0f; // Valor máximo para buscar el TOI (1.0 significa un paso completo de simulación)
    b2TOIOutput outputTOI;
    b2TimeOfImpact(&outputTOI, &toiInput);
    std::cout << "El tiempo de impacto es : " << outputTOI.t <<std::endl;
}

void tutoBox2DParte5(){
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    b2BodyDef defBody1;
    defBody1.type = b2_dynamicBody;
    // Existen tres tipos de cuerpo estatico (ej: paredes, suelo) , cinematico (como los elevadore de mario bros 1) , dinamico ( ej el gusano se mueve y choca con todo).
    // No crear un cuerpo en el origen mundial y luego moverlo. inicializar la posicion al crear el cuerpo.
    defBody1.position.Set(10.0f, 12.0f);
    // Cuerpo tiene 2 ptos importantes, 1) el de origen del cuerpo - fixtures y joints estan unidos a ese cuerpo
    // 2) Es el centro de masa se determina apartir de la distribucion de la masa Si cambias las prop de masa el centro de masa cambia.

    //  Amortiguacion para reduir la velocidad de los cuerpos. se usan entre 0 y 0.1 normalemnte. 0: Sin amortgiuacion, (no lo usa el creadro cuerpos parecen "flotar"
    defBody1.linearDamping = 0.0f;
    defBody1.angularDamping = 0.01f; // Amortiguacion aprox para estabilidad y rendimiento.
    defBody1.gravityScale = 0.0f; // Ajustamos la gravedad de un solo cuerpo , ojo aca el cuerpo flotara.

    // Parametros del sueño (sleep parameters) : Es caro simular cuerpos, mientras menos mejor, Box2D detecta q  un cuerpo o grupo de cuerpo se ha detenido, entra
    // en un estado de suspension. poca sobrecarga del CPU, si un cuerpo despierta choca con un cuerpo dormido, el dormido se despierta, tambien se despierta si se
    //  destruye una articulacion o un contacto adherido a ello.
    defBody1.allowSleep = true;
    defBody1.awake = true;

    // Rotacion fija: EJ UN personaje debe tener una rotacion fija, un cuerpo de este tipo no deberia girar, ni siquiera bajo carga,
    defBody1.fixedRotation = true;  // Inercia rotacional y su inversa sean cero.

    //  Balas: en el caso q un cuerpo vaya a velocidades altas es posible q el cuerpo pase atraves de otro (por ej un cuerpo estatico) (Efecto tunel).
    // Las balas realizaran CCD ( Dteccion de colisiones continua ->esto evita el efecto tunnel a traves de cuerpos estaticos) por lo tanto hay q añadirle :
    defBody1.bullet = true; // true si se movera muy rapido como una bala.

    // ACTIVACION: Podemos crear un cuerpo q no particione en colisiones o en dinamicas,
    // No se colocara en FASE AMPLIA: q el cuerpo no participara en colisiones, proyecciones de rayo,
    defBody1.enabled = true;
    // Si hay articulaciones (joints) conectadas a cuerpos inactivos, estas uniones no seran simuladas pueden deformarse los joints.
    // No usar la activacion para mundos de transmision.

    // Datos del usuario:
    // Brinda un gancho (hook) para vincular los objetos de su aplicacion a los cuerpos. Debe ser coherente al utilizar el mismo tipo de objeto para todos
    // los datos del usuario corporal.
    MyActor unActor(1, "Hola soy un body este es un string");
    b2Body* body = world.CreateBody(&defBody1);
    body->GetUserData().pointer = (uintptr_t) &unActor;
    MyActor* otroActor = (MyActor*) body->GetUserData().pointer;
    std:: cout << otroActor->getNombre() << " --- " << otroActor->getId() << "\n";
}

void tutoBox2DParte6(){
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);
    b2BodyDef defBody1;
    b2Body* unBody =  world.CreateBody(&defBody1); // Nunca usar new para crear un cuerpo, el mundo no sabra sobre el cuerpo y el cuerpo no se inicializara correctamente.
    // Bodys se crean y se destruyen usando el b2World SIEMPRE
    world.DestroyBody(unBody); // Cuando se destruye un cuerpo los fixtures y joints se destruyen automaticamente.
    //  Datos masivos:
    // un cuerpo Tiene masa (Escalar) , centro de masa ( dos vectores) , inercia rotacional (escalar)
    // Cuerpos estaticos:  Masa e inercia son cero.; Cuerpo con rotacion fija, su inercia rotacional es cero.
    // Masa se establece cuando se añade fixtures al cuerpo.  Podemos setear la masa en tiempo de ejecucion:
    b2MassData unObjetoMasa;
    unObjetoMasa.mass = 30; // Seteo una nueva masa
    unBody->SetMassData(&unObjetoMasa);  // le asignamos.
    // Reseteamos la masa por default con .
    unBody->ResetMassData();
    float unaMasaFloat = unBody->GetMass();  // Obtenemos la masa de un cuerpo
    std:: cout << "masa Actual " << unaMasaFloat << std::endl;
    float unaInercia = unBody->GetInertia(); // Obtenemos la inercia
    std:: cout << "inercia Actual " << unaInercia << std::endl;
    b2Vec2 posCentroMasa = unBody->GetLocalCenter(); //  obtenemos la posicion local del centro de masa.
    unBody->GetMassData(&unObjetoMasa); // otra manera de obtener datos de la masa pasandole un objeto por referencia.

    // Informacion estatal.

    //Set y get del tipo de cuerpo (body):
    unBody->SetType(b2_kinematicBody);
    b2BodyType unTipoBody =  unBody->GetType();


    // Setear si es de tipo bala o chequear si es de tipo bala.
    unBody->SetBullet(false);
    bool esBullet = unBody->IsBullet();

    // Setear su estado dormido o ver si esta dormido.
    unBody->SetSleepingAllowed(false);
    bool estaDormido =  unBody->IsSleepingAllowed();

    // Setear si esta despierto o chequear si esta despierto.
    unBody->SetAwake(true);
    bool estaDespierto = unBody->IsAwake();

    //  Setear su actividad o chequear si esta activo:
    unBody->SetEnabled(true);
    bool estaActivo = unBody->IsEnabled();

    unBody->SetFixedRotation(true);
    bool fixedRotation =  unBody->IsFixedRotation();

    // Accedemos a la posicion y rotacion de un cuerpo:

    unBody->SetTransform(b2Vec2(30.0f,30.0f), 45.0f* (b2_pi/180.0f) );
    // Trabajamos gran parte con la transformacion del cuerpo:  su posicion y su angulo.
    b2Transform unaTransform = unBody->GetTransform();
    b2Vec2 unaPosition = unBody->GetPosition();
    float unAngle = unBody->GetAngle();
    std:: cout << "un Angle" << unAngle << std::endl;

    // Obtenemos coordenadas  Locales y mundiales:
    b2Vec2 coordLocal = unBody->GetLocalCenter();  // pos local del centro de masa
    b2Vec2 coordMundial = unBody->GetWorldCenter();  // Posciion mundial del centro de masa
    b2Vec2 veloLineal = unBody->GetLinearVelocity(); // Obtenemos la velocidad lineal;
    float velocAngular = unBody->GetAngularVelocity(); // Obtenemos la velocidad angular;
}

void tutoBox2DParte7(){
    //Creacion de fixtures;
    b2Vec2 gravity;
    b2World world(gravity);

    b2BodyDef unaDefBody;
    b2Body* unBody1 =  world.CreateBody(&unaDefBody);

    b2CircleShape circuloShape;
    circuloShape.m_p.Set(4.0f, 8.0f);
    circuloShape.m_radius = 3.0f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circuloShape;
    fixtureDef.density = 1.0f;
    b2Fixture* unFixture = unBody1->CreateFixture(&fixtureDef);
    // Creamos el fixture y lo fijamos al cuerpo Puedes crear multiples fixtures en un solo body. se pueede destruir a mano tambien el fixture
    unBody1->DestroyFixture(unFixture);  // dejar q la destruccion del body se encargue de destruir todos los fixtures. (Recomendado),
    // Generalmente debes usar densidades similares para todos tus objetos tus fixtures,  Puede ser zero o positivo.
    unFixture->SetDensity(5.0f);
    unBody1->ResetMassData(); // La masa de un cuerpo no se ajusta cuando se establece la densidad hay q llamar a ResetMassData(). OJO NO OLVIDAR.

    // Friccion: BOX2D admite friccion estatica y dinamica. se utiliza el mismo parametro para ambas. va entre 0 y 1 generalmente, puede ser mayor a 1
    // y no debe ser negativo.  con 0: Desactivamos la friccion , 1 : la fortalecemos
    float friccion = sqrtf(unFixture->GetFriction() * unFixture->GetFriction());
    // si un fixture tiene friccion cero, el contacto tendra friccion Cero.  Anular friccion mixta con b2Contact::SetFriction

    // Restitucion: se establece entre 0 y 1 .Ej pelota si la tiras y no rebota es choque inelastico tiene restitucion = 0.
    // si la tiras y refleja (rebota) exactamente es choque perfectamente elastico tiene restitucion = 1.
    float restitucion = b2Max(unFixture->GetRestitution(), unFixture->GetRestitution());

    // Filtracion:
    // filtrado de colisiones permite evitar colisiones entre dispositvos. Por ej creas un personaje q anda en bici queres q la bici y el personaje choquen con el terreno
    // y no queres que el personaje choque con la bicicleta.
    // Box2D Admite filtrado de categoria  y de grupo: Por ej podrian no colisionar los jugadores entre si, no colosionar los moustros entre si, pero si colisionan
    // los moustros y los jugadores.
    /*
    playerFixtureDef.filter.categoryBits = 0x0002;
    monsterFixtureDef.filter.categoryBits = 0x0004;
    playerFixtureDef.filter.maskBits = 0x0004;
    monsterFixtureDef.filter.maskBits = 0x0002;
    uint16 catA = fixtureA.filter.categoryBits;
    uint16 maskA = fixtureA.filter.maskBits;
    uint16 catB = fixtureB.filter.categoryBits;
    uint16 maskB = fixtureB.filter.maskBits;
    if ((catA & maskB) != 0 && (catB & maskA) != 0){
        // fixtures can collide
    }
    */

    // Otra manera de hacerlo es por grupo:
    //  fixture1Def.filter.groupIndex = 2; // fixtures con el mismo indice de grupo (positivo) colisionan
    //  fixture2Def.filter.groupIndex = 2;
    //  fixture3Def.filter.groupIndex = -8; // fixtures con el mismo indice (en negativo) NO colisionan.
    //  fixture4Def.filter.groupIndex = -8;
}

void tutoBox2DParte8(){
    //  Joints : Se utiliza para limitar el movimiento de los cuerpos en un mundo simulado. Permite un rango de movimientos, se puede usar para controlar la posicion
    //  controlar la posicion especificando la velocidad del joint que sea proporcional a posic real y la deseada. Los joints conectan dos cuerpos diferentes.
    //  Joints entre cuerpo estatico y cinematicos esta permitido pero no tiene efecto en la simulacion.
    //  Los cuerpos conectados no colisionan entre si, usar el flag collideConnect para permitir colision.
    //  Joints se definen requieren datos geometricos, por ej requiere un punto de anclaje q estan fijados a los cuerpos conectados.
    //  Primero creamos la def de un join
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);
    b2BodyDef defBody1, defBody2;
    b2Body* body1 = world.CreateBody(&defBody1);
    b2Body* body2 = world.CreateBody(&defBody2);

    b2RevoluteJointDef joinDef; // Necesitamos crear la definicion de joint para luego crear un Join.
    joinDef.bodyA = body1;
    joinDef.bodyB = body2;
    joinDef.localAnchorA = body1->GetLocalCenter();
    joinDef.localAnchorB = body2->GetLocalCenter();
    b2RevoluteJoint* joint = (b2RevoluteJoint*) world.CreateJoint(&joinDef);

    //world.DestroyJoint(joint); // Destruimos el join a mnao
    //joint = NULL; // Para evitar el acceso accidental a una variable
    // Los joints se destruyen cuando se destruye un cuerpo adherido.
    b2Body* bodyA = joint->GetBodyA();  //obtenemos los cuerpos a partir del joint
    b2Body* bodyB = joint->GetBodyB();
    b2Vec2 anchorA = joint->GetAnchorA();
    b2Vec2 anchorB = joint->GetAnchorB();
    joint->GetUserData(); // Podems obtener data del usuario apartir del joint

    //joint->GetReactionForce();  Fuerza de reaccion
    //joint->GetReactionTorque(1);  el  torque.
    b2DistanceJointDef jointDef;
    jointDef.Initialize(bodyA, bodyB, bodyA->GetWorldCenter(), bodyB->GetWorldCenter());
    jointDef.collideConnected = true;

    //  Junta de revolucion: Una ARTICULACION obliga a dos cuerpos a compartir un punto de anclaje comun, llamado un punto de articulacion.
    //  la articulacion de revolucion tiene un unico grado de libertad: la rotacion relativa de los dos cuerpos. Esto se llama angulo articular.
    b2RevoluteJointDef jointDefRev;
    jointDefRev.Initialize(body1, body2, body1->GetWorldCenter());
    jointDefRev.lowerAngle = -0.5f * b2_pi; // -90 degrees
    jointDefRev.upperAngle = 0.25f * b2_pi; // 45 degrees
    jointDefRev.enableLimit = true;
    jointDefRev.maxMotorTorque = 10.0f;
    jointDefRev.motorSpeed = 0.0f;
    jointDefRev.enableMotor = true;

    // POdemos acceder al angulo, velocidad y el torque de un joints
    joint->GetJointAngle();
    joint->GetJointSpeed();
    joint->GetMotorTorque(1);
    //
    joint->SetMaxMotorTorque(3000); //
    // podemos actualizar la velocidad de la  articulacion  en cada paso.
    //... Game Loop Begin ...
    joint->SetMotorSpeed(cosf(0.5f * 1));; // por itempo en lugar de uno
    //... Game Loop End ...

}
class MyContactListener : public b2ContactListener{
public:

    // Se llama cuando dos objetos comienzan a sueperponerse.
    virtual void BeginContact(b2Contact* contact) override {

    }

    // Se llama cuando dos objetos dejan de sueperponerse.
    virtual void EndContact(b2Contact* contact) override {
        //
    }

    // Se llama deespues de detectar la colision . pero antes de la resolucion de la colision previo
    // buen luga rpara deteminar el estado del punto y la velocid de aprox de la colisiones.
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override {
        b2WorldManifold worldManifold;
        contact->GetWorldManifold(&worldManifold);
        b2PointState stateAntesChoq[2], stateDspChoq[2]; // Arreglo para almacenar estado de los ptos de contacto antes y dsp de la colision
        b2GetPointStates(stateAntesChoq, stateDspChoq, oldManifold, contact->GetManifold()); // se obtiene la info y se guarda en los states anteriores.
        if (stateDspChoq[0] == b2_addState ){ // cheqo si el 1er pto de contacto  dsp choq se agrego durante la resolucion de la colsiion ( b2_addState indica eso )
            const b2Body* bodyA = contact->GetFixtureA()->GetBody();   // se obtienen los bodys apartir del punto de contacto
            const b2Body* bodyB = contact->GetFixtureB()->GetBody();
            b2Vec2 point = worldManifold.points[0];  // se obtiene el 1er punto de contacto en coordenadas mundiales
            b2Vec2 vA = bodyA->GetLinearVelocityFromWorldPoint(point);  // se obtienen las velocidades lineales en el pto de contacto utilizado point
            b2Vec2 vB = bodyB->GetLinearVelocityFromWorldPoint(point);
            float approachVelocity = b2Dot(vB - vA, worldManifold.normal);  // se obtiene la velocidad al hacer el P.I entre diferencia de las velocidad y la normal.
            if (approachVelocity > 1.0f){  // si la velocidad es mayor a 1 (es lo suficiente signficativa)  haemos un sonidod.
                // Hago sonar un sonidito.
            }
        }
    }

    // Se llama deespues de detectar la colision . pero despues de la resolucion de la colision
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override {
        //
    }

};

void tutoBox2DParte9(){
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);
    b2BodyDef defBody1, defBody2;
    b2Body* body1 = world.CreateBody(&defBody1);
    b2Body* body2 = world.CreateBody(&defBody2);
    // Contactos : No son creados por el usuario , se puede acceder a la clase contacto e interactuar con ella.
    // Podemos interactuar con la clase contacto usando el colector de contactos (En el Contacto entre 2 poligonos convexoss se generan hasta 2 contactos).
    // Funcion auxiliar para obtener b2WorldManifold: // Sensores no crean contactos: //  bool tocando = sensorContac->IsTouching();
    b2Manifold unManiFold;// Estructura para almacenar informacion informacion de los puntos de contactos, incluye un vector normal y hasta 2 ptos de contacto.
    b2WorldManifold worldManifold; // Se crea para calcular y almacenar informacion sobre la colision en coordenadas mundiales.
    b2Contact* contact;
    contact->GetWorldManifold(&worldManifold); // calcula informa y guarda en worldManifold como la normal y los ptos de contacto en coord mundiales.

    //for (int i = 0; i < worldManifold.points ; ++i) {
    //    b2Vec2 point = worldManifold.points[i];  }        // Haz algo con el punto de contacto en coordenadas mundiales.
    b2Vec2 normal = worldManifold.normal; // También puedes obtener la normal del contacto.

    for(b2Contact* c = world.GetContactList(); c; c = c->GetNext()){ // Accedemos a todos los contactos del WORLD:
        // Procesamos cada contacto.
    }
    for(b2ContactEdge* ce = body1->GetContactList(); ce; ce = ce->next){ // iterar sobre todos los contactos de un cuerpo:
        b2Contact* c = ce->contact;
        // PROCESO el contacto.
    }

    // posible q en estos fors se pierdan contactos transitorios, que ocurren en la mitad del paso del tiempo, utilice b2ContactListener.

    // DEBEMOS implementar una clase b2ContactListener con metodos de inicio, fin, resolucion previa, resolucion posterior
    // Ejemplo de codigo donde se buscan los contacots en el mundo y el cuerpo q tiene menos masa en el choque  desaparecera.

    int maxBodyDestr = 4;
    int bodysDestrActuales = 0;
    b2Body* bodysParaDestruir[maxBodyDestr];
    for(b2Contact* c = world.GetContactList(); c; c = c->GetNext()){ // Accedemos a todos los contactos del WORLD:
        b2Body* bodyA = c->GetFixtureA()->GetBody(); // puedo obtener el cuerpo en un contacto atraves del fixture.
        b2Body* bodyB = c->GetFixtureB()->GetBody(); // puedo obtener el cuerpo en un contacto atraves del fixture.
        float massA = bodyA->GetMass();
        float massB = bodyB->GetMass();
        if( massA > 0.0f && massB > 0.0f ){
            if( massB > massA){
                bodysParaDestruir[bodysDestrActuales++] = bodyA;
            } else {
                bodysParaDestruir[bodysDestrActuales++] = bodyB;
            }
            if( bodysDestrActuales == maxBodyDestr ) break; // corto no quiero destruir mas cuerpo q el maximo  q fije arriba
        }
    }
    std::sort(bodysParaDestruir, bodysParaDestruir + bodysDestrActuales);
    int i = 0;
    while ( i < bodysDestrActuales){
        b2Body* unBody = bodysParaDestruir[i++];
        while( i < bodysDestrActuales && bodysParaDestruir[i] == unBody){
            i++;
        }
        world.DestroyBody(unBody); // aca eliminamos el cuerpo
    }
}


void tutoBox2DParte10(){
    // Clase world: Contiene todos los cuerpos y las articulaciones.
    // CREAR a todos ls cuerpos antes del paso del tiempo. para obtener resultados de colisiones para los nuevos cuerpos.
    b2World myWorld = b2World(b2Vec2(0.0f, -10.0f));
    // Simulacion: tradeoff entre rendimiento y preccision con 1/60 (60 actualizaciones/s estamos OK)
    // Recuento de iteraciones: # veces q el solucionado recorre todos los contactos y uniones en el mundo. 60Hz y 10 iteriaciones esta OK ! .
    // despues de dar un paso debes eliminar cualquier fuerza que hayas aplicado a tu cuerpo. con clearForces.
    myWorld.ClearForces();
    float timeSleep = 1.0f/60.0f;
    // para destruir a un cuerpo: Hay que tener cuidado de no dejar roto la listaBodys:
    b2Body* listaBodys = myWorld.GetBodyList();
    while(listaBodys){
        b2Body* bodyAct = listaBodys;
        listaBodys = bodyAct->GetNext();
        MyActor* unActor = (MyActor*) bodyAct->GetUserData().pointer;
        if(unActor->getNombre() == "Muerto"){
            myWorld.DestroyBody(bodyAct);
        }
    }
    b2BodyDef b1Def, b2Def;
    b2Body* body1 = myWorld.CreateBody(&b1Def);
    b2Body* body2 = myWorld.CreateBody(&b2Def);

    // Fuerzas e impulsos: Podemos aplicar fuerzas, torceduras impuslsos al cuerpo. Cuando aplicas una fuerza o un impulso
    // proporcionas un PUNTO MUNDIAL donde se aplica la carga. A menudo resulta en un torque alrededor de la masa.
    // Le pasamos el vector fuerza en N, la posicion mundial a aplicar la fuerza y si el cuerpo se despertara le paso true ver luego.
    // Aplicamos una fuerza al cuerpo:
    b2Vec2 vectorFuerza(-100.0f, 80.0f);
    b2Vec2 posDelGolpe(5.0f, 5.0f);
    body1->ApplyForce(vectorFuerza, posDelGolpe, true);

    // afecta la velocidad sin afectar la velocidad lineal del centro de masa, aplicamos un torque.
    body1->ApplyTorque(30,true);

    // Aplicamos Impulso a un cuerpo
    b2Vec2 vectorImpulso(100.0f, 100.0f);
    b2Vec2 posAplicarImpulso(5.0f, 3.0f);
    body1->ApplyLinearImpulse(vectorImpulso, posAplicarImpulso, true);

    // Aplicamos un impulso angular
    body1->ApplyAngularImpulse(30.0f, true);

    // Conviene solo despertar a cuerpos q estan despiertos (No conviene despertar a las vigas indestructibles).
    if(body1->IsAwake()){
        body1->ApplyForce(vectorFuerza, posDelGolpe, true);
    }
    // Metodos utiles
    body1->GetWorldPoint(posDelGolpe);      // le das un punto local te escupe un punto mundial
    body1->GetWorldVector(vectorFuerza);    // le das un vector local te escupe un vector mundial
    body1->GetLocalPoint(posDelGolpe);      // le das un punto mundial te escupe un punto local
    body1->GetLocalVector(vectorFuerza);    // le das un vector mundial te escupe un vector local.

    // Podemos iterar sobre los fixtures de un cuerpo  Util si necesitas acceder a la data del usuario.
    for (b2Fixture* f = body1->GetFixtureList(); f; f = f->GetNext()) {
        MyActor* data = (MyActor*)f->GetUserData().pointer;
    }
    // el cuerpo tambien proporciona una lista de contactos asociados puede usar para obtener informacion de los contactos acuales.
    // cuidado porq pueden q la lista de contactos no tengan todos lo coantatos que existieron durante el paso de tiempo anterior.

    // Datos de usuario: Tipico adjuntar un puntero del actor al cuerpo rigido de ese actor, y el cuerpo rigido adjuntar un puntero al actor.
    b2BodyDef defBody;
    MyActor unActor(1, "gusano");
    defBody.userData.pointer = (uintptr_t) &unActor;
    b2Body* bodyGusano = myWorld.CreateBody(&defBody);
    unActor.setBody(bodyGusano);
    // Ejemplos de por q necesitamos los datos del usuario:
    //   1) Aplicar daño a un actor utilizando el resultado de una colision, 2) Reproducir un evento si el jugador esta dentro de un cuadro 3) acceder A Una estrcutura
    // del jugego cuando un joint va a ser destruido. Sugiere el autor q todos los cuerpos deben tener el mismo tipo de puntero  y no un body puntero a Actor y otro body
    //  con un puntero a Foo (por problemas de casteo segun el). PARA FIXTURES: Considerar una estructura de datos que le permite almacenar informacion especifica del juego.
    FixtureData dataFixture;
    b2FixtureDef fixtureDef;
    fixtureDef.userData.pointer = (uintptr_t)  &dataFixture;
    b2Fixture* unFixture = body1->CreateFixture(&fixtureDef);
    // ... usos y al finalizar:
    unFixture->GetUserData().pointer = NULL;
    body1->DestroyFixture(unFixture);
    // Destruccion implcita: Si destruyes un cuerpo, todas los shapes, contactos y joints asociadas se destruyen automáticamente.(esto es destruccion implicita)
    // cuerpos conectados a estas joints/contactos se despiertan. Un body destruido llena la entidad destruida con "FDFDFFD".
    // Si destruyes una entidad BOX2D depende de vos eliminar todas las referencias usadas.
    // No hay ninguna notificacion cuando una junta o un fixture se destruye explicitamente. Podemos almacnear en nuestro codigo punteros a shape o joints y estos
    //  punteros quedan huerfanos al eliminar el bodyDestroyer.
    // Podemos llamar a b2DestructtionListener para limpiar los punteros huerfanos Y ademas le permite a b2Wrold informanos cuando un shape o joints es destruido
    // implicitamente, por q un cuerpo asociado fue destruido.
    MyDestructionListener myDestructor;
    myWorld.SetDestructionListener(&myDestructor);

}

void tutoBox2DParte11(){
    // BOX2D utiliza MKS ( Metros, km, s) y radianos para los angulos.  Si tomamos 50 pixeles por metro  (por q tu caracter tiene 75 px de alto).
    // puedes convertir de pixeles a metro usando esta formula. podes convertir de pixeles a metros usando:
    // xMetros = 0,02f * xPíxeles;
    // yMetros = 0,02f * yPíxeles;
    // y Pasar de metros a pixeles:
    // xPíxeles = 50,0f * xMetros;
    // yPíxeles = 50,0f * yMetros;
    // (Recomendado tener el juego en MKS y luego al momento de renderizar pasamos a pixeles everything ).

}

