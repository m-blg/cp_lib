#include "mbgldef.h"
#include "memory.cc"

namespace cp {

template <typename T>
struct List_Queue_Node {
    T data;
    List_Queue_Node* next;
};


template <typename T>
struct List_Queue {
    List_Queue_Node<T>* head;
    List_Queue_Node<T>* tail;

    void init() {
        head = null;
        tail = null;
    }

    bool is_empty() {
        return (head == null);
    }

    T& front() {
        return head->data;
    }

    T& back() {
        return tail->data;
    }

    // Functions

    static bool 
    enqueue(List_Queue<T> *self, T value) 
    {
        List_Queue_Node<T>* node = m::alloc<List_Queue_Node<T>>(1);
        if (node == null) { return false; }
        node->data = value;
        node->next = null;

        if (self->tail != null) {
            self->tail->next = node;
        }
        self->tail = node;

        if (self->head == null) {
            self->head = node;
        }

        return true;
    }

    static bool 
    dequeue(List_Queue<T> *self) 
    {
        if (self->head == null) return false;

        List_Queue_Node<T>* node = self->head;
        self->head = self->head->next;
        if (self->head == null)
            self->tail = null;

        free(node);
        return true;
    }

};

template <typename T>
using lqueue = List_Queue<T>;

using lqueueu = lqueue<u32>;
using lqueuei = lqueue<i32>;
using lqueuef = lqueue<f32>;
using lqueued = lqueue<f64>;



}
