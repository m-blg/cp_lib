
#include "mbgldef.h"
#include "basic.cc"
#include "memory.cc"
#include "cassert"
#include "string.h"


namespace cp {

namespace array { 


    template <typename T>
    void push(T* buffer, u32 *len, T item) { // push with value
        buffer[(*len)] = item;
        (*len)++;
    }
        
    template <typename T>
    T pop(T* buffer, u32 *len) { // remove last and return, if don't want to return, use remove(last) instead
        (*len)--;
        return buffer[(*len)];
    }

    template <typename T>
    void add(T* buffer, u32 *len, T item, u32 index) { // add with value
        T* p_target = buffer + index;
        for (T* p = buffer + (*len); p > p_target; p--) {
            *p = *(p - 1);
        }
        *p_target = item;
        (*len)++;
    }

    template <typename T>
    void remove(T* buffer, u32 *len, u32 index) {
        (*len)--;
        T* p_end = buffer + (*len);
        for (T* p = buffer + index; p < p_end; p++) {
            *p = *(p + 1);
        }
    }


    // dynamic
    template <typename T>
    void dresize(T* *buffer, u32 *capacity, u32 new_capacity) {
        *buffer = (T*)realloc(*buffer, new_capacity * sizeof(T));
        *capacity = new_capacity;
    }

    template <typename T>
    void dpush(T* *buffer, u32 *len, u32 *capacity, T item) { 
        if (*len >= *capacity) {
            dresize( buffer, capacity, max(1u, 2 * (*capacity)) );
        }
        (*buffer)[(*len)] = item;
        (*len)++;
    }

    void raw_print(i8* buffer, u32 stride, u32 len, const char* item_fmt) {
        i8* endp = buffer + stride * len;
        for (i8* p = buffer; p < endp; p += stride) {
            printf(item_fmt, *p);
        }
    }

    template <typename T>
    void print(T* buffer, u32 len, const char* item_fmt) {
        T* endp = buffer + len;
        for (T* p = buffer; p < endp; p++) {
            printf(item_fmt, *p);
        }
    }

    template <typename T>
    void scan(T* buffer, u32 len, const char* item_fmt) {
        T* p = buffer;
        T* ep = buffer + len;
        for (; p < ep; p++) {
            scanf(item_fmt, p);
        }
    }

};

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


template <typename T>
struct DynamicBuffer {
    u32 capacity; // in items
    T* buffer;
    T* begin() { return buffer; }
    T* end() { return buffer + capacity; }

    void init(u32 initial_capacity=0) { 
        capacity = initial_capacity; 
        buffer = m::alloc<T>(initial_capacity); 
    }
    void shut() { free(buffer); }

    T& operator[](u32 index) {
        assert(("Index out of range", 0 <= index < capacity));
        return buffer[index];
    }
};

template <typename T>
using dbuff = DynamicBuffer<T>;


template <typename T, u32 t_capacity>
struct StaticArray {
    u32 len;
    T buffer[t_capacity];
    
    void init() { len = 0; }
    
    constexpr u32 capacity() {
        return t_capacity;
    }
    
    T& operator[](u32 index) {
        assert(("Index out of range", 0 <= index < t_capacity));
        return buffer[index];
    }
    
};

template <typename T, u32 t_capacity>
using sarr = StaticArray<T, t_capacity>;

namespace array {
    template <typename T, u32 t_capacity>
    void push(sarr<T, t_capacity> *self, T item) {
        array::push(self->buffer, &self->len, item);
    }

    template <typename T, u32 t_capacity>
    T pop(sarr<T, t_capacity> *self) {
        return array::pop(self->buffer, &self->len);
    }

    template <typename T, u32 t_capacity>
    void add(sarr<T, t_capacity> *self, T item, u32 index) {
        array::add(self->buffer, &self->len, item, index);
    }

    template <typename T, u32 t_capacity>
    void remove(sarr<T, t_capacity> *self, u32 index) {
        array::remove(self->buffer, &self->len, index);
    }

    template <typename T, u32 t_capacity>
    void print(sarr<T, t_capacity> *self, const char* item_fmt) {
        array::print(self->buffer, self->len, item_fmt);
    }
}

template <typename T>
struct DynamicArray {
    u32 capacity; // max count of T
    u32 len;
    T* buffer;

    void init(u32 init_capacity=0) { 
        capacity = init_capacity; 
        len = 0; 
        buffer = m::alloc<T>(init_capacity); 
    }

    template <u32 t_arg_count>
    void init_range(u32 init_capacity, sbuff<T, t_arg_count>&& args) {
        capacity = init_capacity;
        len = t_arg_count;
        buffer = m::alloc<T>(init_capacity);
        memcpy(buffer, args.buffer, t_arg_count * sizeof(T));
    }

    void shut() { free(buffer); }


    T& operator[](u32 index) {
        assert(("Index out of range", 0 <= index < capacity));
        return buffer[index];
    }
};

template <typename T>
using darr = DynamicArray<T>;

namespace array {
    template <typename T>
    void push(darr<T> *self, T item) {
        array::push(self->buffer, &self->len, item);
    }

    template <typename T>
    T pop(darr<T> *self) {
        return array::pop(self->buffer, &self->len);
    }

    template <typename T>
    void add(darr<T> *self, T item, u32 index) {
        array::add(self->buffer, &self->len, item, index);
    }

    template <typename T>
    void remove(darr<T> *self, u32 index) {
        array::remove(self->buffer, &self->len, index);
    }

    template <typename T>
    void print(darr<T> *self, const char* item_fmt) {
        array::print(self->buffer, self->len, item_fmt);
    }

    template <u32 t_items_count, typename T>
    void dpush_range(darr<T> *self, sbuff<T, t_items_count>&& items) {
        if (self->len + t_items_count >= self->capacity) {
            dresize( &self->buffer, &self->capacity, max(t_items_count, 2 * (self->capacity)) );
        }

        memcpy(self->buffer, items.buffer, t_items_count * sizeof(T));
        self->len += t_items_count;
    }
}

template <typename T>
struct DynamicBuffer2 {
    u32 y_capacity; // rows
    u32 x_capacity; // collumns
    T* buffer;

    void init(u32 init_y_capacity, u32 init_x_capacity) {
        y_capacity = init_y_capacity;
        x_capacity = init_x_capacity;
        buffer = m::alloc<T>(y_capacity * x_capacity);
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
};

template <typename T>
using dbuff2 = DynamicBuffer2<T>;

namespace buffer2 {

    template<typename T>
    void scan(dbuff2<T> *self, const char* item_fmt) {
        array::scan(self->buffer, self->total_capacity(), item_fmt);
    }

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

