#ifndef QUEUE_H_
#define QUEUE_H_

#include <climits>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <queue>
#include <exception>
#include <stdexcept>

struct ClosedQueue: public std::runtime_error {
    ClosedQueue(): std::runtime_error("The Queue is closed") {}
};

/*
 * Multiproducer/Multiconsumer Blocking Queue (MPMC)
 *
 * Queue is a generic MPMC queue with blocking operations
 * push() and pop().
 *
 * Two additional methods, try_push() and try_pop() allow
 * non-blocking operations.
 *
 * On a closed queue, any method will raise ClosedQueue.
 *
 * */
template <typename T, class C = std::deque<T> >
class Queue {
private:
    std::queue<T, C> q;                    // cppcheck-suppress unusedStructMember
    const unsigned int max_size;           // cppcheck-suppress unusedStructMember
    bool closed;                           // cppcheck-suppress unusedStructMember
    std::mutex mtx;                        // cppcheck-suppress unusedStructMember
    std::condition_variable is_not_full;   // cppcheck-suppress unusedStructMember
    std::condition_variable is_not_empty;  // cppcheck-suppress unusedStructMember

public:
    Queue(): max_size(UINT_MAX - 1), closed(false) {}
    explicit Queue(const unsigned int max_size): max_size(max_size), closed(false) {}


    bool try_push(T const& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw ClosedQueue();
        }

        if (q.size() == this->max_size) {
            return false;
        }

        if (q.empty()) {
            is_not_empty.notify_all();
        }

        q.push(val);
        return true;
    }

    bool try_pop(T& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (q.empty()) {
            if (closed) {
                throw ClosedQueue();
            }
            return false;
        }

        if (q.size() == this->max_size) {
            is_not_full.notify_all();
        }

        val = q.front();
        q.pop();
        return true;
    }

    void push(T const& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw ClosedQueue();
        }

        while (q.size() == this->max_size) {
            is_not_full.wait(lck);
        }

        if (q.empty()) {
            is_not_empty.notify_all();
        }

        q.push(val);
    }


    T pop() {  // cppcheck-suppress duplInheritedMember
        std::unique_lock<std::mutex> lck(mtx);

        while (q.empty()) {
            if (closed) {
                throw ClosedQueue();
            }
            is_not_empty.wait(lck);
        }

        if (q.size() == this->max_size) {
            is_not_full.notify_all();
        }

        T const val = q.front();
        q.pop();

        return val;
    }

    void close() {  // cppcheck-suppress duplInheritedMember
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw std::runtime_error("The Queue is already closed.");
        }

        closed = true;
        is_not_empty.notify_all();
    }

private:
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
};

template <>
class Queue<void*> {
private:
    std::queue<void*> q;
    const unsigned int max_size;

    bool closed;

    std::mutex mtx;
    std::condition_variable is_not_full;
    std::condition_variable is_not_empty;

public:
    // Constructor
    explicit Queue(const unsigned int max_size): max_size(max_size), closed(false) {}

    //  Pre: recibir el valor a pushear
    //  Post: intentap pushear el elemento si no esta llena  lo pushea y retorna true, si esta llena
    //  no lo pushea y reorna false, es no bloqueante
    bool try_push(void* const& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw ClosedQueue();
        }

        if (q.size() == this->max_size) {
            return false;
        }

        if (q.empty()) {
            is_not_empty.notify_all();
        }

        q.push(val);
        return true;
    }

    //  Pre: recibir el valor a pushear
    //  Post: intentap pushear el elemento si no esta llena  lo pushea y retorna true, si esta llena
    //  no lo pushea y reorna false, es no bloqueante
    bool try_pop(void*& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (q.empty()) {
            if (closed) {
                throw ClosedQueue();
            }
            return false;
        }

        if (q.size() == this->max_size) {
            is_not_full.notify_all();
        }

        val = q.front();
        q.pop();
        return true;
    }

    //  Pre: recibir el valor a pushear
    //  Post: Pushea el elemento si la cola esta llena, se bloquea hasta que haya lugar, si hay
    //  lugar pushea el valor directamente.
    void push(void* const& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw ClosedQueue();
        }

        while (q.size() == this->max_size) {
            is_not_full.wait(lck);
        }

        if (q.empty()) {
            is_not_empty.notify_all();
        }

        q.push(val);
    }

    //  Pre: -
    //  Post: Popea un valor de la cola (el primero) y lo retorna , si esta vacia se bloquea hasta
    //  que haya algun valor, si hay elemento hace el pop.
    void* pop() {
        std::unique_lock<std::mutex> lck(mtx);

        while (q.empty()) {
            if (closed) {
                throw ClosedQueue();
            }
            is_not_empty.wait(lck);
        }

        if (q.size() == this->max_size) {
            is_not_full.notify_all();
        }

        void* const val = q.front();
        q.pop();

        return val;
    }

    //  Pre: -
    //  Post: Cierra la Queuee (no permite que se pushee mas elementos).
    void close() {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw std::runtime_error("The Queue is already closed.");
        }

        closed = true;
        is_not_empty.notify_all();
    }

private:
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
};


template <typename T>
class Queue<T*>: private Queue<void*> {
public:
    explicit Queue(const unsigned int max_size): Queue<void*>(max_size) {}

    bool try_push(T* const& val) { return Queue<void*>::try_push(val); }

    bool try_pop(T*& val) {
        return Queue<void*>::try_pop((void*&)val);  // cppcheck-suppress cstyleCast
    }

    void push(T* const& val) { return Queue<void*>::push(val); }


    T* pop() { return (T*)Queue<void*>::pop(); }  // cppcheck-suppress duplInheritedMember

    void close() { return Queue<void*>::close(); }  // cppcheck-suppress duplInheritedMember

private:
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
};

#endif
