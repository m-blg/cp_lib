#pragma once

#include "mbgldef.h"
#include "basic.cc"
#include "array.cc"
#include "memory.cc"
#include <cassert>

namespace cp {



constexpr u32 bitfld_t_byte_count(u32 t_bit_count) {
    u32 div = t_bit_count / 8u;
    u32 mod = t_bit_count % 8u;
    return (mod ? div + 1 : div);
}

inline bool bitfld_get_bit(u8* buffer, u32 bit_index) {
    return buffer[bit_index / 8u] & (1u << (7u - bit_index % 8u));
}

inline void bitfld_set_bit_high(u8* buffer, u32 bit_index) {
    buffer[bit_index / 8u] |= (1u << (7u - bit_index % 8u)); 
}

inline void bitfld_set_bit_low(u8* buffer, u32 bit_index) {
    buffer[bit_index / 8u] &= ~(1u << (7u - bit_index % 8u)); 
}

inline void bitfld_flip_bit(u8* buffer, u32 bit_index) {
    buffer[bit_index / 8u] ^= (1u << (7u - bit_index % 8u)); 
}

inline void bitfld_set_bit(u8* buffer, u32 bit_index, bool value) {
    if (bitfld_get_bit(buffer, bit_index) != value) {
        bitfld_flip_bit(buffer, bit_index);
    }
}

inline int bitfld_cmp_bits(u8* first, u8* second, u32 bit_count) {
    for (u32 i = 0; i < bit_count; i++) {
        if (bitfld_get_bit(first, i) != bitfld_get_bit(second, i)) {
            return (bitfld_get_bit(first, i) ? 1 : -1);
        }
    }
    return 0;
}

inline void bitfld_print_bits(u8* buffer, u32 bit_count) {
    for (i32 i = 0; i < bit_count; i++) {
        printf("%d", bitfld_get_bit(buffer, i));
    }
}
    

template <u32 t_bit_count>
struct Static_Bit_Field {
    u8 buffer[bitfld_t_byte_count(t_bit_count)];

    constexpr u32 bit_count() { return t_bit_count; }
    // in bytes
    constexpr u32 capacity() { return bitfld_t_byte_count(t_bit_count); }
};

template <u32 t_bit_count>
using sbitfld = Static_Bit_Field<t_bit_count>;

template <u32 t_bit_count>
bool get_bit(sbitfld<t_bit_count> self, u32 bit_index) {
    assert(("Bit index out of range", bit_index < t_bit_count));
    return bitfld_get_bit(self->buffer, bit_index);
}

template <u32 t_bit_count>
void set_bit_high(sbitfld<t_bit_count> self, u32 bit_index) {
    assert(("Bit index out of range", bit_index < t_bit_count));
    return bitfld_set_bit_high(self->buffer, bit_index);
}

template <u32 t_bit_count>
void set_bit_low(sbitfld<t_bit_count> self, u32 bit_index) {
    assert(("Bit index out of range", bit_index < t_bit_count));
    return bitfld_set_bit_low(self->buffer, bit_index);
}

template <u32 t_bit_count>
void flip_bit(sbitfld<t_bit_count> self, u32 bit_index) {
    assert(("Bit index out of range", bit_index < t_bit_count));
    return bitfld_flip_bit(self->buffer, bit_index);
}

template <u32 t_bit_count>
void set_bit(sbitfld<t_bit_count> self, u32 bit_index, bool value) {
    assert(("Bit index out of range", bit_index < t_bit_count));
    return bitfld_set_bit(self->buffer, bit_index, value);
}


struct Dynamic_Bit_Field {
    u8* buffer;
    u32 capacity; // in bytes
    u32 bit_count;

    void init_bits(u32 init_bit_count=0) { 
        capacity = bitfld_t_byte_count(init_bit_count); 
        bit_count = init_bit_count;
        buffer = m::alloc<u8>(capacity); 
    }
    void init_bytes(u32 initial_capacity=0) { 
        capacity = initial_capacity; 
        bit_count = initial_capacity * 8u;
        buffer = m::alloc<u8>(initial_capacity); 
    }
    void shut() { free(buffer); }


    static i32 cmp_bitfld(Dynamic_Bit_Field *first, Dynamic_Bit_Field *second) {
        if (first->bit_count == second->bit_count) {
            return bitfld_cmp_bits(first->buffer, second->buffer, first->bit_count);
        } else {
            return (first->bit_count > second->bit_count ? 1 : -1);
        }
    }

    bool operator==(Dynamic_Bit_Field& other) {
        return (cmp_bitfld(this, &other) == 0);
    }

};

using dbitfld = Dynamic_Bit_Field;

bool get_bit(dbitfld self, u32 bit_index) {
    //assert(("Bit index out of range", bit_index < bit_count));
    return bitfld_get_bit(self.buffer, bit_index);
}

void set_bit_high(dbitfld self, u32 bit_index) {
    //assert(("Bit index out of range", bit_index < bit_count));
    return bitfld_set_bit_high(self.buffer, bit_index);
}

void set_bit_low(dbitfld self, u32 bit_index) {
    //assert(("Bit index out of range", bit_index < bit_count));
    return bitfld_set_bit_low(self.buffer, bit_index);
}

void flip_bit(dbitfld self, u32 bit_index) {
    //assert(("Bit index out of range", bit_index < bit_count));
    return bitfld_flip_bit(self.buffer, bit_index);
}

void set_bit(dbitfld self, u32 bit_index, bool value) {
    //assert(("Bit index out of range", bit_index < bit_count));
    return bitfld_set_bit(self.buffer, bit_index, value);
}

void dpush_bit(dbitfld *self, bool value) {
    u32 len = (self->bit_count + 1u) / 8u + (u32)((self->bit_count + 1u) % 8u > 0);
    if (len >= self->capacity) {
        dresize( &self->buffer, &self->capacity, max(1u, 2u * ((*self).capacity)) );
    }
    set_bit(*self, self->bit_count, value);
    self->bit_count++;
}

void print_bits(dbitfld self) {
    bitfld_print_bits(self.buffer, self.bit_count);
}

}
