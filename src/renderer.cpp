#include "renderer.hpp"
#include <fstream>
#include <iostream>
#include <string>

std::string readShaderFile(const char *filePath) 
{
	std::string content;

	std::ifstream fileStream(filePath, std::ios::in);
	if (!fileStream.is_open())
	{
		throw "Unable to open file.";
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



Renderer::Renderer(){

    const char *files[] = {"test.glsl", "fragment.glsl"};
	std::cout << readShaderFile(files[0]) << std::endl;	

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