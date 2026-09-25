#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "math.hpp"

#define NUM_VBOS 10
#define NUM_VAOS 10
#define NUM_RPS 1

class Renderer {

    public:
        GLFWwindow *window = nullptr;
        
        Renderer();
        ~Renderer();
        int bindWindow(GLFWwindow *window_to_bind);
        int render();

    private:
        GLuint vbo[NUM_VBOS];
        GLuint vao[NUM_VAOS];
        GLuint renderingPrograms[NUM_RPS];
        GLuint pMat = 0; GLuint mMat = 0;
};

#endif