#version 330 core

in vec3 normal;
in vec3 color;

out vec3 FragColor;

void main() {
    FragColor = color;
}