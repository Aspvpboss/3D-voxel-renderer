#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <memory>

#include "renderer.hpp"
#include "camera.hpp"

class Program {

    public:
        GLFWwindow *window = nullptr;
        std::unique_ptr<Renderer> renderer;
        std::unique_ptr<Camera> camera;
        Program(int width, int height, const char *window_title);
        ~Program();
        void loop();

    private:

};


#endif