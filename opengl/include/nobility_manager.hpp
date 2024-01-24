#pragma once

#include <array>
#include <memory>
#include "shader.hpp"
#include "textures.hpp"
#include "buffers.hpp"
#include "glad/glad.h"
#include "game_object.hpp"
#include "window_manager.hpp"
#include "utils.hpp"

namespace OpenGL {
    class Nobility_Manager {
        public:
            constexpr static float half_h = 0.02;
            constexpr static float half_x = 0.25;
            constexpr static float half_y = 0.25;
        private:
            #pragma pack (1)
            struct Element {
                std::array<float, 3> pos;
                std::array<float, 3> n;
                std::array<float, 2> text_cord;
            };
            #pragma pack ()


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

            static std::array<Element, 24> elements;
            constexpr static std::array<unsigned int, 36> indices {
                0, 1, 2, 
                0, 2, 3, 
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

            static void set_texcord(unsigned int id, std::array<Element, 24>& surfaces);

            std::shared_ptr<Shader_Program> _shader;
            std::shared_ptr<Texture2D> _texture;

            class Nobility : public GameObject {
                private:
                    std::shared_ptr<Shader_Program> _shader;
                    std::shared_ptr<Texture2D>      _texture;
                    VAO                             _vao;
                    VBO<Element>                    _vbo;
                    EBO<unsigned int>               _ebo;
                public:
                    Nobility(unsigned int id, glm::vec3 scale, glm::mat3 rot, glm::vec3 trans, 
                        std::shared_ptr<Shader_Program> shader, std::shared_ptr<Texture2D> texture, 
                        std::array<Element, 24>& elements, const std::array<unsigned int, 36>& indices) : 
                        GameObject{id, scale, rot, trans}, _shader{shader}, _texture{texture}, _vao{}, _vbo{}, _ebo{} {
                            set_texcord(_id, elements);
                            _vbo.set_data(std::vector<Element>(std::begin(elements), std::end(elements)));
                            _ebo.set_data(std::vector<unsigned int>(std::begin(indices), std::end(indices)));
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

                    void draw() const override {
                        _texture->bind(0);
                        _shader->use();
                        _shader->setMat4("model", get_model_mat4());
                        _vao.bind();
                        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                    }
            };

        public:
            Nobility_Manager(std::shared_ptr<Shader_Program> shader);

            std::shared_ptr<GameObject> get_a_nobility(unsigned int id, 
                glm::vec3 scaling, 
                glm::mat3 rot,
                glm::vec3 trans
            ) {
                assert(id >= 100 && id < 110);
                return std::make_shared<Nobility>(id, std::move(scaling), std::move(rot), std::move(trans), _shader, _texture, elements, indices);
            }

            void update_shader() const {
                _shader->use();
                _shader->setVec3("objectColor", 1, 0.5, 0.31);
                _shader->setVec3("lightColor", Window::light_color);
                _shader->setVec3("viewPos", Window::camera.get_position());
                _shader->setVec3("lightPos", Window::light_pos);
                _shader->setMat4("projection", Window::camera.get_projection(Window::src_width, Window::src_height));
                _shader->setMat4("view", Window::camera.get_view_mat());
            }
    };

    std::array<Nobility_Manager::Element, 24> Nobility_Manager::elements {
        //surface 1
        Element{.pos = pos[4], .n = nz, .text_cord = {-1,-1}}, 
        Element{.pos = pos[5], .n = nz, .text_cord = {-1,-1}}, 
        Element{.pos = pos[6], .n = nz, .text_cord = {-1,-1}}, 
        Element{.pos = pos[7], .n = nz, .text_cord = {-1,-1}},
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

    void Nobility_Manager::set_texcord(unsigned int id, std::array<Element, 24>& surfaces) {
        //# of cards in one line
        constexpr float h_normalize = 1.f / 11;
        assert(id >= 100 && id < 110);
        unsigned int r = id % 10;
        const float y_high_normalize = 1.0 - r * h_normalize;
        const float y_low_normalize = y_high_normalize - h_normalize;


        //front
        // 1 - 0
        // |   |
        // 3 - 2
        surfaces[0].text_cord[0] = 0;
        surfaces[0].text_cord[1] = y_low_normalize;
        surfaces[1].text_cord[0] = 1;
        surfaces[1].text_cord[1] = y_low_normalize;
        surfaces[2].text_cord[0] = 1;
        surfaces[2].text_cord[1] = y_high_normalize;
        surfaces[3].text_cord[0] = 0;
        surfaces[3].text_cord[1] = y_high_normalize;

        surfaces[20].text_cord[0] = 1;
        surfaces[20].text_cord[1] = 0;
        surfaces[21].text_cord[0] = 0;
        surfaces[21].text_cord[1] = 0;
        surfaces[22].text_cord[0] = 0;
        surfaces[22].text_cord[1] = h_normalize;
        surfaces[23].text_cord[0] = 1;
        surfaces[23].text_cord[1] = h_normalize;
    }

    Nobility_Manager::Nobility_Manager(std::shared_ptr<Shader_Program> shader) : 
        _shader{shader} {
        _texture = std::make_shared<Texture2D>("../opengl/data/nobility.png");
    }
}