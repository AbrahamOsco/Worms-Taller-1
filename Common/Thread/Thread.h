//
// Created by abraham on 23/10/23.
//

#ifndef WORMS_TALLER_1_THREAD_H
#define WORMS_TALLER_1_THREAD_H

#include <thread>

class Thread {
private:
    std::thread thread;  // cppcheck-suppress unusedStructMember

public:
    //  Constructor .
    Thread() = default;

    //  Pre: -
    //  Post: Lanza el thread usando la funcion main.
    void start();

    //  Pre: -
    //  Post: Funcion que invoca al metodo abstracto run y con try-catch de ultimo recurso.
    void main();

    //  Pre: -
    //  Post: Metodo abstracto cuyas clases hijas deben implementarlo.
    virtual void run() = 0;


    //  Pre: -
    //  Post: Joinea el thread
    void join();

    // Destructor, en clases abstractas destructures siempre virtuales.
    virtual ~Thread() = default;

    //  Eliminamos el constructor por copia, no tiene sentido copiar threads.
    Thread(const Thread&) = delete;

    //  Eliminamos el operador asigancion ambien para evitar copias de threads.
    Thread& operator=(const Thread&) = delete;

    // Tambien eliminamos la opcion de mover threads.
    Thread(Thread&& other) = delete;
    Thread& operator=(Thread&& other) = delete;

};


#endif //WORMS_TALLER_1_THREAD_H
