#pragma once

#include "mbgldef.h"
#include "basic.cc"
#include "buffer.cc"
#include <cassert>
#include <string.h>


namespace cp {


template <typename T>
void arr_push(T* buffer, u32 *len, T item) { // push with value
    buffer[(*len)] = item;
    (*len)++;
}
    
template <typename T>
T arr_pop(T* buffer, u32 *len) { // remove last and return, if don't want to return, use remove(last) instead
    (*len)--;
    return buffer[(*len)];
}

template <typename T>
void arr_add(T* buffer, u32 *len, T item, u32 index) { // add with value
    T* p_target = buffer + index;
    for (T* p = buffer + (*len); p > p_target; p--) {
        *p = *(p - 1);
    }
    *p_target = item;
    (*len)++;
}

template <typename T>
void arr_remove(T* buffer, u32 *len, u32 index) {
    assert(len != 0);
    (*len)--;
    T* p_end = buffer + (*len);
    for (T* p = buffer + index; p < p_end; p++) {
        *p = *(p + 1);
    }
}

template <typename T>
void arr_remove(T* buffer, u32 *len, T* it) {
    assert(len != 0);
    (*len)--;
    T* p_end = buffer + (*len);
    for (T* p = it; p < p_end; p++) {
        *p = *(p + 1);
    }
}


// dynamic


template <typename T>
void arr_dpush(T* *buffer, u32 *len, u32 *cap, T item) { 
    if (*len >= *cap) {
        dresize( buffer, cap, max(1u, 2 * (*cap)) );
    }
    (*buffer)[(*len)] = item;
    (*len)++;
}

void arr_raw_print(i8* buffer, u32 stride, u32 len, const char* item_fmt) {
    i8* endp = buffer + stride * len;
    for (i8* p = buffer; p < endp; p += stride) {
        printf(item_fmt, *p);
    }
}



template <typename T, u32 t_cap>
struct Static_Array {
    T buffer[t_cap];
    u32 len;
    
    void init() { len = 0; }
    
    constexpr u32 cap() {
        return t_cap;
    }
    
    T& operator[](u32 index) {
        assert(("Index out of range", index < t_cap));
        return buffer[index];
    }
   
};

template <typename T, u32 t_cap>
using sarr = Static_Array<T, t_cap>;

template <u32 t_cap>
using sarru = Static_Array<u32, t_cap>;
template <u32 t_cap>
using sarri = Static_Array<i32, t_cap>;
template <u32 t_cap>
using sarrf = Static_Array<f32, t_cap>;
template <u32 t_cap>
using sarrd = Static_Array<f64, t_cap>;

template <typename T, u32 t_cap>
inline u32 cap(sarr<T, t_cap> *self) { return t_cap; }
template <typename T, u32 t_cap>
inline u32 len(sarr<T, t_cap> *self) { return self->len; }
template <typename T, u32 t_cap>
inline T* begin(sarr<T, t_cap> *self) { return self->buffer; }
template <typename T, u32 t_cap>
inline T* end(sarr<T, t_cap> *self) { return self->buffer + self->len; }

template <typename T, u32 t_cap>
inline bool is_empty(sarr<T, t_cap> *self) { return (self->len == 0); }

template <typename T, u32 t_cap>
inline T& back(sarr<T, t_cap> *self) { return self->buffer[self->len-1]; }



template <typename T, u32 t_cap>
void push(sarr<T, t_cap> *self, T item) {
    arr_push(self->buffer, &self->len, item);
}

template <typename T, u32 t_cap>
T pop(sarr<T, t_cap> *self) {
    return arr_pop(self->buffer, &self->len);
}

template <typename T, u32 t_cap>
void add(sarr<T, t_cap> *self, T item, u32 index) {
    arr_add(self->buffer, &self->len, item, index);
}

template <typename T, u32 t_cap>
void remove(sarr<T, t_cap> *self, u32 index) {
    arr_remove(self->buffer, &self->len, index);
}

template <typename T, u32 t_cap>
void print(sarr<T, t_cap> *self, const char* item_fmt) {
    buff_print(self->buffer, self->len, item_fmt);
}



template <typename T>
struct Dynamic_Array {
    union {
        struct {
            T* buffer;
            u32 cap;
        };
        dbuff<T> db;
    };
    u32 len;

    void init(u32 init_cap) { 
        buffer = m_alloc<T>(init_cap); 
        cap = init_cap; 
        len = 0; 
    }

    template <u32 t_arg_count>
    void init_range(u32 init_cap, sbuff<T, t_arg_count> args) {
        buffer = m_alloc<T>(init_cap); 
        cap = init_cap;
        len = t_arg_count;
        memcpy(buffer->buffer, args.buffer, t_arg_count * sizeof(T));
    }

    void shut() { 
        free(buffer); 
        *this = {};
    }


    T& operator[](u32 index) {
        assert(("Index out of range", index < cap));
        return buffer[index];
    }

};

template <typename T>
using darr = Dynamic_Array<T>;

using darru = Dynamic_Array<u32>;
using darri = Dynamic_Array<i32>;
using darrf = Dynamic_Array<f32>;
using darrd = Dynamic_Array<f64>;

template <typename T>
inline u32 cap(darr<T> *self) { return self->cap; }
template <typename T>
inline u32 len(darr<T> *self) { return self->len; }
template <typename T>
inline T* begin(darr<T> *self) { return self->buffer; }
template <typename T>
inline T* end(darr<T> *self) { return self->buffer + self->len; }

template <typename T>
inline bool is_empty(darr<T> *self) { return (self->len == 0); }

template <typename T>
inline T& back(darr<T> *self) { return self->buffer[self->len-1]; }


//darr methods

template <typename T>
void push(darr<T> *self, T item) {
    arr_push(self->buffer, &self->len, item);
}

template <typename T>
void dpush(darr<T> *self, T item) {
    arr_dpush(&self->buffer, &self->len, &self->cap, item);
}

template <typename T>
T pop(darr<T> *self) {
    return arr_pop(self->buffer, &self->len);
}

template <typename T>
void add(darr<T> *self, T item, u32 index) {
    arr_add(self->buffer, &self->len, item, index);
}

template <typename T>
void remove(darr<T> *self, u32 index) {
    arr_remove(self->buffer, &self->len, index);
}

template <typename T>
void remove(darr<T> *self, T* it) {
    arr_remove(self->buffer, &self->len, it);
}


template <typename T>
void print(darr<T> *self, const char* item_fmt) {
    buff_print(self->buffer, self->len, item_fmt);
}

template <typename T, u32 t_items_count>
void dpush_range(darr<T> *self, sbuff<T, t_items_count>&& items) {
    if (self->len + t_items_count >= self->cap) {
        dresize( &self->buffer, &self->cap, max(t_items_count, 2 * (self->cap)) );
    }

    memcpy(self->buffer, items.buffer, t_items_count * sizeof(T));
    self->len += t_items_count;
}

}

