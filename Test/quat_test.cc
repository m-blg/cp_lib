#include "../quaternion.cc"

using namespace cp;

int main() {
    vec3f v1 = { 1, 1, 0};
    quat rot; rot.init({0, 1, 0}, (float)M_PI);
    vec3f v2 = rot * v1;
    printf("%f %f %f\n", v2.x, v2.y, v2.z);
}