#version 410

layout(location = 0) out vec4 vFragColor;
in vec4 color; // Input color from vertex shader

void main() {
    vFragColor = color;
}