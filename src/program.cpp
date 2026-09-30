#include "program.hpp"
#include <iostream>


void window_reshape_callback(GLFWwindow *window, int newWidth, int newHeight){
    glViewport(0, 0, newWidth, newHeight);

    Program* program = static_cast<Program*>(glfwGetWindowUserPointer(window));
    program->camera->updatePerspectiveMatrix();
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

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    window = glfwCreateWindow(width, height, window_title, NULL, NULL);
    if(!window) 
        throw std::runtime_error("glfw3 window failed to create");

    glfwSetWindowUserPointer(window, this);
    glfwSetWindowSizeCallback(window, window_reshape_callback);
    glfwMakeContextCurrent(window);
  
    
    if(glewInit() != GLEW_OK) 
        throw std::runtime_error("glew failed to initilize");
    
    glfwSwapInterval(1);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
    glDebugMessageCallback(MessageCallback, 0);

    std::vector<Voxel> voxels;
    voxels.push_back(Voxel(vec3(0, 0, -8), vec3(0, 0, 0), DIRT_TEX));
    voxels.push_back(Voxel(vec3(2, 0, -8), vec3(0, 0, 0), DIRT_TEX));
    voxels.push_back(Voxel(vec3(4, 0, -8), vec3(0, 0, 0), DIRT_TEX));
    voxels.push_back(Voxel(vec3(2, 4, -60), vec3(0, 0, 0), DIRT_TEX));

    std::vector<std::string> textures;
    textures.push_back("assets/textures/sun.png"); 
    textures.push_back("assets/textures/dirt.jpg"); 

    try{
        renderer = std::make_unique<Renderer>(textures, voxels);
    } catch(const std::exception& e){
        throw;
    }

    renderer->bindWindow(window);

    camera = std::make_unique<Camera>(vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), 5.0f, 150.0f);
    camera->bindWindow(window);
    camera->updatePerspectiveMatrix(95.0f, 0.1f, 1000.0f);
}

Program::~Program(){

    if(window) glfwDestroyWindow(window);
    window = nullptr;
    glfwTerminate();

}


void Program::loop(){

    double lastFrame = 0.0;
    while(!glfwWindowShouldClose(window)){
        double currentFrame = glfwGetTime();
        double dt = currentFrame - lastFrame;
        lastFrame = currentFrame;
       
        camera->HandleMovement(dt);
        if(renderer->render(camera)) throw std::runtime_error("failed to render a frame"); 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}
