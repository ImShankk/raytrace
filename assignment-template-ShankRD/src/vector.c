#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include <math.h>


Vec3 add(Vec3 v1, Vec3 v2) {
    Vec3 ans = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
    return ans;
}

Vec3 subtract(Vec3 v1, Vec3 v2) {
    Vec3 ans = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
    return ans;
}

Vec3 scalarMultiply(float s, Vec3 v) {
    Vec3 ans = {s * v.x, s * v.y, s * v.z};
    return ans;
}

Vec3 scalarDivide(Vec3 v, float d) {

    // if (d == 0) {
    //     printf("ERROR: CANNOT DIVIDE BY ZERO.\n");  //ilya said not needed
    //     return v;  //original vector unchanged
    // }

    Vec3 ans = {v.x / d, v.y / d, v.z / d};
    return ans;
}


Vec3 normalize(Vec3 v){
    double divider = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);  //to absoulute value it
    Vec3 ans = {v.x / divider, v.y / divider, v.z / divider};
    return ans;
}


float dot(Vec3 v1, Vec3 v2){
    //dot product
    return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

float length2(Vec3 v){

    return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}
float length(Vec3 v) {

    return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}
float distance2(Vec3 v1, Vec3 v2){
    return (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y) + (v1.z - v2.z) * (v1.z - v2.z);
}
float distance(Vec3 v1, Vec3 v2) {
    return sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y) + (v1.z - v2.z) * (v1.z - v2.z));
}