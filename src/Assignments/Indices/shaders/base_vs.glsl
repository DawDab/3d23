#version 410

layout(location = 0) in vec4 a_vertex_position; // Vertex position
layout(location = 1) in vec4 a_vertex_color;    // Vertex color
out vec4 color;                                 // Output color to fragment shader

void main() {
    gl_Position = a_vertex_position;
    color = a_vertex_color;
}