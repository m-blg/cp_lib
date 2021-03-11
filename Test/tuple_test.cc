#include "../buffer.cc"
#include "../vector.cc"

using namespace cp;

// void test1() {
//         // Tuple<i32, f32, bool> t;
//     // t.get<0>();
//     u8 b[100];
//     u8* p = b;
//     cpy_values(b, 3, 3.5f, 's');
//     printf("%i\n", *(i32*)p); p += sizeof(i32);
//     printf("%f\n", *(f32*)p); p += sizeof(f32);
//     printf("%c\n", *(char*)p); p += sizeof(char);

//     Memory_Layout<i32, f32, char> ml;
//     i32* p0 = &get_value<i32>(ml, b, 0);
//     f32* p1 = &get_value<f32>(ml, b, 1);
//     get_value<f32>(ml, b, 1) = 5;
//     get_value<char>(ml, b, 2) = 'c';

//     p = b;
//     printf("%i\n", *(i32*)p); p += sizeof(i32);
//     printf("%f\n", *(f32*)p); p += sizeof(f32);
//     printf("%c\n", *(char*)p); p += sizeof(char);
// }

void test2() {
    // printf("%i\n", _ML_Size<2, i32, f32, bool>::size);

    u8 b[100];
    u8* p = b;
    cpy_values(b, 3, 3.5f, 's');
    printf("%i\n", *(i32*)p); p += sizeof(i32);
    printf("%f\n", *(f32*)p); p += sizeof(f32);
    printf("%c\n", *(char*)p); p += sizeof(char);

    auto ml = (Memory_Layout<i32, f32, char>*)b;
    i32* p0 = &get_value<0>(ml);
    f32* p1 = &get_value<1>(ml);
    get_value<0>(ml) = 5.7;
    get_value<1>(ml) = 6.7;
    get_value<2>(ml) = 'c';

    p = b;
    printf("%i\n", *(i32*)p); p += sizeof(i32);
    printf("%f\n", *(f32*)p); p += sizeof(f32);
    printf("%c\n", *(char*)p); p += sizeof(char);
}

struct A {
    i32 a;
    i64 b;
    char x;
};

void test3() {
    u8 b[100];
    u8* p = b;
    cpy_values(b, 3, 3.5f, 's');
    printf("%i\n", *(i32*)p); p += sizeof(i32);
    printf("%f\n", *(f32*)p); p += sizeof(f32);
    printf("%c\n", *(char*)p); p += sizeof(char);

    p = b;  
    auto t = (Tuple<i32, f32, char>*)p;
    t->get<0>() = 6.1;
    t->get<1>() = 5.4;
    t->get<2>() = 'c'; 

    
    printf("%i\n", *(i32*)p); p += sizeof(i32);
    printf("%f\n", *(f32*)p); p += sizeof(f32);
    printf("%c\n", *(char*)p); p += sizeof(char);
    puts("");
    printf("%i\n", sizeof(*t));
    printf("%i\n", sizeof(A));

}

int main() {
    test3();
    Tuple<i32, f32> t = {1, 3.5f};
    Tuple<vec2i, vec2f> t2 = { {1, 3}, {{3, 5.5}} };
}