#include "memory.cc"

namespace cp {

template <typename T>
struct List_Node {
    T data;
    List_Node* next;
};

template <typename T>
List_Node<T>* list_node_make(T data) {
    List_Node<T>* node = m_alloc<List_Node<T>>(1);
    *node = { data, null }; 
    return node;
}

template <typename T>
List_Node<T>* next(List_Node<T> *self) {
    return self->next;
}

template <typename T>
void add_after(List_Node<T> *self, List_Node<T> *node) {
    node->next = next(self);
    self->next = node;
}

template <typename T>
void add_after(List_Node<T> *self, T data) {
    auto node = list_node_make(data);
    node->next = next(self);
    self->next = node;
}



template <typename T>
struct List {
    List_Node<T>* first;
    u32 len;
}; 

template <typename T>
List_Node<T>* begin(List<T> *self) {
    return self->first;
}

template <typename T>
List_Node<T>* end(List<T> *self) {
    return null;
}

template <typename T>
void init(List<T> *self) {
    *self = {};
}

template <typename T>
void shut(List<T> *self) {
    for (auto it = begin(self); it != end(self);) {
        auto temp = next(it);
        free(it);
        it = temp;
    }
}

template <typename T>
u32 len(List<T> *self) {
    return self->len;
}


template <typename T>
void add(List<T> *self, T data, u32 index) {
    assert(index <= self->len);
    if (index == 0) {
        auto node = list_node_make(data);
        node->next = self->first;
        self->first = node;
        self->len++;
        return;
    }

    auto it = begin(self);
    for (u32 i = 0; i < index - 1; i++) {
        it = next(it);
    }

    auto node = list_node_make(data);
    node->next = next(it);
    it->next = node;
    self->len++;
}


template <typename T>
void remove(List<T> *self, u32 index) {
    assert(index < self->len);
    if (self->len == 1) {
        free(self->first);
        self->first = null;
        self->len--;
        return;
    }

    List_Node<T>* it1 = self->first;
    List_Node<T>* it2 = next(self->first);

    for (u32 i = 0; i < index - 1; i++) {
        it1 = it2;
        it2 = next(it2);
    }

    it1->next = next(it2);
    free(it2);
    self->len--;
}

template <typename T>
struct Queue {
    List<T> buffer;
};

void push() {

}

template <typename T>
void pop(Queue<T> *self) {
    remove(&self->buffer, len(&self->buffer) - 1);
}

}
