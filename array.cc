
#include "mbgldef.h"
#include "memory.cc"


namespace cp {

namespace array { 


    template <typename T>
    static void push(T* buffer, u32* len, T item) { // push with value
        buffer[(*len)] = item;
        (*len)++;
    }
        
    template <typename T>
    static void pushp(T* buffer, u32* len, T* item) { // push with pointer
        buffer[(*len)] = *item;
        (*len)++;
    }

    template <typename T>
    static T pop(T* buffer, u32* len) { // remove last and return, if don't want to return, use remove(last) instead
        (*len)--;
        return buffer[(*len)];
    }

    template <typename T>
    static void add(T* buffer, u32* len, T item, u32 index) { // add with value
        T* p_target = buffer + index;
        for (T* p = buffer + (*len); p > p_target; p--) {
            *p = *(p - 1);
        }
        *p_target = item;
        (*len)++;
    }

    template <typename T>
    static void addp(T* buffer, u32* len, T* item, u32 index) { // add with pointer
        T* p_target = buffer + index;
        for (T* p = buffer + (*len); p > p_target; p--) {
            *p = *(p - 1);
        }
        *p_target = *item;
        (*len)++;
    }

    template <typename T>
    static void remove(T* buffer, u32* len, u32 index) {
        (*len)--;
        T* p_end = buffer + (*len);
        for (T* p = buffer + index; p < p_end; p++) {
            *p = *(p + 1);
        }
    }


    template <typename T>
    void dresize(T* buffer, u32* capacity, u32 new_capacity) {
        buffer = realoc(buffer, new_capacity);
        *capacity = new_capacity;
    }

    template <typename T>
    static void dpush(T* buffer, u32* len, u32* capacity, T item) { // dynamic push with pointer
        if (len >= capacity) {
            dresize(buffer, capacity, 2 * (*capacity));
        }
        buffer[(*len)] = item;
        (*len)++;
    }

    template <typename T>
    static void dpushp(T* buffer, u32* len, u32* capacity, T* item) { // dynamic push with pointer
        if (len >= capacity) {
            dresize(buffer, capacity, 2 * (*capacity));
        }
        buffer[(*len)] = *item;
        (*len)++;
    }
};
    


template <typename T, u32 t_count>
struct StaticArray {
    u32 len;
    T buffer[t_count];
    
    u32 count() {
        return t_count;
    }
    
    void push(T* item) {
        array::push(buffer, &len, item);
    }

    T pop() {
        array::pop(buffer, &len);
    }

    void add(T* item, u32 index) {
        array::push(buffer, &len, item, index);
    }

    void remove(u32 index) {
        array::push(buffer, &len, index);
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
    T* buffer;

    DynamicArray() = default;
    DynamicArray(u32 initial_capacity)
    : capacity(initial_capacity), len(0) {
        buffer = alloc<T>(initial_capacity);
    }
    ~DynamicArray() = default;
    
    void push(T* item) {
        array::push(buffer, &len, item);
    }
    void dpush(T* item) {
        array::dpush(buffer, &len, &capacity, item);
    }

    T pop() {
        array::pop(buffer, &len);
    }

    void add(T* item, u32 index) {
        array::push(buffer, &len, item, index);
    }

    void remove(u32 index) {
        array::push(buffer, &len, index);
    }

    T last() {
        return buffer[len - 1];
    }

    T& operator[](u32 index) {
        return buffer[index];
    }
};

template <typename T>
using darr = DynamicArray<T>;

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
