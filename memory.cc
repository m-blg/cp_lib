#include "mbgldef.h"
#include "stdlib.h"

namespace cp {

template <typename T>
T* alloc(u32 count) {
    return (T*)malloc(count * sizeof(T));
}

#define alloci(x) alloc<int>((x))
#define allocl(x) alloc<long>((x))
#define allocf(x) alloc<float>((x))
#define allocd(x) alloc<double>((x))

template <typename T>
struct UniquePointer {
    T* _ptr;

    ~UniquePointer() { free(_ptr); }
    
    T* operator->() {
        return _ptr;
    }
    T& operator*() {
        return &_ptr;
    }
};

template <typename T>
using uptr = UniquePointer<T>;

}