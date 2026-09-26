#pragma once

#include <GLFW/glfw3.h>
#include "math.hpp"

class Camera {

    public:

        enum CameraKeybinds{
            MOVE_FORWARD,
            MOVE_BACKWARD,
            MOVE_RIGHT,
            MOVE_LEFT,
            MOVE_UP,
            MOVE_DOWN,
            ROTATE_UP,
            ROTATE_DOWN,
            ROTATE_RIGHT,
            ROTATE_LEFT,
            ROTATE_ROLL_LEFT,
            ROTATE_ROLL_RIGHT,
            KEYBIND_SIZE,
        };

        float cameraXrot = 0.0f, cameraYrot = 0.0f, cameraZrot = 0.0f;
        float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 0.0f;
        float cameraSpeed = 1.0f;
        float rotationSpeed = 1.0f;

        Camera();
        ~Camera();
        void HandleMovement();
        mat4 buildCameraMatrix();
        const mat4& getPerspectiveMatrix();
        bool updatePerspectiveMatrix(float fovy, float near, float far);
        bool updatePerspectiveMatrix(float fovy);
        bool updatePerspectiveMatrix();
        bool updatePerspectiveMatrix(float near, float far);
        bool bindWindow(GLFWwindow *window_to_bind);
            
    private:
        int camera_keybinds[KEYBIND_SIZE];
        int buf_width = 0, buf_height = 0;
        float aspect = 0.0f; float fovy = 0.0f; float near = 0.0f; float far = 0.0f;
        
        GLFWwindow *binded_window = nullptr;
        mat4 perspectiveMat;
        
        mat4 buildLookAt();
};