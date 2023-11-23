#version 410

layout(location = 0) out vec4 vFragColor;
layout(location = 1) in vec4 color; // Input color from vertex shader

void main() {
    vFragColor = color;
}