
#include "stdio.h"
#include "../array.cc"
#include "../memory.cc"

#include "iostream"

using namespace cp;

template struct ManualStaticArray<int, 1>;
template struct StaticArray<int, 1>;
template struct ManualDynamicArray<int>;
template struct DynamicArray<int>;

void Test1() {
    i32 i = 0;
    uptr<i32> iptr = alloc<i32>(5);
    for (u32 i = 0; i < 5; i++) {
        iptr[i] = i * i;
    }
    
    printf("%d\n", iptr[3]);
}

void Test2() {
    msarr<i32, 5> a; a.init();
    for (int i = 0; i < 5; i++) {
        a[i] = i + 3*i;
    }
    a.len += 5;
    
    array::print("%d ", a.buffer, a.len);
    a.print("%d ");
    
}

void Test3() {
    darr<int> a(5);
    
    for (int i = 0; i < 5; i++) {
        a.push(i + 3*i);
    }
    for (int i = 0; i < 5; i++) {
        printf("%d ", a[i]);
    }
    puts("");
    array::print("%d ", a.buffer.ptr, a.len);
    a.print("%d ");
    puts("");
}

void Test4() {
    darr<float> a;

    for (int i = 1; i <= 10; i++) {
        a.dpush(3.5f * i);
    }
    
    a.print("%f ");
    
}

int main() {
    Test4();
}
