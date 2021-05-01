
#include "array.cc"

namespace cp {

template <typename T, u32 t_static_cap>
struct String {
    T sbuffer[t_static_cap];
    T* dbuffer;
    u32 cap;
    u32 len;
};


template <typename T, u32 t_static_cap>
void init(String<T, t_static_cap> *self, u32 init_cap=0) {
    if (init_cap > t_static_cap) {
        self->dbuffer = m_alloc<T>(init_cap - t_static_cap);
        self->cap = init_cap;
    } else {
        self->dbuffer = null;
        self->cap = t_static_cap;
    }
    self->len = 0;
}


template <typename T, u32 t_static_cap>
void init(String<T, t_static_cap> *self, const T* c_str) {
    u32 init_cap = strlen(c_str);
    if (init_cap > t_static_cap) {
        self->dbuffer = m_alloc<T>(init_cap - t_static_cap);
        self->cap = init_cap;
    } else {
        self->dbuffer = null;
        self->cap = t_static_cap;
    }
    self->len = init_cap;
}

template <typename T, u32 t_static_cap>
void shut(String<T, t_static_cap> *self) {
    if (self->dbuffer != null)
        free(self->dbuffer);
    self->dbuffer = null;
    self->cap = 0;
    self->len = 0;
}

template <typename T, u32 t_static_cap>
String<T, t_static_cap>* cat(String<T, t_static_cap> *first, String<T, t_static_cap> *second) {

}


using str = String<char, 16>;


using dstr = Dynamic_Array<char>;

void init(dstr *self, const char* c_str) {
    u32 init_cap = strlen(c_str);
    self->buffer = (char*)c_str;
    self->cap = init_cap;
    self->len = init_cap;
}

dstr *cat(dstr *first, dstr *second) {
    append(first, second);
}

}


