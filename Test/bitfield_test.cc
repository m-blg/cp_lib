#include "../bitfield.cc"

using namespace cp;

int main() {
    dbitfld bf;
    init_bits(&bf);
    for (i32 i = 0; i < 10000; i++) {
        dpush_bit(&bf, 0);
    }

    darri b;
    init(&b, 0);
    for (i32 i = 0; i < 10000; i++) {
        push(&b, 0);
    }
}