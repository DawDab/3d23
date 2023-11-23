#version 410

layout(location = 0) in vec4 a_vertex_position; // Vertex position
layout(location = 1) in vec4 a_vertex_color;    // Vertex color
layout(location = 1) out vec4 fragColor;        // Output color to fragment shader

void main() {
    gl_Position = a_vertex_position;
    fragColor = a_vertex_color;
}