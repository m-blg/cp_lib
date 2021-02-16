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


    template <typename S>
    operator Vector2<S>() {
        return {(S)x, (S)y};
    }

    // Functions
    static Vector2<T> zero() {
        return { 0, 0 };
    }

    static Vector2<T> one() {
        return { 1, 1 };
    }
};

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


    template <typename S>
    operator Vector3<S>() {
        return {(S)x, (S)y, (S)z};
    }
    

    static Vector3<T> zero() {
        return { 0, 0, 0 };
    }

    static Vector3<T> one() {
        return { 1, 1, 1 };
    }

};


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
    struct {T w, x, y, z;};
    struct {T a, r, g, b;};
    sbuff<T, 4> buffer;
    
    
    Vector4() = default;
    Vector4(T _w, T _x, T _y, T _z) { w = _w; x = _x; y = _y; z = _z; }


    template <typename S>
    operator Vector4<S>() {
        return {(S) w, (S)x, (S)y, (S)z};
    }
    

    static Vector4<T> zero() {
        return { 0, 0, 0, 0 };
    }

    static Vector4<T> one() {
        return { 1, 1, 1, 1 };
    }

};


template <typename T>
using vec4 = Vector4<T>;

using vec4f = Vector4<f32>;
using vec4i = Vector4<i32>;
using vec4u = Vector4<u32>;    
using vec4d = Vector4<f64>;


template <typename T>
vec4<T> operator+(vec4<T> first, vec4<T> second) {
    return { first.w + second.w, first.x + second.x, first.y + second.y, first.z + second.z };
}
template <typename T>
vec4<T> operator-(vec4<T> first, vec4<T> second) {
    return { first.w - second.w, first.x - second.x, first.y - second.y, first.z - second.z };
}

template <typename T>
vec4<T> operator*(vec4<T> first, T second) {
    return { first.w * second, first.x * second, first.y * second, first.z * second };
}
template <typename T>
vec4<T> operator*(T first, vec4<T> second) {
    return { second.w * first, second.x * first, second.y * first, second.z * first };
}
template <typename T>
vec4<T> operator/(vec4<T> first, T second) {
    return { first.w / second, first.x / second, first.y / second, first.z / second };
}
template <typename T>
vec4<T> operator/(T first, vec4<T> second) {
    return { second.w / first, second.x / first, second.y / first, second.z / first };
}

template <typename T>
vec4<T>& operator+=(vec4<T>& first, vec4<T> second) {
    first.w += second.w;
    first.x += second.x;
    first.y += second.y;
    first.z += second.z;
    return first;
}
template <typename T>
vec4<T>& operator-=(vec4<T>& first, vec4<T> second) {
    first.w -= second.w;
    first.x -= second.x;
    first.y -= second.y;
    first.z -= second.z;
    return first;
}
template <typename T>
vec4<T>& operator*=(vec4<T>& first, T second) {
    first.w *= second;
    first.x *= second;
    first.y *= second;
    first.z *= second;
    return first;
}
template <typename T>
vec4<T>& operator/=(vec4<T>& first, T second) {
    first.w /= second;
    first.x /= second;
    first.y /= second;
    first.z /= second;
    return first;
}
template <typename T>
bool operator==(vec4<T> first, vec4<T> second) {
    return first.w == second.w && first.x == second.x && first.y == second.y && first.z == second.z;
}
template <typename T>
bool operator!=(vec4<T> first, vec4<T> second) {
    return first.w != second.w || first.x != second.x || first.y != second.y || first.z != second.z;
}

template <typename T>
T magnitude(vec4<T> self) {
    return sqrt(self.w * self.w + self.x * self.x + self.y * self.y + self.z * self.z);
}

template <typename T>
vec4<T> normalized(vec4<T> self) {
    T mag = magnitude(self);
    return { self.w / mag, self.x / mag, self.y / mag, self.z / mag };
}

template <typename T>
T dot(vec4<T> first, vec4<T> second) {
    return first.w * second.w + first.x * second.x + first.y * second.y + first.z * second.z;
}

}
