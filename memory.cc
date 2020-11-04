
#pragma once
#include "mbgldef.h"
#include <stdlib.h>
#include <stdio.h>

namespace cp {

namespace memory {

template <typename T>
inline T* alloc(u32 count) {
    return (T*)malloc(count * sizeof(T));
}

template <typename T>
inline T* nalloc(u32 count) {
    return (T*)calloc(count, sizeof(T));
}

template <typename T>
inline T* ralloc(T* ptr, u32 count) {
    return (T*)realloc(ptr, count * sizeof(T));
}

#define alloci(x) alloc<int>((x))
#define allocl(x) alloc<long>((x))
#define allocf(x) alloc<float>((x))
#define allocd(x) alloc<double>((x))

template <typename T>
struct UniquePointer {
    T* ptr;

    UniquePointer() = default;
    UniquePointer(T* other) {
        ptr = other;
    }
    ~UniquePointer() { delete[] ptr; printf("Unique dealoc\n"); }
    
    T* operator=(T* other) {
        ptr = other;
        return ptr;
    }
    T* operator->() {
        return ptr;
    }
    T& operator*() {
        return *ptr;
    }
    T& operator[](u32 index) {
        return ptr[index];
    }
    
    operator T*() {
        return ptr;
    }
};

template <typename T>
using uptr = UniquePointer<T>;

}

namespace m = memory;

}
