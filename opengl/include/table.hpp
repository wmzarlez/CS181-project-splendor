#pragma once

#include <array>
#include <memory>
#include <assert.h>
#include "shader.hpp"
#include "textures.hpp"
#include "buffers.hpp"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "window_manager.hpp"


namespace OpenGL {
    class Table : public GameObject {
        public:
            static constexpr float half_x = 0.625;
            static constexpr float half_y = 0.52;
            static constexpr float half_h = 0.1;
            static constexpr float card_x = 135.f / 1000;
            static constexpr float card_y = 189.f / 1000;
            static constexpr float nobility_x = 135.f / 1000;
            static constexpr float nobility_y = 135.f / 1000;

        private:
            #pragma pack (1)
            struct Element {
                std::array<float, 3> pos;
                std::array<float, 3> n;
                std::array<float, 2> text_cord;
            };
            #pragma pack()
            constexpr static glm::vec3 table_left_bottom {-half_x, -half_y, half_h};

            constexpr static std::array<std::array<float, 3>, 8> pos = {
                std::array<float, 3>{-half_x, -half_y, -half_h}, 
                std::array<float, 3>{half_x, -half_y, -half_h}, 
                std::array<float, 3>{half_x, half_y, -half_h}, 
                std::array<float, 3>{-half_x, half_y, -half_h},
                std::array<float, 3>{-half_x, -half_y, half_h}, 
                std::array<float, 3>{half_x, -half_y, half_h}, 
                std::array<float, 3>{half_x, half_y, half_h}, 
                std::array<float, 3>{-half_x, half_y, half_h},
            };

            constexpr static std::array<float, 3> nx = {1,0,0};
            constexpr static std::array<float, 3> ny = {0,1,0};
            constexpr static std::array<float, 3> nz = {0,0,1};

            std::array<Element, 24>elements {
                //surface 1
                Element{.pos = pos[4], .n = nz, .text_cord = {0,0}}, 
                Element{.pos = pos[5], .n = nz, .text_cord = {1,0}}, 
                Element{.pos = pos[6], .n = nz, .text_cord = {1,1}}, 
                Element{.pos = pos[7], .n = nz, .text_cord = {0,1}},
                //surface 2
                Element{.pos = pos[0], .n = -ny, .text_cord = {-1,-1}}, 
                Element{.pos = pos[1], .n = -ny, .text_cord = {-1,-1}}, 
                Element{.pos = pos[5], .n = -ny, .text_cord = {-1,-1}}, 
                Element{.pos = pos[4], .n = -ny, .text_cord = {-1,-1}}, 
                //surface 3
                Element{.pos = pos[1], .n = nx, .text_cord = {-1,-1}}, 
                Element{.pos = pos[2], .n = nx, .text_cord = {-1,-1}}, 
                Element{.pos = pos[6], .n = nx, .text_cord = {-1,-1}}, 
                Element{.pos = pos[5], .n = nx, .text_cord = {-1,-1}}, 
                //surface 4
                Element{.pos = pos[2], .n = ny, .text_cord = {-1,-1}}, 
                Element{.pos = pos[3], .n = ny, .text_cord = {-1,-1}},
                Element{.pos = pos[7], .n = ny, .text_cord = {-1,-1}}, 
                Element{.pos = pos[6], .n = ny, .text_cord = {-1,-1}},
                //surface 5
                Element{.pos = pos[3], .n = -nx, .text_cord = {-1,-1}}, 
                Element{.pos = pos[0], .n = -nx, .text_cord = {-1,-1}}, 
                Element{.pos = pos[4], .n = -nx, .text_cord = {-1,-1}}, 
                Element{.pos = pos[7], .n = -nx, .text_cord = {-1,-1}}, 
                //surface 6
                Element{.pos = pos[0], .n = -nz, .text_cord = {-1,-1}}, 
                Element{.pos = pos[1], .n = -nz, .text_cord = {-1,-1}}, 
                Element{.pos = pos[2], .n = -nz, .text_cord = {-1,-1}}, 
                Element{.pos = pos[3], .n = -nz, .text_cord = {-1,-1}}
            };

