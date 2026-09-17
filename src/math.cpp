#include "math.hpp"
#include <mem.h>
#include <iostream>
#include <cmath>

mat4::mat4(float x){
    for(int i = 0; i < 16; i++){
        data[i] = x;
    }
}

mat4::mat4(float x1, float x2, float x3, float x4,
    float x5, float x6, float x7, float x8, 
    float x9, float x10, float x11, float x12, 
    float x13, float x14, float x15, float x16){

    data[0] = x1; data[1] = x2; data[2] = x3; data[3] = x4;
    data[4] = x5; data[5] = x6; data[6] = x7; data[7] = x8;
    data[8] = x9; data[9] = x10; data[10] = x11; data[11] = x12;
    data[12] = x13; data[13] = x14; data[14] = x15; data[15] = x16;
}

mat4::mat4(float x1, float x2, float x3, float x4,
    float x5, float x6, float x7, float x8, 
    float x9, float x10, float x11, float x12, 
    float x13, float x14, float x15, float x16){

    data[0] = x1; data[1] = x2; data[2] = x3; data[3] = x4;
    data[4] = x5; data[5] = x6; data[6] = x7; data[7] = x8;
    data[8] = x9; data[9] = x10; data[10] = x11; data[11] = x12;
    data[12] = x13; data[13] = x14; data[14] = x15; data[15] = x16;            
}

void mat4::print(){

    for(int y = 0; y < 4; y++){
        for(int x = 0; x < 4; x++){
            std::cout << data[y * 4 + x] << " ";
        }
        std::cout << std::endl;
    }
}

mat4 mat4::operator*(const mat4& other) const{
    mat4 result(0);
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                result.data[i * 4 + j] += data[i * 4 + k] * other.data[k * 4 + j];
            }
        }
    }
    return result;
}

vec3::vec3(float xyz){
    vec3::x = xyz;
    vec3::y = xyz;
    vec3::z = xyz;
}

vec3::vec3(float x, float y, float z){
    vec3::x = x;
    vec3::y = y;
    vec3::z = z;
}


vec3 vec3::operator*(const vec3& other) const{
    return vec3(this->x * other.x, this->y * other.y, this->z * other.z);
}

float math::radians(float degrees){
    return (degrees * math::PI_FLOAT) / 180.0f;
}

float math::degrees(float radians){
    return (radians * 180) / math::PI_FLOAT;
}

mat4 math::translate(const mat4& base, const vec3& offset){

    mat4 trans(1.0f, 0.0f, 0.0f, offset.x,
               0.0f, 1.0f, 0.0f, offset.y,
               0.0f, 0.0f, 1.0f, offset.z,
               0.0f, 0.0f, 0.0f, 1.0f);

    return base * trans;
}

mat4 math::rotationX(const mat4& base, float radians){
    mat4 trans(1, 0.0f, 0.0f, 0.0f,
               0.0f, cosf(radians), -sinf(radians), 0.0f,
               0.0f, sinf(radians), cosf(radians), 0.0f,
               0.0f, 0.0f, 0.0f, 1.0f);
    
    return base * trans;
}

mat4 math::rotationY(const mat4& base, float radians){
    mat4 trans(cosf(radians), 0.0f, sinf(radians), 0,
               0.0f, 1.0f, 0.0f, 0,
               -sinf(radians), 0.0f, cosf(radians), 0,
               0.0f, 0.0f, 0.0f, 1.0f);
    
    return base * trans;
}

mat4 math::rotationZ(const mat4& base, float radians){
    mat4 trans(cosf(radians), -sinf(radians), 0.0f, 0.0f,
               sinf(radians), cosf(radians), 0.0f, 0.0f,
               0.0f, 0.0f, 1.0f, 0.0f,
               0.0f, 0.0f, 0.0f, 1.0f);
    
    return base * trans;
}