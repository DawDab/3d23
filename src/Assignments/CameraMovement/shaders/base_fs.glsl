#version 420

layout(location = 0) out vec4 vFragColor;
in vec4 color; // Input color from vertex shader
layout(std140, binding = 0) uniform Modifier {
    float strength;
    vec3  color_mod;
};

void main() {
    vFragColor = vec4(color[0] * color_mod[0] * strength, color[1] * color_mod[1] * strength,  color[2] * color_mod[2] * strength, 1.0);
}