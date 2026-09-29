#include <SOIL2/SOIL2.h>
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

const static float VOXEL_UVS[] = {
    // Face 1 (Back)
    0.0f, 1.0f,  0.0f, 0.0f,  1.0f, 0.0f,
    1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,

    // Face 2 (Right)
    1.0f, 0.0f,  0.0f, 0.0f,  1.0f, 1.0f,
    0.0f, 0.0f,  0.0f, 1.0f,  1.0f, 1.0f,

    // Face 3 (Front)
    1.0f, 0.0f,  0.0f, 0.0f,  1.0f, 1.0f,
    0.0f, 0.0f,  0.0f, 1.0f,  1.0f, 1.0f,

    // Face 4 (Left)
    1.0f, 0.0f,  0.0f, 0.0f,  1.0f, 1.0f,
    0.0f, 0.0f,  0.0f, 1.0f,  1.0f, 1.0f,

    // Face 5 (Bottom)
    0.0f, 1.0f,  1.0f, 1.0f,  1.0f, 0.0f,
    1.0f, 0.0f,  0.0f, 0.0f,  0.0f, 1.0f,

    // Face 6 (Top)
    0.0f, 1.0f,  1.0f, 1.0f,  1.0f, 0.0f,
    1.0f, 0.0f,  0.0f, 0.0f,  0.0f, 1.0f
};


vec3 cubeLoc(3.0f, -2.0f, -8.0f);
GLuint cubeTex;

GLuint loadTexture(const char *textImagePath){

	GLuint textureID;
	textureID = SOIL_load_OGL_texture(textImagePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if(textureID == 0) throw std::runtime_error(std::format("Tried to open the texture {} but failed", textImagePath));
	// Bind it once to configure it
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // Set parameters and generate mipmaps HERE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 	
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	if(glewIsSupported("GL_EXT_texture_filter_anisotropic")){
		GLfloat anisoSetting = 0.0f;	
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoSetting);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoSetting);
	}
	
	return textureID;
}

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
		cubeTex = loadTexture("assets/textures/dirt.jpg");
	}	
	catch(const std::exception& e){
		throw;
	}

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(NUM_VBOS, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VOXEL_VERTEXES), VOXEL_VERTEXES, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VOXEL_UVS), VOXEL_UVS, GL_STATIC_DRAW);

}


Renderer::~Renderer(){
	for(GLuint program: renderingPrograms){
		if(program) glDeleteProgram(program);
	}
	glDeleteVertexArrays(1, vao);
	glDeleteBuffers(NUM_VBOS, vbo);
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

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cubeTex);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
    return 0;
}

