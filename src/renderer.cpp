#include "renderer.hpp"

Renderer::Renderer(){

}


Renderer::~Renderer(){

}

int Renderer::bindWindow(GLFWwindow *window_to_bind){
    if(!window_to_bind || window) return 1;
    window = window_to_bind; 

    return 0;
}

int Renderer::render(){
    glClear(GL_COLOR_BUFFER_BIT);

    return 0;
}