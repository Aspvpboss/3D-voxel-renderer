#include "math.hpp"
#include <mem.h>
#include <iostream>
#include <cmath>


mat4::mat4(float x00, float x01, float x02, float x03,
           float x10, float x11, float x12, float x13, 
           float x20, float x21, float x22, float x23, 
           float x30, float x31, float x32, float x33){

    data[0] = x00; data[4] = x01; data[8]  = x02; data[12] = x03;
    data[1] = x10; data[5] = x11; data[9]  = x12; data[13] = x13;
    data[2] = x20; data[6] = x21; data[10] = x22; data[14] = x23;
    data[3] = x30; data[7] = x31; data[11] = x32; data[15] = x33;

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


float math::dot(const vec3& v1, const vec3& v2){
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}


mat4 math::perspective(float fovy_degrees, float aspect, float near, float far){

    float tanHalffovy = tanf(math::radians(fovy_degrees) / 2.0f);
    mat4 perp(1 / ((aspect * tanHalffovy)), 0, 0, 0,
            0, 1 / tanHalffovy, 0, 0,
            0, 0, (far + near) / (near - far), 2 * (far * near) / (near - far),
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