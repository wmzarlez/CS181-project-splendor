#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNorm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 side_color;

out vec3 normal;
out vec3 color;

void main() {
    gl_Position = projection * view * model * vec4(inPos, 1.0f);
    normal = inNorm;
    color  = side_color;
}
