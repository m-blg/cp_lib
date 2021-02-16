
#pragma once

#include "mbgldef.h"
#include "buffer.cc"
#include "vector.cc"
#include <math.h>

namespace cp {


struct Quaternion {
    float w, x, y, z;


    void init(vec3f axis, float angle) {
        w = cos(angle / 2);
        x = axis.x * sin(angle / 2);
        y = axis.y * sin(angle / 2);
        z = axis.z * sin(angle / 2);
    }

};

using quat = Quaternion;


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

float norm(quat q) {
    return sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
}

quat normalized(quat q) {
    float n = norm(q);
    return { q.w / n, q.x / n, q.y / n, q.z / n };
}




}
