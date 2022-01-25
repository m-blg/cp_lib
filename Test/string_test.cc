#include "../string.cc"
#include "../io.cc"

#include <initializer_list>

using namespace cp;



// void foo(std::initializer_list<str> a) {

// }

template <u32 t_cap>
struct A {
    str buffer[t_cap];

    template <typename T, typename... Ts>
    A(T first, Ts... rest) 
    : buffer{first, rest...} {}
};

template <u32 t_a_cap>
void foo(sbuff<str, t_a_cap> a) {

}

int main() {
    // foo({"333", "33", ""});

    str s = "52525";
    s = "sfd";
    u32 c = Arg_Count<int, str, bool>::count();
    auto p = pack(3, 4, 5);

    str s2 = "sfsff";
    sstrb sb; init(&sb, 1);
    sb[0] = 'c';
    // init(&sb);
    cat(&sb, pack(s, s2));
    print(s); puts("");
    print(len(s)); puts("");

    print(to_str(sb)); puts("");

    sarr<str, 100> tokens; init(&tokens);
    // darr<str> temp = to_dbuff(&tokens);
    split(&tokens, to_str(sb), 's');
    print(tokens); puts(""); 

    cat(&sb, tokens);
    print(to_str(sb)); puts("");

    tokens.len = 0;
    split(&tokens, to_str(sb), pack('c', 'd'));
    print(tokens); puts(""); 

    A<3> a = {str{null, 2}, s2, ""};
    sbuff<str, 3> sba = {str{null, 3}, s2, ""};
    foo(pack(str{null, 3}, s2, ""));
}
