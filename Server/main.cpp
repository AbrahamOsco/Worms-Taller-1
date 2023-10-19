#include <box2d/b2_math.h>
#include <box2d/box2d.h>
#include <box2d/b2_body.h>
#include "src/Modelo/Gusano.h"
#include "string"
#include <SDL2pp/SDL2pp.hh>
#include "math.h"
#include <iostream>
#define TAMANIO_GUSANO 1

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
    float friccionPorViga = 1.5f;
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
    shapeGusano.SetAsBox(1.0f, 1.0f, b2Vec2(2.0f, 1.450f), 0.0f);
    b2FixtureDef defFixtGusano;
    defFixtGusano.shape = &shapeGusano;
    defFixtGusano.friction = 2.0f;
    defFixtGusano.density = 2.0f;
    defFixtGusano.filter.groupIndex = -3;
    gusanoBody->CreateFixture(&defFixtGusano);
    return gusanoBody;
}


int main() {
    b2Vec2 gravity(0.0f, -10.0f);
    b2World* m_world = new b2World(gravity); //  heredamos este atributo de test
    // Creamos una la def y el body  de una linea de ancho infinitesimal.
    /*
    // Creamos una la def y el body  de una linea de ancho infinitesimal.
    b2BodyDef defLinea;
    defLinea.type = b2_staticBody;
    defLinea.position.Set(0.0f, 0.0f);
    b2Body* lineaBody = m_world->CreateBody(&defLinea); // creamos el body

    // creamos la forma
    b2EdgeShape shapeLineaFinita;
    shapeLineaFinita.SetTwoSided(b2Vec2(-30.0f, 0.0f), b2Vec2(30.0f, 0.0f)); // Le pasamos los dos vertices q tendra la linea (NO TIENE ANCHO).

    //agregamos la forma como un atributo del fixture y agregamos el fixture al body
    b2FixtureDef defFixLinea;
    defFixLinea.shape = &shapeLineaFinita;
    b2Fixture* lineaFixture =  lineaBody->CreateFixture(&defFixLinea);
    */

    b2Body* vigaSuelo1, *vigaSuelo2, *vigaSuelo3, *vigaSuelo4, *vigaSuelo5, *vigaSuelo6, *vigaSuelo7, *vigaSuelo8, *vigaSuelo9;
    b2Body* viga1, *viga2, *viga3, *viga4, *viga5, *viga6, *viga7, *viga8;
    vigaSuelo1 = crearNuevaViga(b2Vec2(0.0f, 0.0f), b2Vec2(50.0f, 0.4f), 0, m_world);
    vigaSuelo2 = crearNuevaViga(b2Vec2(-50, 25.0f), b2Vec2(25.0f, 0.4f), 90, m_world);
    vigaSuelo3 = crearNuevaViga(b2Vec2(0.0f, 50.0f), b2Vec2(50.0f, 0.4f), 0, m_world);
    vigaSuelo4 = crearNuevaViga(b2Vec2(50.0f, 25.0f), b2Vec2(25.0f, 0.4f), 90, m_world);



    /*
    vigaSuelo1 = crearNuevaViga(b2Vec2(-30.0f, 0.0f), b2Vec2(50.0f, 0.4f), 0, m_world);
    vigaSuelo2 = crearNuevaViga(b2Vec2(-30.0f, 0.0f), b2Vec2(50.0f, 0.4f), 90, m_world);
    vigaSuelo3 = crearNuevaViga(b2Vec2(100.0f, 0.0f), b2Vec2(50.0f, 0.4f), 90, m_world);
    vigaSuelo4 = crearNuevaViga(b2Vec2(-30.0f, 100.0f), b2Vec2(100.0f, 0.4f), 0, m_world);
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
    b2Body* gusanos[3];
    //creamos un payload que luego sera un gusano
    gusanos[0] = crearGusano(m_world, 15.0f);
    gusanos[1] = crearGusano(m_world, 20.0f);
    gusanos[2] = crearGusano(m_world, 25.0f);


    //gusanos[0]->ApplyForce( b2Vec2(0.0f, 100.0f), gusanos[0]->GetWorldCenter(), true);
    float impulsoX = gusanos[0]->GetMass() * 16.0924f;
    float impulsoY = gusanos[0]->GetMass() * 0.3109f;
    b2Vec2 impusloAdelante(impulsoX, impulsoY); //  por la gravedad
    gusanos[0]->ApplyLinearImpulse(impusloAdelante, gusanos[0]->GetWorldCenter(), true);


    //Teletrasportacion
    gusanos[1]->SetTransform( b2Vec2(-15.0f, 20.0f), 0);
    gusanos[2]->ApplyLinearImpulse( b2Vec2(0.0f, 100.0f), gusanos[0]->GetWorldCenter(), true);


}

/*
    // Ejemplo de de juguete con box2d.
    Worm gusano(Posicion(20, 20), 0.2f, 1.0f, 300);
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);
    b2BodyDef bodyGusDef;
    bodyGusDef.fixedRotation = true; // Impedimos que el gusano gire. solo  podra gira a izq a derecha a mano.
    bodyGusDef.type = b2_dynamicBody;
    bodyGusDef.position.Set(20.0f, 20.0f);
    world.CreateBody(&bodyGusDef);


   // Ejemplo con SDL Andando en el repo OK!.
   // Initialize SDL library
   SDL sdl(SDL_INIT_VIDEO);

   // Initialize SDL_ttf library
   SDLTTF ttf;

   // Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
   Window window("SDL2pp demo",
                 SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                 640, 480,
                 SDL_WINDOW_RESIZABLE);

   // Create accelerated video renderer with default driver
   Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

   // Load sprites image as a new texture; since there's no alpha channel
   // but we need transparency, use helper surface for which set color key
   // to color index 0 -> black background on image will be transparent on our
   // texture
   Texture sprites(renderer, Surface(DATA_PATH "/M484SpaceSoldier.png")
   .SetColorKey(true, 0));

   // Enable alpha blending for the sprites
   sprites.SetBlendMode(SDL_BLENDMODE_BLEND);

   // Gradient texture to be generated
   Texture gradient(renderer, SDL_PIXELFORMAT_BGR888, SDL_TEXTUREACCESS_STATIC, 1, 256);
   {
       // Array holding RGB values for 256 pixels
       unsigned char grad[256 * 3];
       int n = 0; // counter

       // Fill array with fading gray values from white to black; its contents will be
       // 255,255,255, 254,254,254, 253,253,253 ... 1,1,1, 0,0,0
       std::generate(grad, grad + sizeof(grad), [&](){ return 255 - n++ / 3; });

       // Update texture with our raw color data, enable blending and set color
       // and alpha modulation, so when rendered our texture will be dark cyan
       gradient.Update(NullOpt, grad, 3)
               .SetBlendMode(SDL_BLENDMODE_BLEND)
               .SetColorMod(0, 255, 255)
               .SetAlphaMod(85);
   }

   // Load font, 12pt size
   Font font(DATA_PATH "/Vera.ttf", 12);

   // Game state
   bool is_running = false; // whether the character is currently running
   int run_phase = -1;      // run animation phase
   float position = 0.0;    // player position

   unsigned int prev_ticks = SDL_GetTicks();
   // Main loop
   while (1) {
       // Timing: calculate difference between this and previous frame
       // in milliseconds
       unsigned int frame_ticks = SDL_GetTicks();
       unsigned int frame_delta = frame_ticks - prev_ticks;
       prev_ticks = frame_ticks;

       // Event processing:
       // - If window is closed, or Q or Escape buttons are pressed,
       //   quit the application
       // - If Right key is pressed, character would run
       // - If Right key is released, character would stop
       SDL_Event event;
       while (SDL_PollEvent(&event)) {
           if (event.type == SDL_QUIT) {
               return 0;
           } else if (event.type == SDL_KEYDOWN) {
               switch (event.key.keysym.sym) {
                   case SDLK_ESCAPE: case SDLK_q:
                       return 0;
                   case SDLK_RIGHT: is_running = true; break;
               }
           } else if (event.type == SDL_KEYUP) {
               switch (event.key.keysym.sym) {
                   case SDLK_RIGHT: is_running = false; break;
               }
           }
       }

       // Update game state for this frame:
       // if character is runnung, move it to the right
       if (is_running) {
           position += frame_delta * 0.2;
           run_phase = (frame_ticks / 100) % 8;
       } else {
           run_phase = 0;
       }

       // If player passes past the right side of the window, wrap him
       // to the left side
       if (position > renderer.GetOutputWidth())
           position = -50;

       int vcenter = renderer.GetOutputHeight() / 2; // Y coordinate of window center

       // Clear screen
       renderer.Clear();

       // Copy our gradient texture, stretching it to the whole window
       renderer.Copy(
               gradient,
               NullOpt,
               Rect(0, vcenter, renderer.GetOutputWidth(), renderer.GetOutputHeight() / 2)
       );

       // Pick sprite from sprite atlas based on whether
       // player is running and run animation phase
       int src_x = 8, src_y = 11; // by default, standing sprite
       if (is_running) {
           // one of 8 run animation sprites
           src_x = 8 + 51 * run_phase;
           src_y = 67;
       }

       // Draw player sprite
       sprites.SetAlphaMod(255); // sprite is fully opaque
       renderer.Copy(
               sprites,
               Rect(src_x, src_y, 50, 50),
               Rect((int)position, vcenter - 50, 50, 50)
       );

       // Draw the same sprite, below the first one, 50% transparent and
       // vertically flipped. It'll look like reflection in the mirror
       sprites.SetAlphaMod(127); // 50% transparent
       renderer.Copy(
               sprites,
               Rect(src_x, src_y, 50, 50),
               Rect((int)position, vcenter, 50, 50),
               0.0,              // don't rotate
               NullOpt,          // rotation center - not needed
               SDL_FLIP_VERTICAL // vertical flip
       );

       // Create text string to render
       std::string text =
               "Position: "
               + std::to_string((int)position)
               + ", running: "
               + (is_running ? "true" : "false");

       // Render the text into new texture. Note that SDL_ttf render
       // text into Surface, which is converted into texture on the fly
       Texture text_sprite(
               renderer,
               font.RenderText_Blended(text, SDL_Color{255, 255, 255, 255})
       );

       // Copy texture into top-left corner of the window
       renderer.Copy(text_sprite, NullOpt, Rect(0, 0, text_sprite.GetWidth(), text_sprite.GetHeight()));

       // Show rendered frame
       renderer.Present();

       // Frame limiter: sleep for a little bit to not eat 100% of CPU
       SDL_Delay(1);
   }

   // Here all resources are automatically released and libraries deinitialized
   return 0;
} catch (std::exception& e) {
   // If case of error, print it and exit with error
   std::cerr << e.what() << std::endl;
   return 1;
 }

*/
