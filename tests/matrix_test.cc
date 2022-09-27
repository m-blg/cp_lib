#include "../src/matrix.cc"
#include "../src/io.cc"

using namespace cp;

int main() {
    mat4f m = {
        11, 12, 13, 14,
        21, 22, 23, 24,
        31, 32, 33, 34,
        41, 42, 43, 44
    };

    mat4f m2 = m.T();
    auto m3 = m + m2;
    mat2f m4 = mat2f::id();
    //println(m4);
    
    return 0;
}
