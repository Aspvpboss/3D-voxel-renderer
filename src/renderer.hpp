#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "math.hpp"
#include "camera.hpp"

#define NUM_VBOS 10
#define NUM_VAOS 10
#define NUM_RPS 1

class Renderer {

    public:
        GLFWwindow *window = nullptr;
        
        Renderer();
        ~Renderer();
        int bindWindow(GLFWwindow *window_to_bind);
        int render(const std::unique_ptr<Camera>& camera);

    private:
        GLuint vbo[NUM_VBOS] = {0};
        GLuint vao[NUM_VAOS] = {0};
        GLuint renderingPrograms[NUM_RPS] = {0};
        GLuint pMat = 0; GLuint mMat = 0;
};

#endif