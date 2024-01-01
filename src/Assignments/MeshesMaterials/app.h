//
// Created by pbialas on 05.08.2020.
//

#pragma once

#include <vector>

#include "Application/application.h"
#include "Application/utils.h"

#include "glad/gl.h"
#include "glm/glm.hpp"
#include "camera.h"
#include "camera_controler.h"
#include "Engine/Mesh.h"
#include "Engine/Material.h"

class SimpleShapeApplication : public xe::Application
{
public: 
    SimpleShapeApplication(int width, int height, std::string title, bool debug) : Application(width, height, title, debug) {}
    ~SimpleShapeApplication() {
        if (camera_) {
            delete camera_;
        }
    }

    void init() override;
    void frame() override;
    void framebuffer_resize_callback(int w, int h) override;
    void mouse_button_callback(int button, int action, int mods) override;
    void cursor_position_callback(double x, double y) override;
    void set_camera(Camera *camera) { camera_ = camera; }
    void set_controler(CameraControler *controler) { controler_ = controler; }
    Camera *camera() { return camera_; }
    void scroll_callback(double xoffset, double yoffset) override {
         Application::scroll_callback(xoffset, yoffset);   
         camera()->zoom(yoffset / 30.0f);
    }
    void add_submesh(xe::Mesh *mesh) {
        meshes_.push_back(mesh);
    }

private:
    GLuint vao_;
    GLuint u_pvm_buffer_;
    Camera *camera_;
    CameraControler *controler_;
    std::vector<xe::Mesh*> meshes_; 
};