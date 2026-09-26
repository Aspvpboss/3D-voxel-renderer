#include "camera.hpp"
#include <cmath>

Camera::Camera(){

    camera_keybinds[MOVE_FORWARD] = GLFW_KEY_W; 
    camera_keybinds[MOVE_BACKWARD] = GLFW_KEY_S; 
    camera_keybinds[MOVE_RIGHT] = GLFW_KEY_D; 
    camera_keybinds[MOVE_LEFT] = GLFW_KEY_A;
    camera_keybinds[MOVE_UP] = GLFW_KEY_SPACE;
    camera_keybinds[MOVE_DOWN] = GLFW_KEY_LEFT_CONTROL;
    
    camera_keybinds[ROTATE_UP] = GLFW_KEY_UP; 
    camera_keybinds[ROTATE_DOWN] = GLFW_KEY_DOWN; 
    camera_keybinds[ROTATE_RIGHT] = GLFW_KEY_RIGHT; 
    camera_keybinds[ROTATE_LEFT] = GLFW_KEY_LEFT; 
    camera_keybinds[ROTATE_ROLL_LEFT] = GLFW_KEY_Z; 
    camera_keybinds[ROTATE_ROLL_RIGHT] = GLFW_KEY_X; 
	
}

Camera::~Camera(){}

bool Camera::bindWindow(GLFWwindow *window_to_bind){
	if(Camera::binded_window != nullptr || window_to_bind == nullptr){
		return false;
	}
	Camera::binded_window = window_to_bind;

	return true;
}


bool Camera::updatePerspectiveMatrix(float fovy, float near, float far){
	if (near <= 0){
		return false;	
	}
	if (far <= 0){
		return false;	
	}
	if (fovy < 0){
		return false;	
	}
	if (fovy > 180){
		return false;	
	}

	Camera::fovy = fovy;
	Camera::near = near;
	Camera::far = far;
	glfwGetFramebufferSize(binded_window, &buf_width, &buf_height);
	float aspect = (float)buf_width / (float)buf_height;
	Camera::aspect = aspect;
	perspectiveMat = math::perspective(math::radians(fovy), aspect, near, far);

	return true;
}
bool Camera::updatePerspectiveMatrix(float near, float far){
	if (near <= 0){
		return false;	
	}
	if (far <= 0){
		return false;	
	}
	
	Camera::fovy = fovy;
	Camera::near = near;
	glfwGetFramebufferSize(binded_window, &buf_width, &buf_height);
	float aspect = (float)buf_width / (float)buf_height;
	Camera::aspect = aspect;
	perspectiveMat = math::perspective(math::radians(fovy), aspect, near, far);
	
	return true;
}
bool Camera::updatePerspectiveMatrix(float fovy){
	if (fovy < 0){
		return false;	
	}
	if (fovy > 180){
		return false;	
	}
	
	Camera::fovy = fovy;
	glfwGetFramebufferSize(binded_window, &buf_width, &buf_height);
	float aspect = (float)buf_width / (float)buf_height;
	Camera::aspect = aspect;
	perspectiveMat = math::perspective(math::radians(fovy), aspect, near, far);
	
	return true;
}
bool Camera::updatePerspectiveMatrix(){
	glfwGetFramebufferSize(binded_window, &buf_width, &buf_height);
	float aspect = (float)buf_width / (float)buf_height;
	Camera::aspect = aspect;
	perspectiveMat = math::perspective(math::radians(fovy), aspect, near, far);
	
	return true;
}


const mat4& Camera::getPerspectiveMatrix(){
	return perspectiveMat;
}


mat4 Camera::buildCameraMatrix(){
    auto vMat = math::translate(mat4(1.0f), vec3(-cameraX, -cameraY, -cameraZ));
    auto rotMat = buildLookAt();

    return rotMat * vMat;
}


