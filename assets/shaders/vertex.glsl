#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texPos;
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

out vec2 tc;

void main(void) {
    gl_Position = proj_matrix * view_matrix * view_matrix * vec4(position, 1.0);
    tc = texPos;
}