//
// Created by Piotr Białas on 02/11/2021.
//

#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>
#include "Application/utils.h"

namespace xe {
    GLuint create_texture(const std::string &name);
    class Material {
    public:
        virtual void bind() = 0;

        virtual void unbind() {};
    };

    class ColorMaterial : public Material {
    public:
        ColorMaterial(const glm::vec4 color, GLuint texture, GLuint texture_unit) : color_(color), texture_(texture), texture_unit_(texture_unit) {}
        ColorMaterial(const glm::vec4 color, GLuint texture) : ColorMaterial(color, texture, 0) {}
        ColorMaterial(const glm::vec4 color) : ColorMaterial(color, 0) {}
        
        void bind();

        static void init();
        
        static GLuint program() { return shader_; }

        GLuint getTexture() const { return texture_; }
        void setTexture(GLuint texture) { texture_ = texture; }

        GLuint getTextureUnit() const { return texture_unit_; }
        void setTextureUnit(GLuint textureUnit) { texture_unit_ = textureUnit; }    

    private:
        static GLuint shader_;
        static GLuint color_uniform_buffer_;
        static GLint uniform_map_Kd_location_;
        GLuint texture_;
        GLuint texture_unit_;

        glm::vec4 color_;

    };


}


