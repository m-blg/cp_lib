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

    Vector2 operator+(const Vector2& other) const {
        return { this->x + other.x, this->y + other.y };
    }
    Vector2 operator-(const Vector2& other) const {
        return { this->x - other.x, this->y - other.y };
    }
    Vector2 operator*(const T& other) const {
        return { this->x * other, this->y * other };
    }
    Vector2 operator/(const T& other) const {
        return { this->x / other, this->y / other };
    }
    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vector2& operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Vector2& operator*=(const T& other) {
        x *= other;
        y *= other;
        return *this;
    }
    Vector2& operator/=(const T& other) {
        x /= other;
        y /= other;
        return *this;
    }
    bool operator==(const Vector2& other) const {
        return this->x == other.x && this->y == other.y;
    }
    bool operator!=(const Vector2& other) const {
        return this->x != other.x || this->y != other.y;
    }

    // Functions

    static T magnitude(Vector2<T> *self) {
        return sqrt(self->x * self->x + self->y * self->y);
    }

    static Vector2<T> normalized(Vector2<T> *self) {
        T magnitude = self->magnitude();
        return { self->x / magnitude, self->y / magnitude };
    }

    static T dot(const Vector2<T> *first, Vector2<T> *second) {
        return first->x * second->x + first->y * second->y;
    }

    static Vector2<T> zero() {
        return { 0, 0 };
    }

    static Vector2<T> one() {
        return { 1, 1 };
    }
};

template<typename T>
union Vector3 {
    struct {T x, y, z;};
    struct {T r, g, b;};
    struct {T u, v;};
    sbuff<T, 3> buffer;
    
    
    Vector3() = default;
    Vector3(T _x, T _y, T _z) { x = _x; y = _y; z = _z; }

    Vector3 operator+(const Vector3& other) const {
        return { x + other.x, y + other.y, z + other.z };
    }
    Vector3 operator-(const Vector3& other) const {
        return { x - other.x, y - other.y, z - other.z };
    }
    Vector3 operator*(const T& other) const {
        return { x * other, y * other, z * other };
    }
    Vector3 operator/(const T& other) const {
        return { x / other, y / other, z / other };
    }
    Vector3& operator+=(const Vector3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    Vector3& operator-=(const Vector3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
    Vector3& operator*=(const T& other) {
        x *= other;
        y *= other;
        z *= other;
        return *this;
    }
    Vector3& operator/=(const T& other) {
        x /= other;
        y /= other;
        z /= other;
        return *this;
    }
    bool operator==(const Vector3& other) const {
        return this->x == other.x && this->y == other.y && this->z == other.z;
    }
    bool operator!=(const Vector3& other) const {
        return this->x != other.x || this->y != other.y || this->z != other.z;
    }
    
    
    // Functions
    
    static T magnitude(Vector3<T> *self) {
        return sqrt(self->x * self->x + self->y * self->y + self->z * self->z);
    }

    static Vector3<T> normalized(Vector3<T> *self) {
        T mag = magnitude(self);
        return { self->x / mag, self->y / mag, self->z / mag };
    }

    static T dot3(const Vector3<T> *first, const Vector3<T> *second) {
        return first->x * second->x + first->y * second->y + first->z * second->z;
    }

    static Vector3<T> cross(const Vector3<T> *first, const Vector3<T> *second) {
        return { first->y * second->z - second->y * first->z, second->x * first->z - first->x * second->z, first->x * second->y - second->x * first->y };
    }

    static Vector3<T> zero() {
        return { 0, 0, 0 };
    }

    static Vector3<T> one() {
        return { 1, 1, 1 };
    }

};

template <typename T>
using vec2 = Vector2<T>;

using vec2f = Vector2<f32>;
using vec2i = Vector2<i32>;
using vec2u = Vector2<u32>;    
using vec2d = Vector2<f64>;

template <typename T>
using vec3 = Vector3<T>;

using vec3f = Vector3<f32>;
using vec3i = Vector3<i32>;
using vec3u = Vector3<u32>;    
using vec3d = Vector3<f64>;

}
