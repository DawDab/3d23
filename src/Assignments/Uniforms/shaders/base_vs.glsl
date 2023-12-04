#version 420

layout(location = 0) in vec4 a_vertex_position; // Vertex position
layout(location = 1) in vec4 a_vertex_color;    // Vertex color
out vec4 color;                                 // Output color to fragment shader
layout(std140, binding=1) uniform Transformations {
    vec2 scale;
    vec2 translation;
    mat2 rotation;
};

void main() {
    gl_Position = a_vertex_position;
    color = a_vertex_color;
    gl_Position.xy = rotation*(scale*a_vertex_position.xy)+translation;
    //It's recommended to start with scaling, then do rotations, and finally translations when you're putting matrices together. 
    //If you do it in a different order, the transformations might not work well together.
    //If you first perform a translation and then scale, the translation vector will also be subject to scaling!
    gl_Position.zw = a_vertex_position.zw;  
}