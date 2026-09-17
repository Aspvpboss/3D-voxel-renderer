#ifndef RENDERER_MATH_HPP
#define RENDERER_MATH_HPP

class mat4 {
    public:
        mat4(float x);
        mat4(float x1, float x2, float x3, float x4,
            float x5, float x6, float x7, float x8, 
            float x9, float x10, float x11, float x12, 
            float x13, float x14, float x15, float x16);
            
        void print();
        
    private:
        mat4 operator*(const mat4& other) const;
        float data[16] = {0};
};

class vec3 {
    public:
        float x = 0, y = 0, z = 0;
        
        vec3(float xyz);
        vec3(float x, float y, float z);

        vec3 operator*(const vec3& other) const;
};

#endif