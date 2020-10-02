#pragma once

#include "mbgldef.h"
#include <math.h>

namespace cp {
    template<typename T>
    struct Vector2 {
        union {
            struct {T x, y;};
            struct {T u, v;};
        };        
        
        void init(T _x, T _y) { x = _x; y = _y; }
    
        T magnitude() const {
            return sqrt(pow(this->x, 2) + pow(this->y, 2));
        }
        Vector2 normalized() const {
            T magnitude = this->magnitude();
            return { this->x / magnitude, this->y / magnitude };
        }

        static T dot(const Vector2 *first, const Vector2 *second) {
            return first->x * second->x + first->y * second->y;
        }

        static Vector2 zero() {
            return { 0, 0 };
        }
        static Vector2 one() {
            return { 1, 1 };
        }

        Vector2 rotated(T angle) const {
            float andleInRad = angle * (M_PI / 180);
            return { x*cos(andleInRad) - y*sin(andleInRad), x*sin(andleInRad) + y*cos(andleInRad) };
        }

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
    };

    template<typename T>
    struct Vector3 {
        union {
            struct {T x, y, z;};
            struct {T r, g, b;};
            struct {T u, v;};
        };
        
        
        void init(T _x, T _y, T _z) { x = _x; y = _y; z = _z; }

        T magnitude() {
            return sqrt(x*x + y*y + z*z);
        }
        Vector3 normalized() {
            T mag = magnitude();
            return { x / mag, y / mag, z / mag };
        }

        static T dot(const Vector3 *first, const Vector3 *second) {
            return first->x * second->x + first->y * second->y + first->z * second->z;
        }

        static Vector3 cross(const Vector3 *first, const Vector3 *second) {
            return { first->y * second->z - second->y * first->z, second->x * first->z - first->x * second->z, first->x * second->y - second->x * first->y };
        }

        static Vector3 zero() {
            return { 0, 0, 0 };
        }
        static Vector3 one() {
            return { 1, 1, 1 };
        }


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

    };

    using vec2 = Vector2<f32>;
    using vec2i = Vector2<i32>;
    using vec2u = Vector2<u32>;    
    using vec2d = Vector2<f64>;

    using vec3 = Vector3<f32>;
    using vec3i = Vector3<i32>;
    using vec3u = Vector3<u32>;    
    using vec3d = Vector3<f64>;

    vec2i::magnitude();
    sarri<5>::stuff();

}
