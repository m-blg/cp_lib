#include "../array.cc"

using namespace cp;

int main() {
    darr<f32> a;
    a.len = 5;
    auto ap = &a;
    ap->init(3);
    u32 c = cap(&a);
    auto e = end(&a);
    a = {null, 3, 3};
}