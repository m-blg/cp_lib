#pragma once

#include "mbgldef.h"
#include "memory.cc"
#include <string.h>
#include <cassert>

namespace cp {


template <typename T>
void buff_dresize(T* *buffer, u32 *cap, u32 new_capacity) {
    *buffer = m::ralloc(*buffer, new_capacity);
    *cap = new_capacity;
}

template <typename T>
void buff_scan(T* buffer, u32 len, const char* item_fmt) {
    T* p = buffer;
    T* ep = buffer + len;
    for (; p < ep; p++) {
        scanf(item_fmt, p);
    }
}

template <typename T>
void buff_print(T* buffer, u32 len, const char* item_fmt) {
    T* endp = buffer + len;
    for (T* p = buffer; p < endp; p++) {
        printf(item_fmt, *p);
    }
}


// wrapper arround T[t_cap], t_cap - buffer capa in items
template <typename T, u32 t_cap>
struct Static_Buffer {
    T buffer[t_cap];

    constexpr u32 cap() { return t_cap; }
    constexpr T* begin() { return buffer; }
    constexpr T* end() { return buffer + t_cap; }

    T& operator[](u32 index) {
        assert(("Index out of range", 0 <= index < t_cap));
        return buffer[index];
    }

};

template <typename T, u32 t_cap>
using sbuff = Static_Buffer<T, t_cap>;

template <u32 t_cap>
using sbuffu = Static_Buffer<u32, t_cap>;
template <u32 t_cap>
using sbuffi = Static_Buffer<i32, t_cap>;
template <u32 t_cap>
using sbufff = Static_Buffer<f32, t_cap>;
template <u32 t_cap>
using sbuffd = Static_Buffer<f64, t_cap>;
template <u32 t_cap>
using sbuffb = Static_Buffer<bool, t_cap>;


template <typename T, u32 t_cap>
void sbuff_print(Static_Buffer<T, t_cap> *self, const char* item_fmt) {
    buff_print(self->buffer, t_cap, item_fmt);
}



template <typename T>
struct Dynamic_Buffer {
    T* buffer;
    u32 cap; // in items
    T* begin() { return buffer; }
    T* end() { return buffer + cap; }

    void init(u32 init_cap = 0) { 
        cap = init_cap; 
        buffer = m::alloc<T>(init_cap); 
    }
    void shut() { free(buffer); cap = 0; }

    T& operator[](u32 index) {
        assert(("Index out of range", 0 <= index < cap));
        return buffer[index];
    }

};

template <typename T>
using dbuff = Dynamic_Buffer<T>;

using dbuffu = Dynamic_Buffer<u32>;
using dbuffi = Dynamic_Buffer<i32>;
using dbufff = Dynamic_Buffer<f32>;
using dbuffd = Dynamic_Buffer<f64>;
using dbuffb = Dynamic_Buffer<bool>;


// methods
template <typename T>
void dbuff_dresize(Dynamic_Buffer<T>* self, u32 new_capacity) {
    buff_dresize(&self->buffer, &self->cap, new_capacity);
}

template <typename T>
T dbuff_sum(Dynamic_Buffer<T> self) {
    T out_sum = 0;
    T* endp = self.buffer + self.cap;
    for (T* p = self.buffer; p < endp; p++) {
        out_sum += *p;
    }
    return out_sum;
}

template <typename T>
T dbuff_sum_lmd(Dynamic_Buffer<T> self, T& (*access_lmd)(T*)) {
    T out_sum = 0;
    T* endp = self.buffer + self.cap;
    for (T* p = self.buffer; p < endp; p++) {
        out_sum += access_lmd(p);
    }
    return out_sum;
}

template <typename T>
void dbuff_print(Dynamic_Buffer<T> self, const char* item_fmt) {
    buff_print(self->buffer, self->cap, item_fmt);
}

template <typename T, u32 t_dim_count>
struct Dynamic_Buffer_N {
    T* buffer;
    u32 caps[t_dim_count];

    void init(sbuffu<t_dim_count> new_caps) {
        memcpy(caps, new_caps.buffer, t_dim_count * sizeof(u32));

        u32 total_cap = 1;
        for (u32 it : caps) {
            total_cap *= it;
        }
        buffer = m::alloc<T>(total_cap);
    }

    u32 total_cap() {
        u32 total_cap = 1;
        for (u32 it : caps) {
            total_cap *= it;
        }
        return total_cap;
    }

    T& get(sbuffu<t_dim_count> indexes) {
        u32 global_index = 0u;
        for (u32 i = 0; i < t_dim_count - 1; i++) {
            global_index += indexes[i] * caps[i];
        }
        global_index += indexes[t_dim_count - 1];
        return buffer[global_index];
    }
};

template <typename T>
struct DynamicBuffer2 {
    T* buffer;
    u32 y_cap; // rows
    u32 x_cap; // collumns

    void init(u32 init_y_capacity, u32 init_x_capacity) {
        y_cap = init_y_capacity;
        x_cap = init_x_capacity;
        buffer = m::alloc<T>(y_cap* x_cap);
    }
    void init_const(u32 init_y_capacity, u32 init_x_capacity, T value) {
        y_cap= init_y_capacity;
        x_cap= init_x_capacity;
        buffer = m::alloc<T>(y_cap * x_cap);
        T* endp = buffer + total_cap();
        for (T* p = buffer; p < endp; p++) {
            *p = value;
        }
    }


    void shut() {
        free(buffer);
    }

    u32 total_cap() {
        return y_cap* x_cap;
    }

    T& get(u32 y_index, u32 x_index) {
        return buffer[x_cap* y_index + x_index];
    }


    // Functions

    static void print(DynamicBuffer2<T> *self, const char* item_fmt, const char* row_delim="\n") {
        u32 len = self->total_capacity();
        for (u32 i = 0; i < len; i++) {
            printf(item_fmt, self->buffer[i]);

            if ((i % self->x_cap) == self->x_cap- 1)
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
void dbuff2_scan(DynamicBuffer2<T> *self, const char* item_fmt) {
    buff_scan(self->buffer, self->total_capacity(), item_fmt);
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
