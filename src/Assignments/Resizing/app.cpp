//
// Created by pbialas on 25.09.2020.
//

#include "app.h"

#include <iostream>
#include <vector>
#include <tuple>

#include "Application/utils.h"
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"
#include "glm/gtc/matrix_transform.hpp"

void SimpleShapeApplication::init()
{   
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
        -0.5f, 0.0f, -0.5f, 0.6f, 0.4f, 0.0f,
        0.5f, 0.0f, -0.5f, 0.6f, 0.4f, 0.0f,
        0.5f, 0.0f, 0.5f, 0.6f, 0.4f, 0.0f,
        -0.5f, 0.0f, 0.5f, 0.6f, 0.4f, 0.0f,

        //Wall1
        0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f,

        //Wall2
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f,

        //Wall3
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 1.0f,

        //Wall4
        0.0f, 1.0f, 0.0f, 0.9f, 1.0f, 0.0f,
        -0.5f, 0.0f, -0.5f, 0.9f, 1.0f, 0.0f,
        -0.5f, 0.0f, 0.5f, 0.9f, 1.0f, 0.0f,
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


    int w, h;
    std::tie(w, h) = frame_buffer_size();
    aspect_ = (float)w/h;
    fov_ = glm::pi<float>()/4.0;
    near_ = 0.1f;
    far_ = 100.0f;
    P_ = glm::perspective(fov_, aspect_, near_, far_);
    V_ = glm::lookAt(glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));

    // Generating the buffer and loading the vertex data into it.
    GLuint v_buffer_handle;
    glGenBuffers(1, &v_buffer_handle);
    OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle));
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint index_buffer_handle;
    glGenBuffers(1, &index_buffer_handle);
    OGL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_handle));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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

    // This setups a Vertex Array Object (VAO) that  encapsulates
    // the state of all vertex buffers needed for rendering
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);

    // This indicates that the data for attribute 0 should be read from a vertex buffer.
    glEnableVertexAttribArray(0);
    // and this specifies how the data is layout in the buffer.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid *>((3 * sizeof(GLfloat)))); // x,y,z,r,g,b offset 3*4byte

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_handle);
    glBindVertexArray(0);
    // end of vao "recording"

    // Setting the background color of the rendering window,
    // I suggest not to use white or black for better debuging.
    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);
    glUseProgram(program);
}

void SimpleShapeApplication::framebuffer_resize_callback(int w, int h) {
    Application::framebuffer_resize_callback(w, h);
    glViewport(0,0,w,h); 
    aspect_ = (float) w / h;
    P_ = glm::perspective(fov_, aspect_, near_, far_);
}

// This functions is called every frame and does the actual rendering.
void SimpleShapeApplication::frame()
{
    auto PVM = P_ * V_;
    glBindBuffer(GL_UNIFORM_BUFFER, u_pvm_buffer_);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &PVM[0]);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    // Binding the VAO will setup all the required vertex buffers.
    glBindVertexArray(vao_);
    //Enable the depth buffer algorithm
    glEnable(GL_DEPTH_TEST);
    //Enable the elimination of invisible walls
    glEnable(GL_CULL_FACE);;
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
}
