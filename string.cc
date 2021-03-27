
#include "array.cc"

namespace cp {

template <u32 t_cap>
using Static_String = Static_Array<char, t_cap>;

template <u32 t_cap>
using sstr = Static_String<t_cap>;


using Dynamic_String = Dynamic_Array<char>;

using dstr = Dynamic_String;

}
