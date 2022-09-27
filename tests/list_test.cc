#include "../list.cc"
#include "../string.cc"

using namespace cp;

int main() {
    List<str> l; init(&l);
    add(&l, str{"sfaf"}, 0);
    print(&l);
}