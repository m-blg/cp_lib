#pragma once

#include "mbgldef.h"
#include <cassert>

namespace cp {
    
    template <typename T>
    inline T min(T first, T second) {
        return ((first < second) ? first : second);
    }

    template <typename T>
    inline T max(T first, T second) {
        return ((first > second) ? first : second);
    }

    template <typename T>
    inline void swap(T *first, T *second) {
        T temp = *first;
        *first = *second;
        *second = temp;
    }

    //inline void dcheck(const char* msg, bool condition) {
//#ifndef CP_NO_CHECK
        //assert((msg, condition));
//#endif
    //}
}
