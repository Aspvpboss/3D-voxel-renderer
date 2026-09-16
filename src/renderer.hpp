#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Renderer {

    public:
        GLFWwindow *window = nullptr;
        
        Renderer();
        ~Renderer();
        int bindWindow(GLFWwindow *window_to_bind);
        int render();

};

#endif