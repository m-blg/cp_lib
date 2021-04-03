#pragma once

#include "mbgldef.h"
#include "buffer.cc"
#include <math.h>

namespace cp {

template<typename T>
union Vector2 {
    struct {T x, y;};
    struct {T u, v;};
    sbuff<T, 2> buffer;
    
    Vector2() = default;
    Vector2(T _x, T _y) { x = _x; y = _y; }

    Vector2 operator-();

    template <typename S>
    operator Vector2<S>();

    T& operator[](u32 index);

    static Vector2<T> zero();
    static Vector2<T> one();
};


template <typename T>
Vector2<T> Vector2<T>::operator-() {
    return { -x, -y };
}

template <typename T>
template <typename S>
Vector2<T>::operator Vector2<S>() {
    return {(S)x, (S)y};
}

template <typename T>
T& Vector2<T>::operator[](u32 index) {
    return buffer[index];
}

template <typename T>
Vector2<T> Vector2<T>::zero() {
    return { 0, 0 };
}

template <typename T>
Vector2<T> Vector2<T>::one() {
    return { 1, 1 };
}

template <typename T>
using vec2 = Vector2<T>;

using vec2f = Vector2<f32>;
using vec2i = Vector2<i32>;
using vec2u = Vector2<u32>;    
using vec2d = Vector2<f64>;


template<typename T>
vec2<T> operator+(vec2<T> first, vec2<T> second) {
    return { first.x + second.x, first.y + second.y };
}
template<typename T>
vec2<T> operator-(vec2<T> first, vec2<T> second) {
    return { first.x - second.x, first.y - second.y };
}

template<typename T>
vec2<T> operator*(vec2<T> first, T second) {
    return { first.x * second, first.y * second };
}
template<typename T>
vec2<T> operator*(T first, vec2<T> second) {
    return { second.x * first, second.y * first };
}
template<typename T>
vec2<T> operator/(vec2<T> first, T second) {
    return { first.x / second, first.y / second };
}
template<typename T>
vec2<T> operator/(T first, vec2<T> second) {
    return { second.x / first, second.y / first };
}

template<typename T>
vec2<T>& operator+=(vec2<T>& first, vec2<T> second) {
    first.x += second.x;
    first.y += second.y;
    return first;
}
template<typename T>
vec2<T>& operator-=(vec2<T>& first, vec2<T> second) {
    first.x -= second.x;
    first.y -= second.y;
    return first;
}
template<typename T>
vec2<T>& operator*=(vec2<T>& first, T second) {
    first.x *= second;
    first.y *= second;
    return first;
}
template<typename T>
vec2<T>& operator/=(vec2<T>& first, T second) {
    first.x /= second;
    first.y /= second;
    return first;
}
template<typename T>
bool operator==(vec2<T> first, vec2<T> second) {
    return first.x == second.x && first.y == second.y;
}
template<typename T>
bool operator!=(vec2<T> first, vec2<T> second) {
    return first.x != second.x || first.y != second.y;
}

template<typename T>
T magnitude(vec2<T> self) {
    return sqrt(self.x * self.x + self.y * self.y);
}

template<typename T>
vec2<T> normalized(vec2<T> self) {
    T magnitude = self->magnitude();
    return { self->x / magnitude, self->y / magnitude };
}

template<typename T>
T dot(vec2<T> first, vec2<T> second) {
    return first.x * second.x + first.y * second.y;
}

template<typename T>
T cross(vec2<T> first, vec2<T> second) {
    return first.x * second.y - first.y * second.x;
}

//template<typename T>
//void print(vec2<T> v) {
    //printf()
//}


template<typename T>
union Vector3 {
    struct {T x, y, z;};
    struct {T r, g, b;};
    struct {T u, v;};
    sbuff<T, 3> buffer;
    
    
    Vector3() = default;
    Vector3(T _x, T _y, T _z) { x = _x; y = _y; z = _z; }
    Vector3(Vector2<T> _xy, T _z) { x = _xy.x; y = _xy.y; z = _z; }
    Vector3(T _x, Vector2<T> _yz) { x = _x; y = _yz.y; z = _yz.z; }

    template <typename S>
    operator Vector3<S>();
    template <typename S>
    operator Vector2<S>();

    T& operator[](u32 index);

