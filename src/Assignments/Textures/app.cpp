//
// Created by pbialas on 25.09.2020.
//

#include "app.h"

#include <iostream>
#include <vector>
#include <tuple>

#include "Engine/mesh_loader.h"
#include "Application/utils.h"
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"
#include "glm/gtc/matrix_transform.hpp"

void SimpleShapeApplication::init()
{   
    xe::ColorMaterial::init();
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

    // A vector containing the x,y,z vertex coordinates for the triangle.
    std::vector<GLfloat> vertices = {
        //Base
        -0.5f, 0.0f, -0.5f, 0.5f, 0.1910f,
        0.5f, 0.0f, -0.5f, 0.8090f, 0.5f,
        0.5f, 0.0f, 0.5f, 0.5f, 0.8090f,
        -0.5f, 0.0f, 0.5f, 0.1910f, 0.5f,

        //Wall1
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.0f, 0.5f, 0.1910f, 0.5f,
        0.5f, 0.0f, 0.5f, 0.5f, 0.8090f,

        //Wall2
        0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.0f, 0.5f, 0.5f, 0.8090f,
        0.5f, 0.0f, -0.5f, 0.8090f, 0.5f,

        //Wall3
        0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.0f, -0.5f, 0.8090f, 0.5f,
        -0.5f, 0.0f, -0.5f, 0.5f, 0.1910f,

        //Wall4
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.0f, -0.5f, 0.5f, 0.1910f,
        -0.5f, 0.0f, 0.5f, 0.1910f, 0.5f,
    };

    std::vector<GLushort> indices = {
        0, 1, 2, 
        0, 2, 3,
        4, 5, 6,
        7, 8, 9,
        10, 11, 12,
        13, 14, 15
        };

    float strength = 1.0f;
    float color[3] = {1.0f, 1.0f, 1.0f};

    set_camera(new Camera);
    set_controler(new CameraControler(camera()));
    auto[w, h] = frame_buffer_size();
    camera_->perspective(glm::pi<float>()/4.0, (float)w / h, 0.1f, 100.0f);
    camera_->look_at(glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    auto pyramid = xe::load_mesh_from_obj(std::string(ROOT_DIR) + "/Models/blue_marble.obj",
                                          std::string(ROOT_DIR) + "/Models");
    add_submesh(pyramid);

    GLuint uniform_buffer_handle;
    glGenBuffers(1, &uniform_buffer_handle);
    glBindBuffer(GL_UNIFORM_BUFFER, uniform_buffer_handle);
    glBufferData(GL_UNIFORM_BUFFER, 8 * sizeof(float), nullptr, GL_STATIC_DRAW);         // base alignment  // aligned offset
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(strength), &strength);                  // 4               // 0
    glBufferSubData(GL_UNIFORM_BUFFER, 4 * sizeof(float), 3 * sizeof(float), &color);    // 16              // 16
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniform_buffer_handle);                       // needed mem 32
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glGenBuffers(1, &u_pvm_buffer_);
    glBindBuffer(GL_UNIFORM_BUFFER, u_pvm_buffer_);
    glBufferData(GL_UNIFORM_BUFFER, 16 * sizeof(float), nullptr, GL_STATIC_DRAW);         
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, u_pvm_buffer_);                
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // Setting the background color of the rendering window,
    // I suggest not to use white or black for better debuging.
    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);
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
    glBindBuffer(GL_UNIFORM_BUFFER, u_pvm_buffer_);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &PVM[0]);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    //Enable the depth buffer algorithm
    glEnable(GL_DEPTH_TEST);
    //Enable the elimination of invisible walls
    glEnable(GL_CULL_FACE);;
    glBindVertexArray(0);
}
