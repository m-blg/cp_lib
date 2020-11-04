#pragma once

#include "mbgldef.h"
#include "basic.cc"
#include "array.cc"
#include "memory.cc"
#include <cassert>

namespace cp {

    namespace bitfield {

        constexpr u32 t_byte_count(u32 t_bit_count) {
            u32 div = t_bit_count / 8u;
            u32 mod = t_bit_count % 8u;
            return (mod ? div + 1 : div);
        }

        inline bool get_bit(u8* buffer, u32 bit_index) {
            return buffer[bit_index / 8u] & (1u << (7u - bit_index % 8u));
        }

        inline void set_bit_high(u8* buffer, u32 bit_index) {
            buffer[bit_index / 8u] |= (1u << (7u - bit_index % 8u)); 
        }

        inline void set_bit_low(u8* buffer, u32 bit_index) {
            buffer[bit_index / 8u] &= ~(1u << (7u - bit_index % 8u)); 
        }

        inline void flip_bit(u8* buffer, u32 bit_index) {
            buffer[bit_index / 8u] ^= (1u << (7u - bit_index % 8u)); 
        }

        inline void set_bit(u8* buffer, u32 bit_index, bool value) {
            if (get_bit(buffer, bit_index) != value) {
                flip_bit(buffer, bit_index);
            }
        }

        inline int cmp_bits(u8* first, u8* second, u32 bit_count) {
            for (u32 i = 0; i < bit_count; i++) {
                if (get_bit(first, i) != get_bit(second, i)) {
                    return (get_bit(first, i) ? 1 : -1);
                }
            }
            return 0;
        }

        inline void print_bits(u8* buffer, u32 bit_count) {
            for (i32 i = 0; i < bit_count; i++) {
                printf("%d", get_bit(buffer, i));
            }
        }
    }

    template <u32 t_bit_count>
    struct StaticBitField {
        u8 buffer[bitfield::t_byte_count(t_bit_count)];

        constexpr u32 bit_count() { return t_bit_count; }
        // in bytes
        constexpr u32 capacity() { return bitfield::t_byte_count(t_bit_count); }

        static inline bool get_bit(StaticBitField *self, u32 bit_index) {
            assert(("Bit index out of range", bit_index < t_bit_count));
            return bitfield::get_bit(self->buffer, bit_index);
        }

        static inline void set_bit_high(StaticBitField *self, u32 bit_index) {
            assert(("Bit index out of range", bit_index < t_bit_count));
            return bitfield::set_bit_high(self->buffer, bit_index);
        }

        static inline void set_bit_low(StaticBitField *self, u32 bit_index) {
            assert(("Bit index out of range", bit_index < t_bit_count));
            return bitfield::set_bit_low(self->buffer, bit_index);
        }

        static inline void flip_bit(StaticBitField *self, u32 bit_index) {
            assert(("Bit index out of range", bit_index < t_bit_count));
            return bitfield::flip_bit(self->buffer, bit_index);
        }

        static inline void set_bit(StaticBitField *self, u32 bit_index, bool value) {
            assert(("Bit index out of range", bit_index < t_bit_count));
            return bitfield::set_bit(self->buffer, bit_index, value);
        }

    };
    
    template <u32 t_bit_count>
    using sbitfld = StaticBitField<t_bit_count>;


    struct DynamicBitField {
        u8* buffer;
        u32 capacity; // in bytes
        u32 bit_count;

        void init_bits(u32 init_bit_count=0) { 
            capacity = bitfield::t_byte_count(init_bit_count); 
            bit_count = init_bit_count;
            buffer = m::alloc<u8>(capacity); 
        }
        void init_bytes(u32 initial_capacity=0) { 
            capacity = initial_capacity; 
            bit_count = initial_capacity * 8u;
            buffer = m::alloc<u8>(initial_capacity); 
        }
        void shut() { free(buffer); }

        static inline bool get_bit(DynamicBitField *self, u32 bit_index) {
            //assert(("Bit index out of range", bit_index < bit_count));
            return bitfield::get_bit(self->buffer, bit_index);
        }

        static inline void set_bit_high(DynamicBitField *self, u32 bit_index) {
            //assert(("Bit index out of range", bit_index < bit_count));
            return bitfield::set_bit_high(self->buffer, bit_index);
        }

        static inline void set_bit_low(DynamicBitField *self, u32 bit_index) {
            //assert(("Bit index out of range", bit_index < bit_count));
            return bitfield::set_bit_low(self->buffer, bit_index);
        }

        static inline void flip_bit(DynamicBitField *self, u32 bit_index) {
            //assert(("Bit index out of range", bit_index < bit_count));
            return bitfield::flip_bit(self->buffer, bit_index);
        }

        static inline void set_bit(DynamicBitField *self, u32 bit_index, bool value) {
            //assert(("Bit index out of range", bit_index < bit_count));
            return bitfield::set_bit(self->buffer, bit_index, value);
        }

        static void dpush_bit(DynamicBitField *self, bool value) {
            u32 len = (self->bit_count + 1u) / 8u + (u32)((self->bit_count + 1u) % 8u > 0);
            if (len >= self->capacity) {
                buffer::dresize( &self->buffer, &self->capacity, max(1u, 2u * ((*self).capacity)) );
            }
            DynamicBitField::set_bit(self, self->bit_count, value);
            self->bit_count++;
        }

        static i32 cmp_bitfld(DynamicBitField *first, DynamicBitField *second) {
            if (first->bit_count == second->bit_count) {
                return bitfield::cmp_bits(first->buffer, second->buffer, first->bit_count);
            } else {
                return (first->bit_count > second->bit_count ? 1 : -1);
            }
        }

        static void print_bits(DynamicBitField *self) {
            bitfield::print_bits(self->buffer, self->bit_count);
        }

        bool operator==(DynamicBitField& other) {
            return (cmp_bitfld(this, &other) == 0);
        }

    };

    using dbitfld = DynamicBitField;
}
