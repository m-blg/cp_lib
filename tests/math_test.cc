#include "../math.cc"
#include "math.h"

using namespace cp;

void test1() {
    dbufff domain  = get_range<f32>(-2, 5, 10000);
    dbufff range;
    range.init(domain.capacity);
    get_func_range(domain, range, sin);
    f32 res = integrate(range, -2.0f, 5.0f);
    printf("%f\n", res);
}

f32 x_func(f32 x) {
    return x;
}

f64 const_func(f64 x) {
    return 5;
}

void test2() {
    dbuff<f64> domain  = get_range<f64>(-2, 5, 1000000);
    dbuff<f64> range;
    range.init(domain.capacity);
    get_func_range(domain, range, sin);
    f64 res = integrate(range, -2.0, 5.0);
    printf("%f\n", res);
}

void test3() {
    f64 res = integrate(sin, -2.0, 5.0, 1000000);
    printf("%f\n", res);
}

int main() {
    test3();
}
