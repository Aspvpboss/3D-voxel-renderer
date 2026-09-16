#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <stdexcept>

#include "renderer.hpp"

class Program {

    public:
        GLFWwindow *window = nullptr;
        Renderer renderer;
        Program(int width, int height, const char *window_title);
        ~Program();
        void loop();

    private:

};


#endif