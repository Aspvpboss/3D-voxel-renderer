#include "program.hpp"

void window_reshape_callback(GLFWwindow *window, int newWidth, int newHeight){
	glViewport(0, 0, newWidth, newHeight);
}

Program::Program(int width, int height, const char *window_title){

    if(!glfwInit()) throw std::runtime_error("glfw3 failed to initialize");

    window = glfwCreateWindow(width, height, window_title, NULL, NULL);
    if(!window) throw std::runtime_error("glfw3 window failed to create");
    glfwSetWindowSizeCallback(window, window_reshape_callback);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

}

Program::~Program(){

    if(window) glfwDestroyWindow(window);
    window = nullptr;

}






void Program::loop(){

    while(!glfwWindowShouldClose(window)){
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

}






