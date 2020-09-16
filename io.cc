#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

namespace cp {

template <typename R, typename ... Types> constexpr size_t t_get_arg_count( R(*f)(Types ...)) {
   return sizeof...(Types);
}

template <typename T>
constexpr char* 

template <typename T>
void input(T* n1...) {
    va_list args;
    va_start(args, n1);

}

} // namespace cp
