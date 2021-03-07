#include "../io.cc"

using namespace cp;

int main() {
    print(1u, "\n");
    print(2, "\n");
    print(5.2, "\n");
    print(6.2f, "\n");

    print(3, 'd', "Text");
}