mat4 Camera::buildLookAt(){
    mat4 rotationMatrix = mat4(1.0f);
    rotationMatrix = math::rotationX(rotationMatrix, math::radians(cameraXrot)); // pitch
    rotationMatrix = math::rotationZ(rotationMatrix, math::radians(cameraZrot)); // roll
    rotationMatrix = math::rotationY(rotationMatrix, math::radians(cameraYrot)); // yaw

    return rotationMatrix;
}

vec2 angle_to_vectors(float degrees){

	vec2 vec;
	float radians = math::radians(degrees);

	vec.x = cos(radians);
	vec.y = sin(radians);

	return vec;
}

float limit_angle(float angle, float limit){
    if (angle > limit){
        angle = limit;
    }
    if (angle < -limit){
        angle = -limit;
    }
    return angle;
}

void Camera::HandleMovement(){

	if (glfwGetKey(binded_window, camera_keybinds[ROTATE_UP]) == GLFW_PRESS){
		cameraXrot -= rotationSpeed;
	}
	if (glfwGetKey(binded_window, camera_keybinds[ROTATE_DOWN]) == GLFW_PRESS){
		cameraXrot += rotationSpeed;
	}
	if (glfwGetKey(binded_window, camera_keybinds[ROTATE_RIGHT]) == GLFW_PRESS){
		cameraYrot += rotationSpeed;
	}
	if (glfwGetKey(binded_window, camera_keybinds[ROTATE_LEFT]) == GLFW_PRESS){
		cameraYrot -= rotationSpeed;
	}
	if (glfwGetKey(binded_window, camera_keybinds[ROTATE_ROLL_RIGHT]) == GLFW_PRESS){
		cameraZrot += rotationSpeed;
	}
	if (glfwGetKey(binded_window, camera_keybinds[ROTATE_ROLL_LEFT]) == GLFW_PRESS){
		cameraZrot -= rotationSpeed;
	}

    cameraXrot = limit_angle(cameraXrot, 90);
    cameraZrot = limit_angle(cameraZrot, 90);


    float cameraXvec = 0.0f;
    float cameraZvec = 0.0f;
	float cameraYvec = 0.0f;

    if (glfwGetKey(binded_window, camera_keybinds[MOVE_UP]) == GLFW_PRESS){
		cameraYvec += 1.0f;	
	}
	if (glfwGetKey(binded_window, camera_keybinds[MOVE_DOWN]) == GLFW_PRESS){
		cameraYvec -= 1.0f;	
	}


	if (glfwGetKey(binded_window, camera_keybinds[MOVE_FORWARD]) == GLFW_PRESS){
		auto vec = angle_to_vectors(cameraYrot - 90);
		cameraXvec += vec.x;	
		cameraZvec += vec.y;	
	}
	if (glfwGetKey(binded_window, camera_keybinds[MOVE_BACKWARD]) == GLFW_PRESS){
		auto vec = angle_to_vectors(cameraYrot - 90);
		cameraXvec -= vec.x;
		cameraZvec -= vec.y;	
	}
	if (glfwGetKey(binded_window, camera_keybinds[MOVE_LEFT]) == GLFW_PRESS){
		auto vec = angle_to_vectors(cameraYrot);
		cameraXvec -= vec.x;	
		cameraZvec -= vec.y;	
	}
	if (glfwGetKey(binded_window, camera_keybinds[MOVE_RIGHT]) == GLFW_PRESS){
		auto vec = angle_to_vectors(cameraYrot);
		cameraXvec += vec.x;
		cameraZvec += vec.y;	
	}

    auto temp = powf(cameraXvec, 2.0f) + powf(cameraYvec, 2.0f) + powf(cameraZvec, 2.0f);
    if (temp == 0) temp = 1.0f;
    auto magnitude = sqrtf(temp);
    cameraXvec /= magnitude;
    cameraYvec /= magnitude;
    cameraZvec /= magnitude;

    cameraX += (cameraXvec * cameraSpeed);
    cameraY += (cameraYvec * cameraSpeed);
    cameraZ += (cameraZvec * cameraSpeed);
}