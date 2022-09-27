#include "../io.cc"
#include "../array.cc"

using namespace cp;

i32& a_lmd(i32* p) {
    return *p;
}



template <
    class T, 
    class base_buff_t>
struct arr {
    base_buff_t buffer;
    u32 len;
};

template <class T>
using darr2 = arr<T, dbuff<T>>;
template <class T, u32 t_cap>
using sarr2 = arr<T, sbuff<T, t_cap>>;

namespace cp {






}


using namespace cp;

int main() {
    // Dynamic_Buffer_N<i32, 4> items;
    // items.init({5, 6, 7, 8});
    // items.get({2, 2, 3, 1}) = -7;

    // printf("total_cap: %u, item: %i\n", items.total_cap(), items.get({2, 2, 3, 1}));

    // sbuffi<3> b = {3, 5, 6};
    // sbuffi<3> c = b;
    // b[0] = 0;
    // c[1] = 7;
    //printf("sum: %i", buff_sum_lmd({b.buffer, cap(&b)}, a_lmd));
    //printf("sum: %i", buff_sum_lmd(to_dbuff(&c), a_lmd));


    darr<i32> a1;

    auto a2 = copy(to_dbuff(a1));

    auto b = pack(1, 2, 3);

    i32 a = foldl([](i32 acc, i32 *x){return acc + *x;}, 0, pack(1, 2, 3));
    print(a, "\n");

    darr<i32> ar1; init(&ar1, 3);
    i32 _b[3] {1, 2, 3};
    darr<i32> l1; init(&l1, 3); l1.len = 3;
    ar1 = foldl([](auto acc, auto *x){push(&acc, *x); return acc;}, 
        ar1, pack(1, 2, 3));

    darr<i32> ar2; init(&ar2, 3);
    ar2 = foldr([](auto *x, darr<i32> acc){push(&acc, *x); return acc;}, 
        ar2, dbuff<i32>{_b, 3});
    print(ar1, "\n");
    print(ar2, "\n");

}
