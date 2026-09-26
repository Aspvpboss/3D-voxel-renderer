#include "program.hpp"
#include <iostream>

void window_reshape_callback(GLFWwindow *window, int newWidth, int newHeight){
	glViewport(0, 0, newWidth, newHeight);
}

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
                                GLenum severity, GLsizei length,
                                const GLchar* message, const void* userParam) {
    
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) return;

    std::cerr << "GL CALLBACK: " << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "") 
              << " type = 0x" << std::hex << type 
              << ", severity = 0x" << severity 
              << ", message = " << message << std::dec << std::endl;

    if (type == GL_DEBUG_TYPE_ERROR) {
        #if defined(_MSC_VER)
            __debugbreak(); // Visual Studio
        #elif defined(__GNUC__)
            __builtin_trap(); // GCC/Clang
        #endif
    }
}

Program::Program(int width, int height, const char *window_title){

    if(!glfwInit()) 
        throw std::runtime_error("glfw3 failed to initialize");

    window = glfwCreateWindow(width, height, window_title, NULL, NULL);
    if(!window) 
        throw std::runtime_error("glfw3 window failed to create");

    glfwSetWindowSizeCallback(window, window_reshape_callback);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
  
    glfwMakeContextCurrent(window);
   
    if(glewInit() != GLEW_OK) 
        throw std::runtime_error("glew failed to initilize");
    
    glfwSwapInterval(1);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
    glDebugMessageCallback(MessageCallback, 0);

    try{
        renderer = std::make_unique<Renderer>();
    } catch(const std::exception& e){
        throw;
    }

    renderer->bindWindow(window);
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
        if(renderer->render()) throw std::runtime_error("failed to render a frame"); 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}






