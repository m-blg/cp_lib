
#pragma once

#include "mbgldef.h"
#include "buffer.cc"
#include "vector.cc"
#include "matrix.cc"
#include <math.h>

namespace cp {


template <typename T>
using cmpx = vec2<T>;

using cmpxf = cmpx<f32>;
using cmpxi = cmpx<i32>;
using cmpxu = cmpx<u32>;


template <typename T>
T abs(cmpx<T> z) {
    return magnitude(z);
}

template <typename T>
T abs2(cmpx<T> z) {
    return z.x * z.x + z.y * z.y;
}

template <typename T>
cmpx<T> conjugate(cmpx<T> z) {
    return {z.x, -z.y};
}

template <typename T>
cmpx<T> operator*(cmpx<T> z1, cmpx<T> z2) {
    return {z1.x * z2.x - z1.y * z2.y, z1.y * z2.x + z1.x * z2.y};
}

template <typename T>
cmpx<T> operator/(cmpx<T> z1, cmpx<T> z2) {
    return z1 * conjugate(z2) / abs2(z2);
}

struct Quaternion {
    f32 w, x, y, z;

    Quaternion() = default;
    Quaternion(f32 _w, f32 _x, f32 _y, f32 _z);
    Quaternion(vec3f axis, f32 angle);
};

using quat = Quaternion;

Quaternion::Quaternion(f32 _w, f32 _x, f32 _y, f32 _z) 
: w(_w), x(_x), y(_y), z(_z) {}


Quaternion::Quaternion(vec3f axis, f32 angle) {
    this->w = cos(angle / 2);
    this->x = axis.x * sin(angle / 2);
    this->y = axis.y * sin(angle / 2);
    this->z = axis.z * sin(angle / 2);
}


void init(quat *self, vec3f axis, f32 angle) {
    self->w = cos(angle / 2);
    self->x = axis.x * sin(angle / 2);
    self->y = axis.y * sin(angle / 2);
    self->z = axis.z * sin(angle / 2);
}


quat inverse(quat q);


quat operator*(quat first, quat second) {
    return {
        first.w * second.w - first.x * second.x - first.y * second.y - first.z * second.z, 
        first.w * second.x + first.x * second.w + first.y * second.z - first.z * second.y, 
        first.w * second.y - first.x * second.z + first.y * second.w + first.z * second.x, 
        first.w * second.z + first.x * second.y - first.y * second.x + first.z * second.w 
    };
}

vec3f operator*(quat first, vec3f second) {
    quat q = {0, second.x, second.y, second.z};
    q = first * q * inverse(first);
    return { q.x, q.y, q.z };
}

quat inverse(quat q) {
    return { q.w, -q.x, -q.y, -q.z };
}

f32 norm(quat q) {
    return sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
}

quat normalized(quat q) {
    f32 n = norm(q);
    return { q.w / n, q.x / n, q.y / n, q.z / n };
}


mat3f vec_rot_mat3(quat q) {
    return {
        2 * (q.w * q.w + q.x * q.x) - 1, 2 * (q.x * q.y - q.w * q.z), 2 * (q.w * q.y + q.x * q.z),
        2 * (q.w * q.z + q.x * q.y), 2 * (q.w * q.w + q.y * q.y) - 1, 2 * (q.y * q.z - q.w * q.x),
        2 * (q.x * q.z - q.w * q.y), 2 * (q.w * q.x + q.y * q.z), 2 * (q.w * q.w + q.z * q.z) - 1
    };
}

mat4f vec_rot_mat4(quat q) {
    return {
        2 * (q.w * q.w + q.x * q.x) - 1, 2 * (q.x * q.y - q.w * q.z), 2 * (q.w * q.y + q.x * q.z), 0,
        2 * (q.w * q.z + q.x * q.y), 2 * (q.w * q.w + q.y * q.y) - 1, 2 * (q.y * q.z - q.w * q.x), 0,
        2 * (q.x * q.z - q.w * q.y), 2 * (q.w * q.x + q.y * q.z), 2 * (q.w * q.w + q.z * q.z) - 1, 0,
        0,                           0,                           0,                               1
    };
}


}
