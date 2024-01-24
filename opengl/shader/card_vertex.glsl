#version 330 core

layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_texture_cord;

out vec2 textCord;
out vec3 normal;
out vec3 frag_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 project;

void main() {
    if(abs(in_normal.z) > 0.9) {
        textCord = in_texture_cord;
    } else {
        textCord = vec2(-1, -1);
    }
    normal = mat3(transpose(inverse(model))) * in_normal;
    frag_pos = vec3(model * vec4(in_pos, 1.0));
    gl_Position = project * view * vec4(frag_pos, 1.0f);
}