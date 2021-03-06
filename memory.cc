
#pragma once
#include "mbgldef.h"
#include <stdlib.h>
#include <stdio.h>

namespace cp {


template <typename T>
inline T* m_alloc(u32 count) {
    return (T*)malloc(count * sizeof(T));
}

template <typename T>
inline T* m_nalloc(u32 count) {
    return (T*)calloc(count, sizeof(T));
}

template <typename T>
inline T* m_ralloc(T* ptr, u32 count) {
    return (T*)realloc(ptr, count * sizeof(T));
}

template <typename T>
inline T* m_salloc(u32 count) {
    return (T*)alloca(count * sizeof(T));
}


#define alloci(x) alloc<int>((x))
#define allocl(x) alloc<long>((x))
#define allocf(x) alloc<float>((x))
#define allocd(x) alloc<double>((x))



}
