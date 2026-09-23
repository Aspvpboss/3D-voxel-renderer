#include "math.hpp"
#include <mem.h>
#include <iostream>
#include <cmath>


mat4::mat4(float x1, float x2, float x3, float x4,
    float x5, float x6, float x7, float x8, 
    float x9, float x10, float x11, float x12, 
    float x13, float x14, float x15, float x16){

    data[0] = x1; data[1] = x2; data[2] = x3; data[3] = x4;
    data[4] = x5; data[5] = x6; data[6] = x7; data[7] = x8;
    data[8] = x9; data[9] = x10; data[10] = x11; data[11] = x12;
    data[12] = x13; data[13] = x14; data[14] = x15; data[15] = x16;
}

mat4::mat4(float x){
    data[0] = x; data[1] = 0.0f; data[2] = 0.0f; data[3] = 0.0f;
    data[4] = 0.0f; data[5] = x; data[6] = 0.0f; data[7] = 0.0f;
    data[8] = 0.0f; data[9] = 0.0f; data[10] = x; data[11] = 0.0f;
    data[12] = 0.0f; data[13] = 0.0f; data[14] = 0.0f; data[15] = x;
}



void mat4::print(){

    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            std::cout << data[col * 4 + row] << " ";
        }
        std::cout << std::endl;
    }
}

mat4 mat4::operator*(const mat4& other) const {
    mat4 result(0.0f);
    for(int col = 0; col < 4; col++) {
        for(int row = 0; row < 4; row++) {
            float sum = 0.0f;
            for(int k = 0; k < 4; k++) {
                sum += this->data[k * 4 + row] * other.data[col * 4 + k];
            }
            result.data[col * 4 + row] = sum;
        }
    }
    return result;
}

vec3 operator*(const mat4& m, const vec3& v) {
    float implicit_w = 1.0f;
    
    float out_x = m.data[0] * v.x + m.data[4] * v.y + m.data[8] * v.z  + m.data[12] * implicit_w;
    float out_y = m.data[1] * v.x + m.data[5] * v.y + m.data[9] * v.z  + m.data[13] * implicit_w;
    float out_z = m.data[2] * v.x + m.data[6] * v.y + m.data[10] * v.z + m.data[14] * implicit_w;
    
    return vec3(out_x, out_y, out_z);
}

vec3 vec3::operator*(const vec3& other) const{
    return vec3(this->x * other.x, this->y * other.y, this->z * other.z);
}
vec3 vec3::operator+(const vec3& other) const{
    return vec3(this->x + other.x, this->y + other.y, this->z + other.z);
}
vec3 vec3::operator-(const vec3& other) const{
    return vec3(this->x - other.x, this->y - other.y, this->z - other.z);
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

void vec3::print(){
    std::cout << "vec3(" << x << ", " << y << ", " << z << ")" << std::endl;
}



float math::radians(float degrees){
    return (degrees * math::PI_FLOAT) / 180.0f;
}

float math::degrees(float radians){
    return (radians * 180) / math::PI_FLOAT;
}


mat4 math::perspective(float fovy_degrees, float aspect, float near, float far){

    float tanHalffovy = tanf(math::radians(fovy_degrees) / 2.0f);
    mat4 perp(1 / ((aspect * tanHalffovy)), 0, 0, 0,
            0, 1 / tanHalffovy, 0, 0,
            0, 0, (far+near) / (far-near), 2 * (far* near) / (near - far),
            0, 0, -1, 0);

    return perp;
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