#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>
#include "math.hpp"
#include "camera.hpp"
#include "voxel.hpp"

#define NUM_VBOS 3
#define NUM_VAOS 20
#define NUM_RPS 1

class Renderer {

    public:
        GLFWwindow *window = nullptr;
        
        Renderer(std::vector<std::string> texture_paths, std::vector<Voxel> voxels);
        ~Renderer();
        int bindWindow(GLFWwindow *window_to_bind);
        int render(const std::unique_ptr<Camera>& camera);

    private:
        std::vector<GLuint> textures;
        std::vector<Voxel> voxels;
        GLuint vbo[NUM_VBOS] = {0};
        GLuint vao[NUM_VAOS] = {0};
        GLuint renderingPrograms[NUM_RPS] = {0};
        GLuint perpMatloc = 0; GLuint modelMatloc = 0; GLuint viewMatloc = 0;
        GLuint lightPosloc = 0; GLuint lightColorloc = 0;

};

#endif