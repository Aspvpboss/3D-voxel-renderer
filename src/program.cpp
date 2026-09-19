#include "program.hpp"

void window_reshape_callback(GLFWwindow *window, int newWidth, int newHeight){
	glViewport(0, 0, newWidth, newHeight);
}

Program::Program(int width, int height, const char *window_title){

    if(!glfwInit()) 
        throw std::runtime_error("glfw3 failed to initialize");

    window = glfwCreateWindow(width, height, window_title, NULL, NULL);
    if(!window) 
        throw std::runtime_error("glfw3 window failed to create");

    glfwSetWindowSizeCallback(window, window_reshape_callback);
  
    glfwMakeContextCurrent(window);
   
    if(glewInit() != GLEW_OK) 
        throw std::runtime_error("glew failed to initilize");
    
    glfwSwapInterval(1);

}

Program::~Program(){

    if(window) glfwDestroyWindow(window);
    window = nullptr;
    glfwTerminate();

}


void Program::loop(){

    vec3 testVec(1.0f, 2.0f, 3.0f);
    mat4 testMat = math::translate(mat4(1.0f), vec3(2.0f));

    testVec = testMat * testVec;

    testVec.print();

    while(!glfwWindowShouldClose(window)){
        if(renderer.render()) throw std::runtime_error("failed to render a frame"); 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}






