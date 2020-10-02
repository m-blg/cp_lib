
#include "stdio.h"
#include "../array.cc"

using namespace cp;

void test1() {
    sbuff<int, 5> stemp = {{3, 5, 3, 5, 1}};
    array::print(stemp.buffer, stemp.capacity(), "%d ");


    dbuff<int> dtemp = {};
    dtemp.capacity = 5;
    dtemp = {};
    dtemp.init(5);
    array::print(dtemp.buffer, dtemp.capacity, "%d ");


    darr<int> a;
    {
        array::dpush_range<3>(&a, {3, 5, 3});
        array::print(&a, "%d ");
    }

    int buf[5] = {3, 5, 3, 1, 4};
}

void test_dynamic_array() {
    darr<f64> da;
    {
        da.init();
        array::dpush_range<5>(&da, {3, 2, 3, 4, 5});
        array::print(&da, "%f ");
        puts("");
    }

    darr<i32> da2;
    da2.init_range<3>(5, {3, 5, 6});
    array::print(&da2, "%d ");

    da.shut();
    da2.shut();
}

int main() {
    test_dynamic_array();
}
