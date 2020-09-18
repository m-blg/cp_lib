
#include "mbgldef.h"
#include "basic.cc"
#include "memory.cc"


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

    template <typename T>
    void dpushp(T* buffer, u32 *len, u32 *capacity, T *item) { // dynamic push with pointer
        if (len >= capacity) {
            dresize(buffer, capacity, 2 * (*capacity));
        }
        buffer[(*len)] = *item;
        (*len)++;
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
    


template <typename T, u32 t_count>
struct ManualStaticArray {
    u32 len;
    T buffer[t_count];
    
    void init() { len = 0; }
    
    u32 count() {
        return t_count;
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
        return buffer[index];
    }
    
};

template <typename T, u32 t_count>
using msarr = ManualStaticArray<T, t_count>;

template <typename T, u32 t_count>
struct StaticArray {
    u32 len;
    T buffer[t_count];
    
    StaticArray() 
    : len(0) {} 

    void init() { len = 0; }
    
    u32 count() {
        return t_count;
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
        return buffer[index];
    }
};

template <typename T, u32 t_count>
using sarr = StaticArray<T, t_count>;


template <typename T>
struct DynamicArray {
    u32 capacity; // max count of T
    u32 len;
    uptr<T> buffer;

    DynamicArray() 
    : capacity(0), len(0), buffer(null) {}
    DynamicArray(u32 initial_capacity)
    : capacity(initial_capacity), len(0) {
        buffer = alloc<T>(initial_capacity);
    }
    ~DynamicArray() = default;
    
    void push(T item) {
        array::push(buffer.ptr, &len, item);
    }
    void dpush(T item) {
        array::dpush(&buffer.ptr, &len, &capacity, item);
    }

    T pop() {
        return array::pop(buffer.ptr, &len);
    }

    void add(T item, u32 index) {
        array::add(buffer.ptr, &len, item, index);
    }

    void remove(u32 index) {
        array::remove(buffer.ptr, &len, index);
    }

    T last() {
        return buffer[len - 1];
    }

    void print(const char* item_fmt) {
        array::print(item_fmt, buffer.ptr, len);
    }

    T& operator[](u32 index) {
        return buffer[index];
    }
};

template <typename T>
using darr = DynamicArray<T>;


template <typename T>
struct ManualDynamicArray {
    u32 capacity; // max count of T
    u32 len;
    T* buffer;

    static ManualDynamicArray qinit(u32 initial_capacity) {
        ManualDynamicArray arr = {initial_capacity, 0, alloc<T>(initial_capacity)};
        return arr;
    }
    
    void init(u32 initial_capacity) { 
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
        return buffer[index];
    }
};

template <typename T>
using mdarr = ManualDynamicArray<T>;

}
//template <typename T>
//void static_array_push_back(void* array, T value) {
    //static_array_push_back();
    //static_array_insert();
    //static_array_append();
    //static_array_do_some_fansy_stuff();
    //staticArrayDoSomeFansyStuff();
//}

//void staticArrayPushBack() {
    //staticArrayPushBack();
    //staticArrayInsert();
    //staticArrayAppend();
//}