            constexpr static std::array<unsigned int, 36> indices {
                0, 1, 2, 
                0, 3, 2, 
                4, 5, 6, 
                4, 6, 7,
                8, 9, 10, 
                8, 10, 11, 
                12, 13, 14, 
                12, 14, 15, 
                16, 17, 18, 
                16, 18, 19, 
                20, 21, 22, 
                20, 22, 23
            };

        std::shared_ptr<Shader_Program> _shader;
        std::shared_ptr<Texture2D>      _texture;
        VAO                             _vao;
        VBO<Element>                    _vbo;
        EBO<unsigned int>               _ebo;
    public:
        Table(std::shared_ptr<Shader_Program> shader) : 
            GameObject{1000, glm::vec3{1,1,1}, glm::mat3{1}, glm::vec3{0,0,0}}, 
            _shader{shader}, 
            _texture{std::make_shared<Texture2D>("../opengl/data/table.png")}, 
            _vao{}, _vbo{std::vector<Element>(std::begin(elements), std::end(elements))}, 
            _ebo{std::vector<unsigned int>(std::begin(indices), std::end(indices))} {
            _vao.bind();
            _vbo.bind();
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);
            _ebo.bind();
        }

        void update_shader() const {
            _shader->use();
            _shader->setVec3("objectColor", 0.31, 0.5, 1);
            _shader->setVec3("lightColor", Window::light_color);
            _shader->setVec3("viewPos", Window::camera.get_position());
            _shader->setVec3("lightPos", Window::light_pos);
            _shader->setMat4("projection", Window::camera.get_projection(Window::src_width, Window::src_height));
            _shader->setMat4("view", Window::camera.get_view_mat());
        }

        void draw() const override {
            _texture->bind(0);
            _shader->use();
            _shader->setMat4("model", get_model_mat4());
            _vao.bind();
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

        glm::vec3 get_card_global_position(unsigned int level, unsigned int col) {
            constexpr float x1 = 184.f / 1000;
            constexpr float y1 = 66.f / 1000;
            constexpr float x2 = 135.f / 1000;
            constexpr float y2 = 189.f / 1000;
            constexpr float x3 = 170.f / 1000;
            constexpr float y3 = 213.f / 1000;
            assert(level < 3);
            assert(col < 5);
            glm::vec3 local_cord = table_left_bottom + glm::vec3{x1 + col * x3 + x2 / 2, y1 + level * y3 + y2 / 2, 0};
            return _rotation * _scaling * local_cord + _translation;
        }

        glm::vec3 get_nobility_global_position(unsigned int idx) {
            constexpr float x1 = 270.f / 1000;
            constexpr float y1 = 710.f / 1000;
            constexpr float x2 = 135.f / 1000;
            constexpr float y2 = 135.f / 1000;
            constexpr float x3 = 150.f / 1000;
            assert(idx < 5);
            glm::vec3 local_cord = table_left_bottom + glm::vec3{x1 + idx * x3 + x2 / 2, y1 + y2 / 2, 0};
            return _rotation * _scaling * local_cord + _translation;
        }

        glm::vec3 get_coin_global_position(unsigned int idx) {
            constexpr float x1 = 1115.f / 1000;
            constexpr float y1 = 120.f / 1000;
            constexpr float y2 = 130.f / 1000;
            constexpr float y3 = 880.f / 1000;
            assert(idx < 6);
            glm::vec3 local_cord = table_left_bottom;
            if(idx == 5) {
                local_cord += glm::vec3{x1, y3, 0};
            } else {
                local_cord += glm::vec3{x1, y1 + idx * y2, 0};
            }
            return _rotation * _scaling * local_cord + _translation;
        }
    };
}