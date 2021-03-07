

#pragma once

#include "mbgldef.h"
#include "memory.cc"
#include <string.h>
#include <cassert>

namespace cp {

template <typename T>
void dresize(T* *buffer, u32 *cap, u32 new_capacity) {
    *buffer = m_ralloc(*buffer, new_capacity);
    *cap = new_capacity;
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

template <typename... Args>
void cpy_values(void* buffer, Args... args) {
    cpy_values(buffer, args...);
}


template <typename t_first, typename... Args>
void cpy_values(void* buffer, t_first first_arg, Args... args) {
    *(t_first*)buffer = first_arg;
    cpy_values((u8*)buffer + sizeof(t_first), args...);
}

// wrapper arround T[t_cap], t_cap - buffer capa in items
template <typename T, u32 t_cap>
struct Static_Buffer {
    T buffer[t_cap];

    T& operator[](u32 index) {
        assert(("Index out of range", index < t_cap));
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
u32 cap(sbuff<T, t_cap> *buffer) { return t_cap; }
template <typename T, u32 t_cap>
T* begin(sbuff<T, t_cap> *buffer) { return buffer->buffer; }
template <typename T, u32 t_cap>
T* end(sbuff<T, t_cap> *buffer) { return buffer->buffer + t_cap; }

template <typename T, u32 t_cap>
void print(Static_Buffer<T, t_cap> *self, const char* item_fmt) {
    print(self->buffer, t_cap, item_fmt);
}


template <typename T>
struct Dynamic_Buffer {
    T* buffer;
    u32 cap; // in items

    void init(u32 init_cap = 0) { 
        cap = init_cap; 
        buffer = m_alloc<T>(init_cap); 
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
using dbuff = Dynamic_Buffer<T>;

using dbuffu = Dynamic_Buffer<u32>;
using dbuffi = Dynamic_Buffer<i32>;
using dbufff = Dynamic_Buffer<f32>;
using dbuffd = Dynamic_Buffer<f64>;
using dbuffb = Dynamic_Buffer<bool>;


template <typename T>
u32 cap(dbuff<T> *buffer) { return buffer->cap; }
template <typename T>
T* begin(dbuff<T> *buffer) { return buffer->buffer; }
template <typename T>
T* end(dbuff<T> *buffer) { return buffer->buffer + buffer->cap; }

template <typename T, u32 t_cap>
Dynamic_Buffer<T> to_dbuff(sbuff<T, t_cap> *buffer) {
    return { buffer->buffer, t_cap };
}


// methods
template <typename T>
void dresize(Dynamic_Buffer<T>* self, u32 new_capacity) {
    dresize(&self->buffer, &self->cap, new_capacity);
}

template <typename T>
T sum(Dynamic_Buffer<T> self) {
    T out_sum = 0;
    T* endp = self.buffer + self.cap;
    for (T* p = self.buffer; p < endp; p++) {
        out_sum += *p;
    }
    return out_sum;
}

template <typename T>
T sum_lmd(dbuff<T> buffer, T& (*access_lmd)(T*)) {
    T out_sum = 0;
    T* endp = end(&buffer);
    for (T* p = begin(&buffer); p < endp; p++) {
        out_sum += access_lmd(p);
    }
    return out_sum;
}


template <typename T>
void print(Dynamic_Buffer<T> self, const char* item_fmt) {
    print(self->buffer, self->cap, item_fmt);
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
        buffer = m_alloc<T>(total_cap);
    }
    void shut() {
        free(buffer);
        *this = {};
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

template <typename T, u32 t_dim_count>
u32 total_cap(Dynamic_Buffer_N<T, t_dim_count> *buffer) {
    u32 total_cap = 1;
    for (u32 it : buffer->caps) {
        total_cap *= it;
    }
    return total_cap;
}



template <typename T>
struct Dynamic_Buffer2 {
    T* buffer;
    u32 y_cap; // rows
    u32 x_cap; // collumns

    void init(u32 init_y_cap, u32 init_x_cap) {
        y_cap = init_y_cap;
        x_cap = init_x_cap;
        buffer = m_alloc<T>(y_cap* x_cap);
    }
    void init_const(u32 init_y_cap, u32 init_x_cap, T value) {
        y_cap = init_y_cap;
        x_cap = init_x_cap;
        buffer = m_alloc<T>(y_cap * x_cap);
        T* endp = buffer + y_cap * x_cap;
        for (T* p = buffer; p < endp; p++) {
            *p = value;
        }
    }

    void shut() {
        free(buffer);
        *this = {};
    }

    T& get(u32 y_index, u32 x_index) {
        return buffer[x_cap* y_index + x_index];
    }
    bool sget(T* *out_p, u32 y_index, u32 x_index) {
        if (y_index < y_cap && x_index < x_cap){
            *out_p = &buffer[x_cap* y_index + x_index];
            return true;
        }
        return false;
    }

};

template <typename T>
using dbuff2 = Dynamic_Buffer2<T>;

using dbuff2u = Dynamic_Buffer2<u32>;
using dbuff2i = Dynamic_Buffer2<i32>;
using dbuff2f = Dynamic_Buffer2<f32>;
using dbuff2d = Dynamic_Buffer2<f64>;
using dbuff2b = Dynamic_Buffer2<bool>;


template<typename T>
u32 total_cap(dbuff2<T> *buffer) {
    return buffer->y_cap * buffer->x_cap;
}

template<typename T>
T* begin(dbuff2<T> *buffer) {
    return buffer->buffer;
}

template<typename T>
T* end(dbuff2<T> *buffer) {
    return buffer->buffer + total_cap(buffer);
}


template<typename T>
void scan(Dynamic_Buffer2<T> *self, const char* item_fmt) {
    scan(self->buffer, self->total_capacity(), item_fmt);
}


template<typename T>
void print(Dynamic_Buffer2<T> *self, const char* item_fmt, const char* row_delim="\n") {
    u32 len = self->total_capacity();
    for (u32 i = 0; i < len; i++) {
        printf(item_fmt, self->buffer[i]);

        if ((i % self->x_cap) == self->x_cap- 1)
            printf(row_delim);
    }
}


template <typename T>
auto& _get(u32 index, void* buffer) {
    if (index != 0) {
        assert(("Index out of bounds", false));
    }
    return *(T*)buffer;
}

template <typename T, typename... Gargs>
auto& _get(u32 index, void* buffer) {
    if (index == 0) {
        return *(T*)buffer;
    }

    return _get<Gargs...>(index - 1, (u8*)buffer + sizeof(T));
}

template <typename... Args>
struct Tupple {
private:

public:
    void* buffer;
    
    auto& get(u32 index) {
        return _get<Args...>(index, buffer);
    }
};

template <typename T, typename... Args>
struct Tupple<T, Args...> {
private:
    Tupple<Args...> next;

    auto& _get(u32 index, void* buffer) {
        if (index == 0) {
            return *(T*)buffer;
        }

        return next._get(index - 1, (u8*)buffer + sizeof(T));
    }

};

template <>
struct Tupple<> {
    auto& _get(u32 index, void* buffer) {
        assert(("Index out of bounds", false));
        return *(u8*)buffer;
    }
};


struct Dynamic_Element_Size_Buffer {
    dbuff<u8> buffer;
    u32 stride;

    void init(u32 init_cap) { buffer.init(init_cap); }
    void shut() { buffer.shut(); }

    u8& operator[](u32 index) {
        return *(buffer.buffer + stride * index);
    }
};

using desbuff = Dynamic_Element_Size_Buffer;



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
