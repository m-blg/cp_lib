
#include "mbgldef.h"
#include "basic.cc"
#include "memory.cc"
#include "cassert"


namespace cp {

namespace array { 


    template <typename T>
    void push(T* buffer, u32 *len, T item) { // push with value
        buffer[(*len)] = item;
        (*len)++;
    }
        
    template <typename T>
    void pushp(T* buffer, u32 *len, T *item) { // push with pointer
        buffer[(*len)] = *item;
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
    void addp(T* buffer, u32 *len, T *item, u32 index) { // add with pointer
        T* p_target = buffer + index;
        for (T* p = buffer + (*len); p > p_target; p--) {
            *p = *(p - 1);
        }
        *p_target = *item;
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
        *buffer = (T*)realloc(*buffer, new_capacity);
        *capacity = new_capacity;
    }

    template <typename T>
    void dpush(T* *buffer, u32 *len, u32 *capacity, T item) { // dynamic push with pointer
        if (len >= capacity) {
            dresize( buffer, capacity, max(1u, 2 * (*capacity)) );
        }
        (*buffer)[(*len)] = item;
        (*len)++;
    }

    //template <typename T>
    //void dpushp(T* buffer, u32 *len, u32 *capacity, T *item) { // dynamic push with pointer
        //if (len >= capacity) {
            //dresize(buffer, capacity, 2 * (*capacity));
        //}
        //buffer[(*len)] = *item;
        //(*len)++;
    //}

    template <typename T>
    void dpush_range(T* *buffer, u32 *len, u32 *capacity, T* items, u32 items_count) {
        T* p_items_end = items + items_count;
        for (T* p = items; p < p_items_end; p++) {
            dpush(buffer, len, capacity, *p);
        }
    }

    void raw_print(const char* item_fmt, i8* buffer, u32 stride, u32 len) {
        i8* endp = buffer + stride * len;
        for (i8* p = buffer; p < endp; p += stride) {
            printf(item_fmt, *p);
        }
    }

    template <typename T>
    void print(const char* item_fmt, T* buffer, u32 len) {
        T* endp = buffer + len;
        for (T* p = buffer; p < endp; p++) {
            printf(item_fmt, *p);
        }
    }

};

// wrapper arround T[t_capacity], t_capacity - buffer capacity in items
template <typename T, u32 t_capacity>
struct StaticBuffer {
    T buffer[t_capacity];

    u32 capacity() { return t_capacity; }
    T* begin() { return buffer; }
    T* end() { return buffer + t_capacity; }

    T& operator[](u32 index) {
        assert(("Index out of range", 0 <= index < t_capacity));
        return buffer[index];
    }
};

template <typename T, u32 t_capacity>
using sbuf = StaticBuffer<T, t_capacity>;


template <typename T>
struct DynamicBuffer {
    u32 capacity; // in items
    T* buffer;
    T* begin() { return buffer; }
    T* end() { return buffer + capacity; }

    void init(u32 initial_capacity=0) { 
        capacity = initial_capacity; 
        buffer = alloc<T>(initial_capacity); 
    }
    void shut() { free(buffer); }

    T& operator[](u32 index) {
        assert(("Index out of range", 0 <= index < capacity));
        return buffer[index];
    }
};

template <typename T>
using dbuf = DynamicBuffer<T>;

/*namespace buffer {*/
/*template <typename T, u32 t_capacity>*/
/*T *static_buffer_get(StaticBuffer<T, t_capacity> *buffer, u32 index) {*/
/*#if CP_DEBUG*/
    /*assert()*/
/*#endif*/
    /*return buffer->ptr[index];*/
/*}*/
/*}*/

template <typename T, u32 t_capacity>
struct StaticArray {
    u32 len;
    T buffer[t_capacity];
    
    void init() { len = 0; }
    
    u32 capacity() {
        return t_capacity;
    }
    
    void push(T item) {
        array::push(buffer, &len, item);
    }

    T pop() {
        return array::pop(buffer, &len);
    }

    void add(T item, u32 index) {
        array::add(buffer, &len, item, index);
    }

    void remove(u32 index) {
        array::remove(buffer, &len, index);
    }

    void print(const char* item_fmt) {
        array::print(item_fmt, buffer, len);
    }

    T& operator[](u32 index) {
        assert(("Index out of range", 0 <= index < t_capacity));
        return buffer[index];
    }
    
};

template <typename T, u32 t_capacity>
using sarr = StaticArray<T, t_capacity>;


template <typename T>
struct DynamicArray {
    u32 capacity; // max count of T
    u32 len;
    T* buffer;

    void init(u32 initial_capacity=0) { 
        capacity = initial_capacity; 
        len = 0; 
        buffer = alloc<T>(initial_capacity); 
    }
    void shut() { free(buffer); }
    
    void push(T item) {
        array::push(buffer, &len, item);
    }
    void dpush(T item) {
        array::dpush(&buffer, &len, &capacity, item);
    }

    T pop() {
        return array::pop(buffer, &len);
    }

    void add(T item, u32 index) {
        array::add(buffer, &len, item, index);
    }

    void remove(u32 index) {
        array::remove(buffer, &len, index);
    }

    T last() {
        return buffer[len - 1];
    }

    void print(const char* item_fmt) {
        array::print(item_fmt, buffer, len);
    }

    T& operator[](u32 index) {
        assert(("Index out of range", 0 <= index < capacity));
        return buffer[index];
    }
};

template <typename T>
using darr = DynamicArray<T>;

namespace array {

    template <typename T, u32 t_items_count>
    void dpush_range(darr<T> *array, sbuf<T, t_items_count> *items) {
        T* p_items_end = items->buffer + items->capacity();
        for (T* p = items; p < p_items_end; p++) {
            dpush(array->buffer, array->len, array->capacity, *p);
        }
    }

    template <typename T, u32 t_items_count>
    void dpush_range2(darr<T> *array, T items[t_items_count]) {
        T* p_items_end = items + t_items_count;
        for (T* p = items; p < p_items_end; p++) {
            dpush(array->buffer, array->len, array->capacity, *p);
        }
    }


}

}
