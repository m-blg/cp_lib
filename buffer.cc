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
    T sum(T* begin, T* end) {
        T out_sum = 0;
        for (T* p = begin; p <= end; p++) {
            out_sum += *p;
        }
        return out_sum;
    }

    template <typename T>
    T sum_lmd(T* begin, T* end, T& (*access_lmd)(T*)) {
        T out_sum = 0;
        for (T* p = begin; p <= end; p++) {
            out_sum += access_lmd(p);
        }
        return out_sum;
    }

    template <typename T>
    void qsort(T* buffer, u32 len, bool (*greater_lmd)(T*, T*)) {

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
        assert(("Index out of range", index < capacity));
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
};

template <typename T>
using dbuff = DynamicBuffer<T>;

using dbuffu = DynamicBuffer<u32>;
using dbuffi = DynamicBuffer<i32>;
using dbufff = DynamicBuffer<f32>;
using dbuffd = DynamicBuffer<f64>;
using dbuffb = DynamicBuffer<bool>;

}
