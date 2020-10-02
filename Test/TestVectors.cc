#include "../vectors.cc"

#include "stdio.h"

using namespace cp;

template struct Vector3<i32>;

int main() {
    vec3i v1{3, 5};
    vec3i v2{5, 1};

    vec3i v3 = v1 + v2;
    printf("%d\n", v3.u);
}