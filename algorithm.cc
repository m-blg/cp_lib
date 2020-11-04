#pragma once

#include "basic.cc"
#include "array.cc"


namespace cp {

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
    void bubble_sort(T* begin, T* end, bool (*less_lmd)(T*, T*)) {
        bool was_permutations = false;
        do {
            was_permutations = false;
            for (T* p = begin; p < end - 1; p++) {
                if (less_lmd(p + 1, p)) {
                    swap(p, p + 1);
                    was_permutations = true;
                }
            }
        } while (was_permutations);
    }
    
    template <typename T>
    void qsort(T* first, T* last, bool (*greater_lmd)(T*, T*)) {

        struct BoundPack {
            T* first;
            T* last;
        };

        darr<BoundPack> stack;
        stack.init(0);
        stack.dpush({first, last});

        //if ()
        
    }

}
