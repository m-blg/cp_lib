#include "../basic.cc"

using namespace cp;

void test_dcheck() {
#define dcheck(x, y)
    dcheck("No check", false);
#undef dcheck(x, y)

    dcheck("Check", false);
}

int main() {
    test_dcheck();
}
