#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <format>
#include "renderer.hpp"

const static float VOXEL_VERTEXES[] ={
	-1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f, 1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f,
	1.0f, -1.0f, -1.0f, 1.0f, -1.0f,  1.0f, 1.0f,  1.0f, -1.0f,
	1.0f, -1.0f,  1.0f, 1.0f,  1.0f,  1.0f, 1.0f,  1.0f, -1.0f,
	1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f, 1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f, 1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f, 1.0f,  1.0f, -1.0f, 1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f
};

vec3 cubeLoc(3.0f, -2.0f, -8.0f);

std::string readShaderFile(const char *filePath){

	std::string content;

	std::ifstream fileStream(filePath, std::ios::in);
	if (!fileStream.is_open()){
		throw std::runtime_error(std::format("Tried to open the shader {} but failed", filePath));
	}
	std::string line = "";
	while (!fileStream.eof()) 
	{
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}


void compileShader(GLuint rendering_program, GLenum shader_type, const char *filePath){

	GLuint shader;
	try{
		shader = glCreateShader(shader_type);
		std::string shaderString = readShaderFile(filePath).c_str();
		const char *shaderSrc = shaderString.c_str();
		glShaderSource(shader, 1, &shaderSrc, NULL);
		glCompileShader(shader);
	}
	catch(const std::exception& e) {
		throw;
	}
	GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled != GL_TRUE) {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(shader, 1024, &log_length, message);
        std::cerr << "Shader compilation failed for " << filePath << ":\n" << message << std::endl;
        throw std::runtime_error("Shader compilation failed");
    }

    glAttachShader(rendering_program, shader);
    
    // Once attached, you can safely delete the individual shader object
    glDeleteShader(shader);

}


Renderer::Renderer(){

	renderingPrograms[0] = glCreateProgram();
	try{
		compileShader(renderingPrograms[0], GL_FRAGMENT_SHADER, "assets/shaders/frag.glsl");
		compileShader(renderingPrograms[0], GL_VERTEX_SHADER, "assets/shaders/vertex.glsl");
		glLinkProgram(renderingPrograms[0]);
	}	
	catch(const std::exception& e){
		throw;
	}


	glGenVertexArrays(NUM_VAOS, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(NUM_VBOS, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VOXEL_VERTEXES), VOXEL_VERTEXES, GL_STATIC_DRAW);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// glEnableVertexAttribArray(0);

}


Renderer::~Renderer(){
	for(GLuint program: renderingPrograms){
		if(program) glDeleteProgram(program);
	}
}

int Renderer::bindWindow(GLFWwindow *window_to_bind){
    if(!window_to_bind || window) return 1;
    window = window_to_bind; 

    return 0;
}

int Renderer::render(const std::unique_ptr<Camera>& camera){
    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingPrograms[0]);

	pMatloc = glGetUniformLocation(renderingPrograms[0], "proj_matrix");
	mMatloc = glGetUniformLocation(renderingPrograms[0], "mv_matrix");

	mat4 pMat = camera->getPerspectiveMatrix();
	mat4 cMat = camera->buildCameraMatrix();

	mat4 mMat = cMat * math::translate(mat4(1.0f), cubeLoc);

	glUniformMatrix4fv(pMatloc, 1, GL_FALSE, &pMat.data[0]);
	glUniformMatrix4fv(mMatloc, 1, GL_FALSE, &mMat.data[0]);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
    return 0;
}

