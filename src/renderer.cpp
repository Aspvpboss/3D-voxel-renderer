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

	try{
		GLuint shader = glCreateShader(shader_type);
		std::string shaderString = readShaderFile(filePath).c_str();
		const char *shaderSrc = shaderString.c_str();
		glShaderSource(shader, 1, &shaderSrc, NULL);
		glCompileShader(shader);
		glAttachShader(rendering_program, shader);
	}
	catch(const std::exception& e){
		throw;
	}	

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

	GLuint active_program = renderingPrograms[0];

	glUseProgram(active_program);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
    return 0;
}