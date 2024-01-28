#version 420

const int MAX_POINT_LIGHTS=24;

struct PointLight {
    vec3 position_in_world_space; 
    vec3 position_in_view_space;    
    vec3 color;
    float intensity;
    float radius;
};
layout(location=0) out vec4 vFragColor;

layout(std140, binding=0) uniform Material {
    vec4  Ka;
    vec4  Kd;
    vec4  Ks;
    float Ns;
    bool use_map_Kd;
};

layout(std140, binding=2) uniform Lights {
    vec3 ambient;
    uint n_p_lights;
    PointLight p_light[MAX_POINT_LIGHTS];
};  

in vec2 vertex_texcoords;
in vec3 vertex_normals_in_vs;
in vec3 vertex_coords_in_vs;

uniform sampler2D map_Kd;

void main() {
    if (use_map_Kd)
        vFragColor = Kd*texture(map_Kd, vertex_texcoords);
    else
        vFragColor = Kd;
    
    vec3 normal = normalize(vertex_normals_in_vs);
    //Fix back face
    if (gl_FrontFacing) {
    normal = -normal;
    }
    vec3 diffuse;
    vec3 specular;
    for(int i = 0; i<n_p_lights; i++){
        //Diffuse lighting
        vec3 lightDirection = normalize(p_light[i].position_in_view_space - vertex_coords_in_vs);
        float diffuseFactor = max(dot(normal, lightDirection), 0.0f);
        diffuse = diffuse + diffuseFactor * p_light[i].color;
    
        //Specular lighting
        vec3 viewDirection =normalize(-vertex_coords_in_vs);
        vec3 relfectDirection = reflect(-lightDirection, normal);
        float specularFactor = pow(max(dot(viewDirection,relfectDirection),0.0f),Ns);
        specular = specular + specularFactor * Ks.rgb;
    }
    //Final color
    vFragColor.a = Kd.a; 
    vFragColor.rgb = Kd.rgb * (ambient + diffuse + specular);
    
}