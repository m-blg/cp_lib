
#pragma once

#include "mbgldef.h"
#include "buffer.cc"
#include "vector.cc"
#include <math.h>

namespace cp {
    template <typename S>
    union Matrix2x2 {
        struct {
            S a1, a2;
            S b1, b2;
        };
        sbuff<S, 4> buffer;

        Matrix2x2 operator+(Matrix2x2& other) {
            return { a1 + other.a1, a2 + other.a2, 
                     b1 + other.b1, b2 + other.b2 };
        }

        Matrix2x2 operator-(Matrix2x2& other) {
            return { a1 - other.a1, a2 - other.a2, 
                     b1 - other.b1, b2 - other.b2 };
        }

        Matrix2x2& operator+=(Matrix2x2& other) {
            a1 += other.a1; a2 += other.a2;
            b1 += other.b1; b2 += other.b2;
            return *this;
        }
 
        Matrix2x2& operator-=(Matrix2x2& other) {
            a1 -= other.a1; a2 -= other.a2;
            b1 -= other.b1; b2 -= other.b2;
            return *this;
        }

        vec2<S> operator*(vec2<S> other) {
            return {a1 * other.x + a2 * other.y, b1 * other.x + b2 * other.y};
        }

        bool operator==(Matrix2x2& other) {
            return (a1 == other.a1 && a2 == other.a2 && 
                    b1 == other.b1 && b2 == other.b2);
        }
        
        bool operator!=(Matrix2x2& other) {
            return (a1 != other.a1 || a2 != other.a2 || 
                    b1 != other.b1 || b2 != other.b2);
        }

        Matrix2x2 T() {
            return { a1, b1, 
                     a2, b2 };
        }
    };

    template <typename T>
    using mat2 = Matrix2x2<T>;
    using mat2u = mat2<u32>;
    using mat2i = mat2<i32>;
    using mat2f = mat2<f32>;
    using mat2d = mat2<f64>;

    template <typename S>
    union Matrix3x3 {
        struct {
            S a1, a2, a3;
            S b1, b2, b3;
            S c1, c2, c3;
        };
        sbuff<S, 9> buffer;

        Matrix3x3 operator+(Matrix3x3& other) {
            return { a1 + other.a1, a2 + other.a2, a3 + other.a3,
                     b1 + other.b1, b2 + other.b2, b3 + other.b3, 
                     c1 + other.c1, c2 + other.c2, c3 + other.c3 };
        }

        Matrix3x3 operator-(Matrix3x3& other) {
            return { a1 - other.a1, a2 - other.a2, a3 - other.a3,
                     b1 - other.b1, b2 - other.b2, b3 - other.b3, 
                     c1 - other.c1, c2 - other.c2, c3 - other.c3 };
        }

        Matrix3x3& operator+=(Matrix3x3& other) {
            a1 += other.a1; a2 += other.a2; a3 += other.a3;
            b1 += other.b1; b2 += other.b2; b3 += other.b3; 
            c1 += other.c1; c2 += other.c2; c3 += other.c3;
            return *this;
        }
 
        Matrix3x3& operator-=(Matrix3x3& other) {
            a1 -= other.a1; a2 -= other.a2; a3 -= other.a3;
            b1 -= other.b1; b2 -= other.b2; b3 -= other.b3; 
            c1 -= other.c1; c2 -= other.c2; c3 -= other.c3;
            return *this;
        }

        bool operator==(Matrix3x3& other) {
            return ( a1 == other.a1 && a2 == other.a2 && a3 == other.a3 &&
                     b1 == other.b1 && b2 == other.b2 && b3 == other.b3 && 
                     c1 == other.c1 && c2 == other.c2 && c3 == other.c3 );

        }
        
        bool operator!=(Matrix3x3& other) {
            return ( a1 != other.a1 || a2 != other.a2 || a3 != other.a3 ||
                     b1 != other.b1 || b2 != other.b2 || b3 != other.b3 || 
                     c1 != other.c1 || c2 != other.c2 || c3 != other.c3 );
        }

        Matrix3x3 T() {
            return { a1, b1, c1, 
                     a2, b2, c2,
                     a3, b3, c3 };
        }
    };

    template <typename T>
    using mat3 = Matrix3x3<T>;
    using mat3u = mat3<u32>;
    using mat3i = mat3<i32>;
    using mat3f = mat3<f32>;
    using mat3d = mat3<f64>;


