
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

        Matrix2x2 
        T(); 

        static 
        Matrix2x2 
        id();
    };

    template <typename T>
    using mat2 = Matrix2x2<T>;
    using mat2u = mat2<u32>;
    using mat2i = mat2<i32>;
    using mat2f = mat2<f32>;
    using mat2d = mat2<f64>;

	template <typename T>
    mat2<T> operator+(mat2<T> lhs, mat2<T>& rhs) {
        return { lhs.a1 + rhs.a1, lhs.a2 + rhs.a2, 
                    lhs.b1 + rhs.b1, lhs.b2 + rhs.b2 };
    }

	template <typename T>
    mat2<T> operator-(mat2<T> lhs, mat2<T>& rhs) {
        return { lhs.a1 - rhs.a1, lhs.a2 - rhs.a2, 
                    lhs.b1 - rhs.b1, lhs.b2 - rhs.b2 };
    }

	template <typename T>
    mat2<T>& operator+=(mat2<T>& lhs, mat2<T>& rhs) {
        lhs.a1 += rhs.a1; lhs.a2 += rhs.a2;
        lhs.b1 += rhs.b1; lhs.b2 += rhs.b2;
        return lhs;
    }

	template <typename T>
    mat2<T>& operator-=(mat2<T>& lhs, mat2<T>& rhs) {
        lhs.a1 -= rhs.a1; lhs.a2 -= rhs.a2;
        lhs.b1 -= rhs.b1; lhs.b2 -= rhs.b2;
        return lhs;
    }

	template <typename T>
    vec2<T> operator*(mat2<T> lhs, vec2<T> rhs) {
        return {lhs.a1 * rhs.x + lhs.a2 * rhs.y, lhs.b1 * rhs.x + lhs.b2 * rhs.y};
    }

	template <typename T>
    bool operator==(mat2<T> lhs, mat2<T>& rhs) {
        return (lhs.a1 == rhs.a1 && lhs.a2 == rhs.a2 && 
                lhs.b1 == rhs.b1 && lhs.b2 == rhs.b2);
    }
    
	template <typename T>
    bool operator!=(mat2<T> lhs, mat2<T>& rhs) {
        return (lhs.a1 != rhs.a1 || lhs.a2 != rhs.a2 || 
                lhs.b1 != rhs.b1 || lhs.b2 != rhs.b2);
    }

	template <typename T>
    mat2<T> 
    Matrix2x2<T>::T() {
        return { a1, b1, 
                    a2, b2 };
    }

	template <typename T>
    mat2<T> 
    Matrix2x2<T>::id() {
        return { 1, 0,
                 0, 1 };
    }

    template <typename S>
    mat2<S>
    operator*(mat2<S> lhs, mat2<S> rhs)
    {
        return {
            lhs.a1 * rhs.a1 + lhs.a2 * rhs.b1, lhs.a1 * rhs.a2 + lhs.a2 * rhs.b2,
            lhs.b1 * rhs.a1 + lhs.b2 * rhs.b1, lhs.b1 * rhs.a2 + lhs.b2 * rhs.b2,
        };
    }



    template <typename S>
    union Matrix3x3 {
        struct {
            S a1, a2, a3;
            S b1, b2, b3;
            S c1, c2, c3;
        };
        sbuff<S, 9> buffer;

        Matrix3x3 
        T();

        static 
        Matrix3x3 
        id();
    };

    template <typename T>
    using mat3 = Matrix3x3<T>;
    using mat3u = mat3<u32>;
    using mat3i = mat3<i32>;
    using mat3f = mat3<f32>;
    using mat3d = mat3<f64>;


	template <typename T>
    mat3<T> operator+(mat3<T> lhs, mat3<T>& rhs) {
        return { lhs.a1 + rhs.a1, lhs.a2 + rhs.a2, lhs.a3 + rhs.a3,
                 lhs.b1 + rhs.b1, lhs.b2 + rhs.b2, lhs.b3 + rhs.b3, 
                 lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3 };
    }

	template <typename T>
    mat3<T> operator-(mat3<T> lhs, mat3<T>& rhs) {
        return { lhs.a1 - rhs.a1, lhs.a2 - rhs.a2, lhs.a3 - rhs.a3,
                 lhs.b1 - rhs.b1, lhs.b2 - rhs.b2, lhs.b3 - rhs.b3, 
                 lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3 };
    }

	template <typename T>
    mat3<T>& operator+=(mat3<T>& lhs, mat3<T>& rhs) {
        lhs.a1 += rhs.a1; lhs.a2 += rhs.a2; lhs.a3 += rhs.a3;
        lhs.b1 += rhs.b1; lhs.b2 += rhs.b2; lhs.b3 += rhs.b3; 
        lhs.c1 += rhs.c1; lhs.c2 += rhs.c2; lhs.c3 += rhs.c3;
        return lhs;
    }

	template <typename T>
    mat3<T>& operator-=(mat3<T>& lhs, mat3<T>& rhs) {
        lhs.a1 -= rhs.a1; lhs.a2 -= rhs.a2; lhs.a3 -= rhs.a3;
        lhs.b1 -= rhs.b1; lhs.b2 -= rhs.b2; lhs.b3 -= rhs.b3; 
        lhs.c1 -= rhs.c1; lhs.c2 -= rhs.c2; lhs.c3 -= rhs.c3;
        return lhs;
    }

	template <typename T>
    bool operator==(mat3<T> lhs, mat3<T>& rhs) {
        return ( lhs.a1 == rhs.a1 && lhs.a2 == rhs.a2 && lhs.a3 == rhs.a3 &&
                 lhs.b1 == rhs.b1 && lhs.b2 == rhs.b2 && lhs.b3 == rhs.b3 && 
                 lhs.c1 == rhs.c1 && lhs.c2 == rhs.c2 && lhs.c3 == rhs.c3 );
    }
    
	template <typename T>
    bool operator!=(mat3<T> lhs, mat3<T>& rhs) {
        return ( lhs.a1 != rhs.a1 || lhs.a2 != rhs.a2 || lhs.a3 != rhs.a3 ||
                 lhs.b1 != rhs.b1 || lhs.b2 != rhs.b2 || lhs.b3 != rhs.b3 || 
                 lhs.c1 != rhs.c1 || lhs.c2 != rhs.c2 || lhs.c3 != rhs.c3 );
    }

	template <typename T>
    mat3<T> Matrix3x3<T>::
    T() {
        return { a1, b1, c1, 
                 a2, b2, c2,
                 a3, b3, c3 };
    }

	template <typename T>
    mat3<T> Matrix3x3<T>::
    id() {
        return { 1, 0, 0, 
                 0, 1, 0,
                 0, 0, 1 };
    }





    template <typename S>
    union Matrix4x4 {
        struct {
            S a1, a2, a3, a4;
            S b1, b2, b3, b4;
            S c1, c2, c3, c4;
            S d1, d2, d3, d4;
        };
        sbuff<sbuff<S, 4>, 4> buffer;

        Matrix4x4
        T();

        static
        Matrix4x4
        id();

    };

    template <typename T>
    using mat4 = Matrix4x4<T>;
    using mat4u = mat4<u32>;
    using mat4i = mat4<i32>;
    using mat4f = mat4<f32>;
    using mat4d = mat4<f64>;


	template <typename T>
    mat4<T> operator+(mat4<T> lhs, mat4<T> rhs) {
        return { lhs.a1 + rhs.a1, lhs.a2 + rhs.a2, lhs.a3 + rhs.a3, lhs.a4 + rhs.a4,
                 lhs.b1 + rhs.b1, lhs.b2 + rhs.b2, lhs.b3 + rhs.b3, lhs.b4 + rhs.b4, 
                 lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3, lhs.c4 + rhs.c4,
                 lhs.d1 + rhs.d1, lhs.d2 + rhs.d2, lhs.d3 + rhs.d3, lhs.d4 + rhs.d4 };
    }

	template <typename T>
    mat4<T> operator-(mat4<T> lhs, mat4<T> rhs) {
        return { lhs.a1 - rhs.a1, lhs.a2 - rhs.a2, lhs.a3 - rhs.a3, lhs.a4 - rhs.a4,
                 lhs.b1 - rhs.b1, lhs.b2 - rhs.b2, lhs.b3 - rhs.b3, lhs.b4 - rhs.b4, 
                 lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3, lhs.c4 - rhs.c4,
                 lhs.d1 - rhs.d1, lhs.d2 - rhs.d2, lhs.d3 - rhs.d3, lhs.d4 - rhs.d4 };
    }

	template <typename T>
    mat4<T>& operator+=(mat4<T>& lhs, mat4<T> rhs) {
        lhs.a1 += rhs.a1; lhs.a2 += rhs.a2; lhs.a3 += rhs.a3; lhs.a4 += rhs.a4;
        lhs.b1 += rhs.b1; lhs.b2 += rhs.b2; lhs.b3 += rhs.b3; lhs.b4 += rhs.b4;
        lhs.c1 += rhs.c1; lhs.c2 += rhs.c2; lhs.c3 += rhs.c3; lhs.c4 += rhs.c4;
        lhs.d1 += rhs.d1; lhs.d2 += rhs.d2; lhs.d3 += rhs.d3; lhs.d4 += rhs.d4;
        return lhs;
    }

	template <typename T>
    mat4<T>& operator-=(mat4<T>& lhs, mat4<T> rhs) {
        lhs.a1 -= rhs.a1; lhs.a2 -= rhs.a2; lhs.a3 -= rhs.a3; lhs.a4 -= rhs.a4;
        lhs.b1 -= rhs.b1; lhs.b2 -= rhs.b2; lhs.b3 -= rhs.b3; lhs.b4 -= rhs.b4;
        lhs.c1 -= rhs.c1; lhs.c2 -= rhs.c2; lhs.c3 -= rhs.c3; lhs.c4 -= rhs.c4;
        lhs.d1 -= rhs.d1; lhs.d2 -= rhs.d2; lhs.d3 -= rhs.d3; lhs.d4 -= rhs.d4;
        return lhs;
    }

	template <typename T>
    mat4<T> operator*(mat4<T> lhs, mat4<T> rhs) {
        mat4<T> ret;
        for (u32 i = 0; i < 4; i++) {
            for (u32 j = 0; j < 4; j++) {
                ret.buffer[i][j] = lhs.buffer[i][0] * rhs.buffer[0][j] + lhs.buffer[i][1] * rhs.buffer[1][j] +
                    lhs.buffer[i][2] * rhs.buffer[2][j] + lhs.buffer[i][3] * rhs.buffer[3][j]; 
            }
        }
        return ret;
    }


	template <typename S>
    vec4<S> operator*(mat4<S> lhs, vec4<S> rhs) {
        vec4<S> ret;
        for (u32 i = 0; i < 4; i++) {
            for (u32 j = 0; j < 4; j++) {
                ret.buffer[i] = lhs.buffer[i][0] * rhs.buffer[0] + lhs.buffer[i][1] * rhs.buffer[1] +
                    lhs.buffer[i][2] * rhs.buffer[2] + lhs.buffer[i][3] * rhs.buffer[3]; 
            }
        }
        return ret;
    }

	template <typename T>
    bool operator==(mat4<T> lhs, mat4<T> rhs) {
        return { lhs.a1 == rhs.a1 && lhs.a2 == rhs.a2 && lhs.a3 == rhs.a3 && lhs.a4 == rhs.a4 &&
                 lhs.b1 == rhs.b1 && lhs.b2 == rhs.b2 && lhs.b3 == rhs.b3 && lhs.b4 == rhs.b4 && 
                 lhs.c1 == rhs.c1 && lhs.c2 == rhs.c2 && lhs.c3 == rhs.c3 && lhs.c4 == rhs.c4 &&
                 lhs.d1 == rhs.d1 && lhs.d2 == rhs.d2 && lhs.d3 == rhs.d3 && lhs.d4 == rhs.d4 };
    }
    
	template <typename T>
    bool operator!=(mat4<T> lhs, mat4<T> rhs) {
        return { lhs.a1 != rhs.a1 || lhs.a2 != rhs.a2 || lhs.a3 != rhs.a3 || lhs.a4 != rhs.a4 ||
                 lhs.b1 != rhs.b1 || lhs.b2 != rhs.b2 || lhs.b3 != rhs.b3 || lhs.b4 != rhs.b4 || 
                 lhs.c1 != rhs.c1 || lhs.c2 != rhs.c2 || lhs.c3 != rhs.c3 || lhs.c4 != rhs.c4 ||
                 lhs.d1 != rhs.d1 || lhs.d2 != rhs.d2 || lhs.d3 != rhs.d3 || lhs.d4 != rhs.d4 };
    }

	template <typename T>
    mat4<T> Matrix4x4<T>::
    T() {
        return { a1, b1, c1, d1,
                 a2, b2, c2, d2,
                 a3, b3, c3, d3,
                 a4, b4, c4, d4, };
    }

	template <typename T>
    mat4<T> Matrix4x4<T>::
    id() {
        return { 1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1, };
    }

}