    static Vector3 zero();
    static Vector3 one();
};

template<typename T>
template <typename S>
Vector3<T>::operator Vector3<S>() {
    return {(S)x, (S)y, (S)z};
}

template<typename T>
template <typename S>
Vector3<T>::operator Vector2<S>() {
    return {(S)x, (S)y};
}

template<typename T>
T& Vector3<T>::operator[](u32 index) {
    return buffer[index];
}


template<typename T>
Vector3<T> Vector3<T>::zero() {
    return { 0, 0, 0 };
}

template<typename T>
Vector3<T> Vector3<T>::one() {
    return { 1, 1, 1 };
}


template <typename T>
using vec3 = Vector3<T>;

using vec3f = Vector3<f32>;
using vec3i = Vector3<i32>;
using vec3u = Vector3<u32>;    
using vec3d = Vector3<f64>;


template <typename T>
vec3<T> operator+(vec3<T> first, vec3<T> second) {
    return { first.x + second.x, first.y + second.y, first.z + second.z };
}
template <typename T>
vec3<T> operator-(vec3<T> first, vec3<T> second) {
    return { first.x - second.x, first.y - second.y, first.z - second.z };
}

template <typename T>
vec3<T> operator*(vec3<T> first, T second) {
    return { first.x * second, first.y * second, first.z * second };
}
template <typename T>
vec3<T> operator*(T first, vec3<T> second) {
    return { second.x * first, second.y * first, second.z * first };
}
template <typename T>
vec3<T> operator/(vec3<T> first, T second) {
    return { first.x / second, first.y / second, first.z / second };
}
template <typename T>
vec3<T> operator/(T first, vec3<T> second) {
    return { second.x / first, second.y / first, second.z / first };
}

template <typename T>
vec3<T>& operator+=(vec3<T>& first, vec3<T> second) {
    first.x += second.x;
    first.y += second.y;
    first.z += second.z;
    return first;
}
template <typename T>
vec3<T>& operator-=(vec3<T>& first, vec3<T> second) {
    first.x -= second.x;
    first.y -= second.y;
    first.z -= second.z;
    return first;
}
template <typename T>
vec3<T>& operator*=(vec3<T>& first, T second) {
    first.x *= second;
    first.y *= second;
    first.z *= second;
    return first;
}
template <typename T>
vec3<T>& operator/=(vec3<T>& first, T second) {
    first.x /= second;
    first.y /= second;
    first.z /= second;
    return first;
}
template <typename T>
bool operator==(vec3<T> first, vec3<T> second) {
    return first.x == second.x && first.y == second.y && first.z == second.z;
}
template <typename T>
bool operator!=(vec3<T> first, vec3<T> second) {
    return first.x != second.x || first.y != second.y || first.z != second.z;
}

template <typename T>
T magnitude(Vector3<T> self) {
    return sqrt(self.x * self.x + self.y * self.y + self.z * self.z);
}

template <typename T>
Vector3<T> normalized(Vector3<T> self) {
    T mag = magnitude(self);
    return { self.x / mag, self.y / mag, self.z / mag };
}

template <typename T>
T dot(Vector3<T> first, Vector3<T> second) {
    return first.x * second.x + first.y * second.y + first.z * second.z;
}

template <typename T>
Vector3<T> cross(Vector3<T> first, Vector3<T> second) {
    return { first.y * second.z - second.y * first.z, second.x * first.z - first.x * second.z, first.x * second.y - second.x * first.y };
}


template<typename T>
union Vector4 {
    struct {T x, y, z, w;};
    struct {T r, g, b, a;};
    struct {T u, v;};
    sbuff<T, 4> buffer;
    
    
    Vector4() = default;
    Vector4(T _x, T _y, T _z, T _w) { x = _x; y = _y; z = _z; w = _w; }
    Vector4(Vector2<T> _xy, T _z, T _w) { x = _xy.x; y = _xy.y; z = _z; w = _w; }
    Vector4(T _x, Vector2<T> _yz, T _w) { x = _x; y = _yz.y; z = _yz.z; w = _w; }
    Vector4(T _x, T _y, Vector2<T> _zw) { x = _x; y = _y; z = _zw.z; w = _zw.w; }
    Vector4(Vector2<T> _xy, Vector2<T> _zw) { x = _xy.x; y = _xy.y; z = _zw.z; w = _zw.w; }
    Vector4(Vector3<T> _xyz, T _w) { x = _xyz.x; y = _xyz.y; z = _xyz.z; w = _w; }
    Vector4(T _x, Vector3<T> _yzw) { x = _x; y = _yzw.y; z = _yzw.z; w = _yzw.w; }

