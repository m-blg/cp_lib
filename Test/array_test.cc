#include "../array.cc"
#include "../io.cc"

using namespace cp;


template <typename T>
struct A {
    typedef T type;
};

int main() {
    darr<f32> a;
    a.len = 5;
    auto ap = &a;
    init(ap, 3);
    u32 c = cap(&a);
    auto e = end(&a);
    a = {null, 3, 3};
    a = {};
    resize(&a, 3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    f32 total = sum(a);
    print(total);
    A<f32>::type b = 5;
    print(b);
}
