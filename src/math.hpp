#ifndef RENDERER_MATH_HPP
#define RENDERER_MATH_HPP



class mat4 {
    public:
        mat4(float x);
        mat4(float x00, float x01, float x02, float x03,
             float x10, float x11, float x12, float x13, 
             float x20, float x21, float x22, float x23, 
             float x30, float x31, float x32, float x33);

        void print();
        
        mat4 operator*(const mat4& other) const;
        float data[16] = {0};
};

class vec3 {
    public:
        float x = 0, y = 0, z = 0;
        
        vec3(float xyz);
        vec3(float x, float y, float z);
        void print();

        vec3 operator*(const vec3& other) const;
        vec3 operator+(const vec3& other) const;
        vec3 operator-(const vec3& other) const;
        friend vec3 operator*(const mat4& m, const vec3& v);
};

namespace math {
    const double PI_DOUBLE = 3.141592653589793115997963468544185161590576171875;
    const float PI_FLOAT = 3.1415927;
    float radians(float degrees);
    float degrees(float radians);
    
    float dot(const vec3& v1, const vec3& v2);
    
    mat4 perspective(float fovy_degrees, float aspect, float near, float far);
    mat4 translate(const mat4& base, const vec3& offset);
    mat4 rotationX(const mat4& base, float radians);
    mat4 rotationY(const mat4& base, float radians);
    mat4 rotationZ(const mat4& base, float radians);
    
};

#endif