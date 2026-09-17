#include "math.hpp"




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