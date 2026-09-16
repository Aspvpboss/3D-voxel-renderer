#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

#include "display.hpp"

class Program {

    public:
        GLFWwindow *window = nullptr;
        Program(int width, int height, const char *window_title);
        ~Program();
        void loop();

    private:
        void display();

};


#endif