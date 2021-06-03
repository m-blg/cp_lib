#include "buffer.cc"

namespace cp {

template <typename T>
struct List_Node {
    T data;
    List_Node* next;
};

template <typename T>
List_Node<T>* list_node_alloc(T data) {
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
    auto node = list_node_alloc(data);
    node->next = next(self);
    self->next = node;
}


// iterator
template <typename T>
struct List_Iterator {
    List_Node<T>* ptr;

    List_Node<T>* operator->();

    typedef T type;
};

template <typename T>
using list_iter = List_Iterator<T>;


template <typename T>
void next(list_iter<T> *it) {
    it->ptr = next(it->ptr);
}
template <typename T>
void prev(list_iter<T> *it) {
    it->ptr = prev(it->ptr);
}

template <typename T>
void next(list_iter<T> *it, u32 step) {
    for (u32 i = 0; i < step; i++) {
        next(it);
    }
}
template <typename T>
void prev(list_iter<T> *it, u32 step) {
    for (u32 i = 0; i < step; i++) {
        prev(it);
    }
}
template <typename T>
List_Node<T>* List_Iterator<T>::operator->() {return this->ptr;}
template <typename T>
T& operator*(const list_iter<T>& it) {return *it.ptr;}
template <typename T>
void operator++(list_iter<T>& it) {next(&it);}
template <typename T>
void operator++(list_iter<T>& it, int) {next(&it);}
template <typename T>
list_iter<T> operator+(list_iter<T> it, u32 step) {next(&it, step); return it;}
template <typename T>
void operator+=(list_iter<T>& it, u32 step) {next(&it, step);}
template <typename T>
bool operator!=(const list_iter<T>& f, const list_iter<T>& s) {return f.ptr != s.ptr;}
template <typename T>
bool operator==(const list_iter<T>& f, const list_iter<T>& s) {return f.ptr == s.ptr;}



template <typename T, bool t_is_circular=false>
struct List {
    List_Node<T>* first;
    u32 len;

    typedef T type;
    typedef list_iter<T> iter;
}; 

template <typename T>
using CList = List<T, true>;

template <typename T, bool t_is_circular>
List_Node<T>* beginp(List<T, t_is_circular> *self) {
    return self->first;
}
template <typename T>
List_Node<T>* endp(List<T> *self) {
    return null;
}
template <typename T>
List_Node<T>* endp(List<T, true> *self) {
    return self->first;
}

template <typename T, bool t_is_circular>
list_iter<T> begin(List<T, t_is_circular> *self) {
    return {self->first};
}
template <typename T>
list_iter<T> end(List<T> *self) {
    return {null};
}
template <typename T>
list_iter<T> end(List<T, true> *self) {
    return {self->first};
}

template <typename T, bool t_is_circular>
void init(List<T, t_is_circular> *self) {
    *self = {};
}

template <typename T, bool t_is_circular>
void shut(List<T, t_is_circular> *self) {
    for (auto it = begin(self); it != end(self);) {
        auto temp = it + 1;
        free(it.ptr);
        it = temp;
    }
}

template <typename T, bool t_is_circular>
u32 len(List<T, t_is_circular> *self) {
    return self->len;
}


template <typename T, bool t_is_circular>
void add(List<T, t_is_circular> *self, T data, u32 index) {
    assert(index <= self->len);
    if (index == 0) {
        auto node = list_node_alloc(data);
        if constexpr(!t_is_circular) {
            node->next = self->first;
        } else {
            node->next = (self->len == 0) ? node : self->first;
        }
        self->first = node;
        self->len++;
        return;
    }

    auto it = begin(self);
    it += index - 1;

    auto node = list_node_alloc(data);
    node->next = (it + 1).ptr;
    it->next = node;
    self->len++;
}


template <typename T, bool t_is_circular>
void remove(List<T, t_is_circular> *self, u32 index) {
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

template <typename T, bool t_is_circular>
void print(List<T, t_is_circular> *self) {
    for (auto it = begin(self); it != end(self); it++) {
        print(it->data); printf(" ");
    }
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
