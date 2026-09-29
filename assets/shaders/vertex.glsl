#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texPos;
layout (location = 2) in vec3 normalVector;
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

out vec2 texCoord;
out vec3 fragPos;
out vec3 normalCoord;

void main(void) {
    fragPos = vec3(model_matrix * vec4(position, 1.0));
    texCoord = texPos;
    normalCoord = mat3(transpose(inverse(model_matrix))) * normalVector;
    //  gl_Position = vec4(position * 0.5, 1.0);   
    gl_Position = proj_matrix * view_matrix * model_matrix * vec4(position, 1.0);
}