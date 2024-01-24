
#include "shader.hpp"
#include "card_manager.hpp"
#include "movement.hpp"
#include "render_manager.hpp"
#include "table.hpp"
#include "window_manager.hpp"
#include "nobility_manager.hpp"
#include "coin_manager.hpp"


using namespace OpenGL;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    OpenGL::Window::window_initialize();
    std::shared_ptr<Shader_Program> shader = std::make_shared<Shader_Program>();
    {
        Shader<Vertex_Shader>   vs {"../opengl/shader/2.2.basic_lighting.vs", File{}};
        Shader<Fragment_Shader> fs {"../opengl/shader/2.2.basic_lighting.fs", File{}};
        shader->init(vs, fs);
    }
    shader->use();
    shader->set_int("texture1", 0);
    std::shared_ptr<Table> table = std::make_shared<Table>(shader);
    Card_Manager card_manager{shader};
    Nobility_Manager nobility_manager{shader};
    Coin_Manager coin_manager{shader};
    Movement_Manager move_manager {};
    Render_Manager render_manager {};
    auto card0 = card_manager.get_a_card(0, glm::vec3{0.27,0.27,0.27}, gen_y_negative(180)(1), table->get_card_global_position(0, 0));
    auto card1 = card_manager.get_a_card(1, glm::vec3{0.27,0.27,0.27}, gen_y_negative(180)(1), table->get_card_global_position(0, 0));
    auto card2 = card_manager.get_a_card(2, glm::vec3{0.27,0.27,0.27}, gen_y_negative(180)(1), table->get_card_global_position(0, 0));
    auto card3 = card_manager.get_a_card(3, glm::vec3{0.27,0.27,0.27}, gen_y_negative(180)(1), table->get_card_global_position(0, 0));
    auto nobility0 = nobility_manager.get_a_nobility(100, glm::vec3{0.27,0.27,0.27}, glm::mat3{1}, table->get_nobility_global_position(0));
    auto coin = coin_manager.get_a_coin(210, glm::vec3{0.05, 0.05, 0.05}, glm::mat3{1}, table->get_coin_global_position(0));
    render_manager.add_game_object(card0);
    render_manager.add_game_object(card1);
    render_manager.add_game_object(card2);
    render_manager.add_game_object(card3);
    render_manager.add_game_object(table);
    render_manager.add_game_object(nobility0);
    render_manager.add_game_object(coin);
    const float now = glfwGetTime();
    move_manager.add_movement(std::make_shared<Rotation>(card0, now, .5, gen_y_negative(180.f)));
    move_manager.add_movement(std::make_shared<Translation>(card0, now, .5, gen_Bezier_path_2(table->get_card_global_position(0, 0), table->get_card_global_position(0, 1), glm::vec3{0,0,1})));
    move_manager.add_movement(std::make_shared<Rotation>(card1, now, 0.5, gen_y_negative(180.f)));
    move_manager.add_movement(std::make_shared<Translation>(card1, now, 0.5, gen_Bezier_path_2(table->get_card_global_position(0, 0), table->get_card_global_position(0, 2), glm::vec3{0,0,1})));
    move_manager.add_movement(std::make_shared<Rotation>(card2, now, 0.5, gen_y_negative(180.f)));
    move_manager.add_movement(std::make_shared<Translation>(card2, now, 0.5, gen_Bezier_path_2(table->get_card_global_position(0, 0), table->get_card_global_position(0, 3), glm::vec3{0,0,1})));
    move_manager.add_movement(std::make_shared<Rotation>(card3, now, .5, gen_y_negative(180.f)));
    move_manager.add_movement(std::make_shared<Translation>(card3, now, .5, gen_Bezier_path_2(table->get_card_global_position(0, 0), table->get_card_global_position(0, 4), glm::vec3{0,0,1})));
    // render loop
    // -----------
    while (!glfwWindowShouldClose(OpenGL::Window::window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        OpenGL::Window::delta_time = currentFrame -  OpenGL::Window::last_frame;
        OpenGL::Window::last_frame = currentFrame;

        // input
        // -----
        OpenGL::Window::process_input(OpenGL::Window::window);
        move_manager.update(currentFrame);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        card_manager.update_shader();
        table->update_shader();
        render_manager.render();

        glfwSwapBuffers(OpenGL::Window::window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

