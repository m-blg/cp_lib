
#include "stdio.h"
#include "../array.cc"

using namespace cp;

void test1() {
    sbuf<int, 5> stemp = {{3, 5, 3, 5, 1}};
    array::print("%d ", stemp.buffer, stemp.capacity());


    dbuf<int> dtemp = {};
    dtemp.capacity = 5;
    dtemp = {};
    dtemp.init(5);
    array::print("%d ", dtemp.buffer, dtemp.capacity);


    darr<int> a;
    sbuf<int, 3> t = {3, 5, 3}; 
    array::dpush_range(&a, &t);
    a.print("%d ");

    int buf[5] = {3, 5, 3, 1, 4};
}

template <u32 t_items_count>
u32 foo(sbuf<int, t_items_count> a) {
    return t_items_count;
}

int main() {
    test1();
}
