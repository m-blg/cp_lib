
#include "mbgldef.h"

template <i32 t_count>
struct StackString {
    
    char buffer[t_count];
    u32 len;

    inline i32 count() {
        return t_count;
    }
};


int main() {

}
