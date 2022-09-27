#include "../array.cc"

using namespace cp;

struct A {
    i32 field;
};

void do_on_A(A obj) {
    puts("do_on_A");
}
void poly_do(A obj) {
    puts("poly_do A");
}

using B = A;

void do_on_B(B obj) {
    puts("do_on_B");
}

// void poly_do(B obj) {
//     puts("poly_do B");
// }
// not working

int main() {
    A a;
    B b;
    do_on_A(a);
    do_on_A(b);
}