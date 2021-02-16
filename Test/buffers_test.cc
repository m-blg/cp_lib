#include "../buffer2.cc"

using namespace cp;

i32& a_lmd(i32* p) {
    return *p;
}

int main() {
    // Dynamic_Buffer_N<i32, 4> items;
    // items.init({5, 6, 7, 8});
    // items.get({2, 2, 3, 1}) = -7;

    // printf("total_cap: %u, item: %i\n", items.total_cap(), items.get({2, 2, 3, 1}));

    sbuffi<3> b = {3, 5, 6};
    sbuffi<3> c = b;
    b[0] = 0;
    c[1] = 7;
    printf("sum: %i", buff_sum_lmd({b.buffer, cap(&b)}, a_lmd));
    printf("sum: %i", buff_sum_lmd(to_dbuff(&c), a_lmd));
}
