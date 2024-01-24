#pragma once

#include "shader.hpp"
#include "card_manager.hpp"
#include "movement.hpp"
#include "render_manager.hpp"
#include "table.hpp"
#include "window_manager.hpp"
#include "nobility_manager.hpp"
#include "coin_manager.hpp"
#include <array>
#include <list>
#include <mutex>
#include <algorithm>
#include <numeric>
#include <stop_token>

class Visualization{
    public:
        virtual void draw_card(int cardLevel, int cardIndex, int cardId) = 0;
        virtual void erase_card(int cardLevel, int cardIndex) = 0;
        virtual void draw_gem(int gemType) = 0;
        virtual void erase_gem(int gemType) = 0;
        virtual void draw_noble(int nobleIndex, int nobleId) = 0;
        virtual void erase_noble(int nobleIndex) = 0;
};

namespace OpenGL {
    
    class GameManager : public Visualization{
        private:
            std::array<std::array<unsigned int, 4>, 3> card_location_to_id;
            std::array<unsigned int, 5> nobility_location_to_id;
            std::array<unsigned int, 6> coin_num;
            std::shared_ptr<Shader_Program> shader;
            std::mutex mtx;

            std::shared_ptr<Table> table;
            std::shared_ptr<Card_Manager> card_manager;
            std::shared_ptr<Nobility_Manager> nobility_manager;
            std::shared_ptr<Coin_Manager> coin_manager;
            std::shared_ptr<Movement_Manager> movement_manager;
            std::shared_ptr<Render_Manager> render_manager;
        public:
            GameManager();

            void draw_card(int card_level, int card_index, int card_id) override {
                if(card_id == 0) {
                    return;
                }
                card_level -= 1;
                card_id -= 1;
                assert(card_location_to_id[card_level][card_index] == (unsigned int)(-1));
                auto card = card_manager->get_a_card(card_id, glm::vec3{0.27,0.27,0.27}, gen_y_negative(180)(1), table->get_card_global_position(card_level, 0));
                render_manager->add_game_object(card);
                const float now = glfwGetTime();
                movement_manager->add_movement(std::make_shared<Rotation>(card, now, .5, gen_y_negative(180.f)));
                movement_manager->add_movement(std::make_shared<Translation>(card, now, .5, gen_Bezier_path_2(table->get_card_global_position(card_level, 0), table->get_card_global_position(card_level, card_index), glm::vec3{0,0,1})));
                card_location_to_id[card_level][card_index] = card_id;
            }

            void erase_card(int card_level, int card_index) override {
                card_level -= 1;
                assert(card_location_to_id[card_level][card_index] != (unsigned int)(-1));
                render_manager->remove(card_location_to_id[card_level][card_index]);
                card_location_to_id[card_level][card_index] = (unsigned int)(-1);
            }

            void operator()() {
                while(!glfwWindowShouldClose(Window::window)) {
                    float currentFrame = static_cast<float>(glfwGetTime());
                    Window::delta_time = currentFrame - Window::last_frame;
                    Window::last_frame = currentFrame;
                    Window::process_input(Window::window);
                    movement_manager->update(currentFrame);
                    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    card_manager->update_shader();
                    table->update_shader();
                    mtx.lock();
                    render_manager->render();
                    mtx.unlock();
                }
                glfwTerminate();
            }
    };

    GameManager::GameManager() : coin_num {200, 210, 220, 230, 240, 250} {
        Window::window_initialize();
        shader = std::make_shared<Shader_Program>();
        {
            Shader<Vertex_Shader>   vs {"../opengl/shader/2.2.basic_lighting.vs", File{}};
            Shader<Fragment_Shader> fs {"../opengl/shader/2.2.basic_lighting.fs", File{}};
            shader->init(vs, fs);
        }
        shader->use();
        shader->set_int("texture1", 0);
        table = std::make_shared<Table>(shader);
        card_manager = std::make_shared<Card_Manager>(shader);
        nobility_manager = std::make_shared<Nobility_Manager>(shader);
        coin_manager = std::make_shared<Coin_Manager>(shader);
        movement_manager = std::make_shared<Movement_Manager>();
        render_manager = std::make_shared<Render_Manager>();
        for(auto& i : card_location_to_id) {
            std::fill(i.begin(), i.end(), -1);
        }
        std::fill(nobility_location_to_id.begin(), nobility_location_to_id.end(), -1);
    }
}


