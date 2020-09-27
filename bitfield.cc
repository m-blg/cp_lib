
#include "mbgldef.h"
#include "memory.cc"
#include "cassert"

namespace cp {

    constexpr u32 t_byte_count(u32 t_bit_count) {
        u32 div = t_bit_count / 8u;
        u32 mod = t_bit_count % 8u;
        return (mod ? div + 1 : div);
    }

    namespace bitfield {

        inline bool get_bit(u8* buffer, u32 bit_index) {
            return buffer[bit_index / 8u] & (1u << (bit_index % 8u));
        }

        inline void set_bit_high(u8* buffer, u32 bit_index) {
            buffer[bit_index / 8u] |= (1u << (bit_index % 8u)); 
        }

        inline void set_bit_low(u8* buffer, u32 bit_index) {
            buffer[bit_index / 8u] &= ~(1u << (bit_index % 8u)); 
        }

        inline void flip_bit(u8* buffer, u32 bit_index) {
            buffer[bit_index / 8u] ^= (1u << (bit_index % 8u)); 
        }

        inline void set_bit(u8* buffer, u32 bit_index, bool value) {
            if (get_bit(buffer, bit_index) != value) {
                flip_bit(buffer, bit_index);
            }
        }
    }

    template <u32 t_bit_count>
    struct StaticBitField {
        u8 buffer[t_byte_count(t_bit_count)];

        u32 bit_count() { return t_bit_count; }
        // in bytes
        u32 capacity() { return t_byte_count(t_bit_count); }

        inline bool get_bit(u32 bit_index) {
            assert(("Bit index out of range", bit_index < t_bit_count));
            return bitfield::get_bit(buffer, bit_index);
        }

        inline void set_bit_high(u32 bit_index) {
            assert(("Bit index out of range", bit_index < t_bit_count));
            return bitfield::set_bit_high(buffer, bit_index);
        }

        inline void set_bit_low(u32 bit_index) {
            assert(("Bit index out of range", bit_index < t_bit_count));
            return bitfield::set_bit_low(buffer, bit_index);
        }

        inline void flip_bit(u32 bit_index) {
            assert(("Bit index out of range", bit_index < t_bit_count));
            return bitfield::flip_bit(buffer, bit_index);
        }

        inline void set_bit(u32 bit_index, bool value) {
            assert(("Bit index out of range", bit_index < t_bit_count));
            return bitfield::set_bit(buffer, bit_index, value);
        }

    };

    struct DynamicBitField {
        u8* buffer;
        u32 capacity; // in bytes
        u32 bit_count;

        void init(u32 initial_capacity=0) { 
            capacity = initial_capacity; 
            buffer = alloc<u8>(initial_capacity); 
        }
        void shut() { free(buffer); }

        inline bool get_bit(u32 bit_index) {
            assert(("Bit index out of range", bit_index < bit_count));
            return bitfield::get_bit(buffer, bit_index);
        }

        inline void set_bit_high(u32 bit_index) {
            assert(("Bit index out of range", bit_index < bit_count));
            return bitfield::set_bit_high(buffer, bit_index);
        }

        inline void set_bit_low(u32 bit_index) {
            assert(("Bit index out of range", bit_index < bit_count));
            return bitfield::set_bit_low(buffer, bit_index);
        }

        inline void flip_bit(u32 bit_index) {
            assert(("Bit index out of range", bit_index < bit_count));
            return bitfield::flip_bit(buffer, bit_index);
        }

        inline void set_bit(u32 bit_index, bool value) {
            assert(("Bit index out of range", bit_index < bit_count));
            return bitfield::set_bit(buffer, bit_index, value);
        }

    };

}
