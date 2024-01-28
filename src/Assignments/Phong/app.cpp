//
// Created by pbialas on 25.09.2020.
//

#include "app.h"

#include <iostream>
#include <vector>
#include <tuple>

#include "Engine/mesh_loader.h"
#include "Engine/Light.h"
#include "Application/utils.h"
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"
#include "glm/gtc/matrix_transform.hpp"

void SimpleShapeApplication::init()
{   
    xe::PhongMaterial::init();
    // A utility function that reads the shader sources, compiles them and creates the program object
    // As everything in OpenGL we reference program by an integer "handle".
    auto program = xe::utils::create_program(
        {{GL_VERTEX_SHADER, std::string(PROJECT_DIR) + "/shaders/base_vs.glsl"},
         {GL_FRAGMENT_SHADER, std::string(PROJECT_DIR) + "/shaders/base_fs.glsl"}});

    if (!program)
    {
        std::cerr << "Invalid program" << std::endl;
        exit(-1);
    }

    set_camera(new Camera);
    set_controler(new CameraControler(camera()));
    auto[w, h] = frame_buffer_size();
    camera_->perspective(glm::pi<float>()/4.0, (float)w / h, 0.1f, 100.0f);
    camera_->look_at(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    add_ambient(glm::vec3(0.25, 0.25, 0.25));
    add_light(xe::PointLight{{ 0.0, 0.0, 1.0 }, {1.0, 1.0, 1.0}, 1.0, 0.1});
    add_light(xe::PointLight{{ 1.0, 0.0, 1.0 }, {0.0, 0.5, 0.5}, 1.0, 0.1});
    add_light(xe::PointLight{{ -1.0, 0.0, 1.0 }, {1.0, 0.0, 0.0}, 1.0, 0.1});
    auto square = xe::load_mesh_from_obj(std::string(ROOT_DIR) + "/Models/square.obj",
                                          std::string(ROOT_DIR) + "/Models");
    add_submesh(square);

    glGenBuffers(1, &u_pvm_buffer_);
    glBindBuffer(GL_UNIFORM_BUFFER, u_pvm_buffer_);      
    glBufferData(GL_UNIFORM_BUFFER, 2* sizeof(glm::mat4) + sizeof(glm::mat3), nullptr, GL_STATIC_DRAW);   
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, u_pvm_buffer_);                
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glGenBuffers(1, &u_light_buffer_);
    glBindBuffer(GL_UNIFORM_BUFFER, u_light_buffer_);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::vec3)+sizeof(GLuint)+ sizeof(p_lights_[0])*p_lights_.size(), nullptr, GL_STATIC_DRAW);  
    glBindBufferBase(GL_UNIFORM_BUFFER, 2, u_light_buffer_);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // Setting the background color of the rendering window,
    // I suggest not to use white or black for better debuging.
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glUseProgram(program);
}

void SimpleShapeApplication::mouse_button_callback(int button, int action, int mods) {
    Application::mouse_button_callback(button, action, mods);

    if (controler_) {
        double x, y;
        glfwGetCursorPos(window_, &x, &y);

        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
            controler_->LMB_pressed(x, y);

        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
            controler_->LMB_released(x, y);
    }

}

void SimpleShapeApplication::cursor_position_callback(double x, double y) {
    Application::cursor_position_callback(x, y);
    if (controler_) {
        controler_->mouse_moved(x, y);
    }
}

void SimpleShapeApplication::framebuffer_resize_callback(int w, int h) {
    Application::framebuffer_resize_callback(w, h);
    glViewport(0,0,w,h);
    camera_->set_aspect((float)w / h);
}

// This functions is called every frame and does the actual rendering.
void SimpleShapeApplication::frame()
{   
    for (auto m: meshes_){
        m->draw();
    }
    auto PVM = camera_->projection() * camera_->view();
    glm::mat4 M = glm::mat4(1.0f);
    auto VM = camera_->view() * M;
    auto R = glm::mat3(VM);
    auto N = glm::mat3(glm::cross(R[1], R[2]), glm::cross(R[2], R[0]), glm::cross(R[0], R[1]));
    glBindBuffer(GL_UNIFORM_BUFFER, u_pvm_buffer_);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(PVM), &PVM[0]);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(PVM), sizeof(VM), &VM);
    glBufferSubData(GL_UNIFORM_BUFFER, 2*sizeof(glm::mat4), sizeof(N[0]), &N[0]);
    glBufferSubData(GL_UNIFORM_BUFFER, 2*sizeof(glm::mat4) + sizeof(N[0]), sizeof(N[1]), &N[1]);
    glBufferSubData(GL_UNIFORM_BUFFER, 2*sizeof(glm::mat4) + sizeof(N[0]) + sizeof(N[1]), sizeof(N[2]), &N[2]);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    GLuint n_p_lights = p_lights_.size();
    glBindBuffer(GL_UNIFORM_BUFFER, u_light_buffer_);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec3), &ambient_);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec3), sizeof(GLuint),&n_p_lights);
    //light loading loop
    for (int i =0 ; i < n_p_lights;i++){
        //transform light from world space to the view space
        p_lights_[i].position_in_vs = glm::vec3(camera_->view() * glm::vec4(p_lights_[i].position_in_ws, 1.0f));
        GLuint offset = sizeof(glm::vec3) + sizeof(GLuint) + i * sizeof(xe::PointLight);
        glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(xe::PointLight), &p_lights_[i]);
    }

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    //Enable the depth buffer algorithm
    glEnable(GL_DEPTH_TEST);
    //Enable the elimination of invisible walls
    // glEnable(GL_CULL_FACE);
    glBindVertexArray(0);
}
