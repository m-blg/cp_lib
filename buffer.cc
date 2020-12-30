#pragma once

#include "mbgldef.h"
#include "memory.cc"
#include <cassert>

namespace cp {

namespace buffer {

    template <typename T>
    void dresize(T* *buffer, u32 *capacity, u32 new_capacity) {
        *buffer = m::ralloc(*buffer, new_capacity);
        *capacity = new_capacity;
    }

    template <typename T>
    void scan(T* buffer, u32 len, const char* item_fmt) {
        T* p = buffer;
        T* ep = buffer + len;
        for (; p < ep; p++) {
            scanf(item_fmt, p);
        }
    }

    template <typename T>
    void print(T* buffer, u32 len, const char* item_fmt) {
        T* endp = buffer + len;
        for (T* p = buffer; p < endp; p++) {
            printf(item_fmt, *p);
        }
    }

}

// wrapper arround T[t_capacity], t_capacity - buffer capacity in items
template <typename T, u32 t_capacity>
struct StaticBuffer {
    T buffer[t_capacity];

    constexpr u32 capacity() { return t_capacity; }
    constexpr T* begin() { return buffer; }
    constexpr T* end() { return buffer + t_capacity; }

    T& operator[](u32 index) {
        assert(("Index out of range", 0 <= index < t_capacity));
        return buffer[index];
    }

    static void print(StaticBuffer<T, t_capacity> *self, const char* item_fmt) {
        buffer::print(self->buffer, t_capacity, item_fmt);
    }
};

template <typename T, u32 t_capacity>
using sbuff = StaticBuffer<T, t_capacity>;

template <u32 t_capacity>
using sbuffu = StaticBuffer<u32, t_capacity>;
template <u32 t_capacity>
using sbuffi = StaticBuffer<i32, t_capacity>;
template <u32 t_capacity>
using sbufff = StaticBuffer<f32, t_capacity>;
template <u32 t_capacity>
using sbuffd = StaticBuffer<f64, t_capacity>;
template <u32 t_capacity>
using sbuffb = StaticBuffer<bool, t_capacity>;


template <typename T>
struct DynamicBuffer {
    T* buffer;
    u32 capacity; // in items
    T* begin() { return buffer; }
    T* end() { return buffer + capacity; }

    void init(u32 initial_capacity = 0) { 
        capacity = initial_capacity; 
        buffer = m::alloc<T>(initial_capacity); 
    }
    void shut() { free(buffer); capacity = 0; }

    T& operator[](u32 index) {
        assert(("Index out of range", 0 <= index < capacity));
        return buffer[index];
    }

    // methods
    static void dresize(DynamicBuffer<T>* self, u32 new_capacity) {
        buffer::dresize(self->buffer, self->capacity, new_capacity);
    }

    T sum(DynamicBuffer<T>* self) {
        T out_sum = 0;
        T* endp = buffer + self->capacity;
        for (T* p = buffer; p < endp; p++) {
            out_sum += *p;
        }
        return out_sum;
    }

    T sum_lmd(DynamicBuffer<T>* self, T& (*access_lmd)(T*)) {
        T out_sum = 0;
        T* endp = buffer + self->capacity;
        for (T* p = buffer; p < endp; p++) {
            out_sum += access_lmd(p);
        }
        return out_sum;
    }

    static void print(DynamicBuffer<T> *self, const char* item_fmt) {
        buffer::print(self->buffer, self->capacity, item_fmt);
    }
};

template <typename T>
using dbuff = DynamicBuffer<T>;

using dbuffu = DynamicBuffer<u32>;
using dbuffi = DynamicBuffer<i32>;
using dbufff = DynamicBuffer<f32>;
using dbuffd = DynamicBuffer<f64>;
using dbuffb = DynamicBuffer<bool>;


template <typename T>
struct DynamicBuffer2 {
    T* buffer;
    u32 y_capacity; // rows
    u32 x_capacity; // collumns

    void init(u32 init_y_capacity, u32 init_x_capacity) {
        y_capacity = init_y_capacity;
        x_capacity = init_x_capacity;
        buffer = m::alloc<T>(y_capacity * x_capacity);
    }
    void init_const(u32 init_y_capacity, u32 init_x_capacity, T value) {
        y_capacity = init_y_capacity;
        x_capacity = init_x_capacity;
        buffer = m::alloc<T>(y_capacity * x_capacity);
        T* endp = buffer + total_capacity();
        for (T* p = buffer; p < endp; p++) {
            *p = value;
        }
    }


    void shut() {
        free(buffer);
    }

    u32 total_capacity() {
        return y_capacity * x_capacity;
    }

    T& get(u32 y_index, u32 x_index) {
        return buffer[x_capacity * y_index + x_index];
    }


    // Functions

    static void print(DynamicBuffer2<T> *self, const char* item_fmt, const char* row_delim="\n") {
        u32 len = self->total_capacity();
        for (u32 i = 0; i < len; i++) {
            printf(item_fmt, self->buffer[i]);

            if ((i % self->x_capacity) == self->x_capacity - 1)
                printf(row_delim);
        }
    }

};

template <typename T>
using dbuff2 = DynamicBuffer2<T>;

using dbuff2u = DynamicBuffer2<u32>;
using dbuff2i = DynamicBuffer2<i32>;
using dbuff2f = DynamicBuffer2<f32>;
using dbuff2d = DynamicBuffer2<f64>;
using dbuff2b = DynamicBuffer2<bool>;


template<typename T>
static void dbuff2_scan(DynamicBuffer2<T> *self, const char* item_fmt) {
    buffer::scan(self->buffer, self->total_capacity(), item_fmt);
}
//namespace mdbuffer {
//template <typename T>
//T& get_item(T* buffer, u32 dim_count, u32 dim_capacity) {

//}

//}

//template <typename T>
//struct Dynamic_Multidim_Buffer {
    //u32 dim_capacity;
    //u32 dim_count;
    //T* buffer;
//};


//template <typename T, u32 t_dim_count, u32 t_dim_capacity>
//struct Static_Multidim_Array {
    //u32 len;
    //T buffer[t_dim_capacity * t_dim_count];

    
//};

}