    template <typename S>
    operator Vector4<S>();
    template <typename S>
    operator Vector3<S>();
    template <typename S>
    operator Vector2<S>();    

    T& operator[](u32 index);

    static Vector4<T> zero();
    static Vector4<T> one();
};

template<typename T>
template <typename S>
Vector4<T>::operator Vector4<S>() {
    return { (S)x, (S)y, (S)z, (S) w };
}

template<typename T>
template <typename S>
Vector4<T>::operator Vector3<S>() {
    return {(S)x, (S)y, (S)z};
}

template<typename T>
template <typename S>
Vector4<T>::operator Vector2<S>() {
    return {(S)x, (S)y};
}

template<typename T>
T& Vector4<T>::operator[](u32 index) {
    return buffer[index];
}

template<typename T>
Vector4<T> Vector4<T>::zero() {
    return { 0, 0, 0, 0 };
}

template<typename T>
Vector4<T> Vector4<T>::one() {
    return { 1, 1, 1, 1 };
}


template <typename T>
using vec4 = Vector4<T>;

using vec4f = Vector4<f32>;
using vec4i = Vector4<i32>;
using vec4u = Vector4<u32>;    
using vec4d = Vector4<f64>;


template <typename T>
vec4<T> operator+(vec4<T> first, vec4<T> second) {
    return { first.x + second.x, first.y + second.y, first.z + second.z, first.w + second.w };
}
template <typename T>
vec4<T> operator-(vec4<T> first, vec4<T> second) {
    return { first.x - second.x, first.y - second.y, first.z - second.z, first.w - second.w };
}

template <typename T>
vec4<T> operator*(vec4<T> first, T second) {
    return { first.x * second, first.y * second, first.z * second, first.w * second };
}
template <typename T>
vec4<T> operator*(T first, vec4<T> second) {
    return { second.x * first, second.y * first, second.z * first, second.w * first };
}
template <typename T>
vec4<T> operator/(vec4<T> first, T second) {
    return { first.x / second, first.y / second, first.z / second, first.w / second };
}
template <typename T>
vec4<T> operator/(T first, vec4<T> second) {
    return { second.x / first, second.y / first, second.z / first, second.w / first };
}

template <typename T>
vec4<T>& operator+=(vec4<T>& first, vec4<T> second) {
    first.x += second.x;
    first.y += second.y;
    first.z += second.z;
    first.w += second.w;
    return first;
}
template <typename T>
vec4<T>& operator-=(vec4<T>& first, vec4<T> second) {
    first.x -= second.x;
    first.y -= second.y;
    first.z -= second.z;
    first.w -= second.w;
    return first;
}
template <typename T>
vec4<T>& operator*=(vec4<T>& first, T second) {
    first.x *= second;
    first.y *= second;
    first.z *= second;
    first.w *= second;
    return first;
}
template <typename T>
vec4<T>& operator/=(vec4<T>& first, T second) {
    first.x /= second;
    first.y /= second;
    first.z /= second;
    first.w /= second;
    return first;
}
template <typename T>
bool operator==(vec4<T> first, vec4<T> second) {
    return first.x == second.x && first.y == second.y && first.z == second.z && first.w == second.w;
}
template <typename T>
bool operator!=(vec4<T> first, vec4<T> second) {
    return first.x != second.x || first.y != second.y || first.z != second.z || first.w != second.w;
}

template <typename T>
T magnitude(vec4<T> self) {
    return sqrt(self.x * self.x + self.y * self.y + self.z * self.z + self.w * self.w);
}

template <typename T>
vec4<T> normalized(vec4<T> self) {
    T mag = magnitude(self);
    return { self.x / mag, self.y / mag, self.z / mag, self.w / mag};
}

template <typename T>
T dot(vec4<T> first, vec4<T> second) {
    return first.x * second.x + first.y * second.y + first.z * second.z + first.w * second.w;
}

}
