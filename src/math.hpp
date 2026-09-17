#ifndef RENDERER_MATH_HPP
#define RENDERER_MATH_HPP

class mat4 {
    private:
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