    template <typename S>
    union Matrix4x4 {
        struct {
            S a1, a2, a3, a4;
            S b1, b2, b3, b4;
            S c1, c2, c3, c4;
            S d1, d2, d3, d4;
        };
        sbuff<sbuff<S, 4>, 4> buffer;

        Matrix4x4 operator+(Matrix4x4 other) {
            return { a1 + other.a1, a2 + other.a2, a3 + other.a3, a4 + other.a4,
                     b1 + other.b1, b2 + other.b2, b3 + other.b3, b4 + other.b4, 
                     c1 + other.c1, c2 + other.c2, c3 + other.c3, c4 + other.c4,
                     d1 + other.d1, d2 + other.d2, d3 + other.d3, d4 + other.d4 };
        }

        Matrix4x4 operator-(Matrix4x4 other) {
            return { a1 - other.a1, a2 - other.a2, a3 - other.a3, a4 - other.a4,
                     b1 - other.b1, b2 - other.b2, b3 - other.b3, b4 - other.b4, 
                     c1 - other.c1, c2 - other.c2, c3 - other.c3, c4 - other.c4,
                     d1 - other.d1, d2 - other.d2, d3 - other.d3, d4 - other.d4 };
        }

        Matrix4x4& operator+=(Matrix4x4 other) {
            a1 += other.a1; a2 += other.a2; a3 += other.a3; a4 += other.a4;
            b1 += other.b1; b2 += other.b2; b3 += other.b3; b4 += other.b4;
            c1 += other.c1; c2 += other.c2; c3 += other.c3; c4 += other.c4;
            d1 += other.d1; d2 += other.d2; d3 += other.d3; d4 += other.d4;
            return *this;
        }
 
        Matrix4x4& operator-=(Matrix4x4 other) {
            a1 -= other.a1; a2 -= other.a2; a3 -= other.a3; a4 -= other.a4;
            b1 -= other.b1; b2 -= other.b2; b3 -= other.b3; b4 -= other.b4;
            c1 -= other.c1; c2 -= other.c2; c3 -= other.c3; c4 -= other.c4;
            d1 -= other.d1; d2 -= other.d2; d3 -= other.d3; d4 -= other.d4;
            return *this;
        }

        Matrix4x4 operator*(Matrix4x4 other) {
            Matrix4x4 ret;
            for (u32 i = 0; i < 4; i++) {
                for (u32 j = 0; j < 4; j++) {
                    ret.buffer[i][j] = buffer[i][0] * other.buffer[0][j] + buffer[i][1] * other.buffer[1][j] +
                        buffer[i][2] * other.buffer[2][j] + buffer[i][3] * other.buffer[3][j]; 
                }
            }
            return ret;
        }


        vec4<S> operator*(vec4<S> other) {
            vec4<S> ret;
            for (u32 i = 0; i < 4; i++) {
                for (u32 j = 0; j < 4; j++) {
                    ret.buffer[i] = buffer[i][0] * other.buffer[0] + buffer[i][1] * other.buffer[1] +
                        buffer[i][2] * other.buffer[2] + buffer[i][3] * other.buffer[3]; 
                }
            }
            return ret;
        }

        bool operator==(Matrix4x4 other) {
            return { a1 == other.a1 && a2 == other.a2 && a3 == other.a3 && a4 == other.a4 &&
                     b1 == other.b1 && b2 == other.b2 && b3 == other.b3 && b4 == other.b4 && 
                     c1 == other.c1 && c2 == other.c2 && c3 == other.c3 && c4 == other.c4 &&
                     d1 == other.d1 && d2 == other.d2 && d3 == other.d3 && d4 == other.d4 };

        }
        
        bool operator!=(Matrix4x4 other) {
            return { a1 != other.a1 || a2 != other.a2 || a3 != other.a3 || a4 != other.a4 ||
                     b1 != other.b1 || b2 != other.b2 || b3 != other.b3 || b4 != other.b4 || 
                     c1 != other.c1 || c2 != other.c2 || c3 != other.c3 || c4 != other.c4 ||
                     d1 != other.d1 || d2 != other.d2 || d3 != other.d3 || d4 != other.d4 };
        }

        Matrix4x4 T() {
            return { a1, b1, c1, d1,
                     a2, b2, c2, d2,
                     a3, b3, c3, d3,
                     a4, b4, c4, d4 };
        }
    };

    template <typename T>
    using mat4 = Matrix4x4<T>;
    using mat4u = mat4<u32>;
    using mat4i = mat4<i32>;
    using mat4f = mat4<f32>;
    using mat4d = mat4<f64>;
}
