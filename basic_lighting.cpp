#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <array>
#include <memory>
#include "window_manager.hpp"
#include "shader.hpp"
#include "textures.hpp"

#pragma pack (1)
struct Card_Element {
    std::array<float, 3> pos;
    std::array<float, 3> n;
    std::array<float, 2> text_cord;
};
#pragma pack ()

constexpr float half_h = 0.02;
constexpr float half_x = 0.25;
constexpr float half_y = 0.35;

constexpr std::array<std::array<float, 3>, 8> pos = {
    std::array<float, 3>{-half_x, -half_y, -half_h}, 
    std::array<float, 3>{half_x, -half_y, -half_h}, 
    std::array<float, 3>{half_x, half_y, -half_h}, 
    std::array<float, 3>{-half_x, half_y, -half_h},
    std::array<float, 3>{-half_x, -half_y, half_h}, 
    std::array<float, 3>{half_x, -half_y, half_h}, 
    std::array<float, 3>{half_x, half_y, half_h}, 
    std::array<float, 3>{-half_x, half_y, half_h},
};

constexpr std::array<float, 3> nx = {1,0,0};
constexpr std::array<float, 3> ny = {0,1,0};
constexpr std::array<float, 3> nz = {0,0,1};



std::array<Card_Element, 24> elements {
    //surface 1
    Card_Element{.pos = pos[4], .n = nz, .text_cord = {-1,-1}}, 
    Card_Element{.pos = pos[5], .n = nz, .text_cord = {-1,-1}}, 
    Card_Element{.pos = pos[6], .n = nz, .text_cord = {-1,-1}}, 
    Card_Element{.pos = pos[7], .n = nz, .text_cord = {-1,-1}},
    //surface 2
    Card_Element{.pos = pos[0], .n = -ny, .text_cord = {-1,-1}}, 
    Card_Element{.pos = pos[1], .n = -ny, .text_cord = {-1,-1}}, 
    Card_Element{.pos = pos[5], .n = -ny, .text_cord = {-1,-1}}, 
    Card_Element{.pos = pos[4], .n = -ny, .text_cord = {-1,-1}}, 
    //surface 3
    Card_Element{.pos = pos[1], .n = nx, .text_cord = {-1,-1}}, 
    Card_Element{.pos = pos[2], .n = nx, .text_cord = {-1,-1}}, 
    Card_Element{.pos = pos[6], .n = nx, .text_cord = {-1,-1}}, 
    Card_Element{.pos = pos[5], .n = nx, .text_cord = {-1,-1}}, 
    //surface 4
    Card_Element{.pos = pos[2], .n = ny, .text_cord = {-1,-1}}, 
    Card_Element{.pos = pos[3], .n = ny, .text_cord = {-1,-1}},
    Card_Element{.pos = pos[7], .n = ny, .text_cord = {-1,-1}}, 
    Card_Element{.pos = pos[6], .n = ny, .text_cord = {-1,-1}},
    //surface 5
    Card_Element{.pos = pos[3], .n = -nx, .text_cord = {-1,-1}}, 
    Card_Element{.pos = pos[0], .n = -nx, .text_cord = {-1,-1}}, 
    Card_Element{.pos = pos[4], .n = -nx, .text_cord = {-1,-1}}, 
    Card_Element{.pos = pos[7], .n = -nx, .text_cord = {-1,-1}}, 
    //surface 6
    Card_Element{.pos = pos[0], .n = -nz, .text_cord = {-1,-1}}, 
    Card_Element{.pos = pos[1], .n = -nz, .text_cord = {-1,-1}}, 
    Card_Element{.pos = pos[2], .n = -nz, .text_cord = {-1,-1}}, 
    Card_Element{.pos = pos[3], .n = -nz, .text_cord = {-1,-1}}
};

std::array<unsigned int, 36> indices {
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

void set_textcord(unsigned int id, float texture_width, float texture_height, std::array<Card_Element, 24>& surfaces) {
    //height / width
    static constexpr float ratio = 7.f / 5;
    //# of cards in one line
    static constexpr float row_num = 10;
    const float width = texture_width / row_num;
    const float height = ratio * width;
    assert(id < 90);
    if(id > 40)
        id -= 40;
    if(id > 30)
        id -= 30;
    unsigned int r = id / 10;
    unsigned int c = id % 10;
    const float width_normalize = width / texture_width;
    const float height_normalize = height / texture_height;
    const float x_low_normalize = c * width / texture_width;
    const float x_high_normalize = x_low_normalize + width / texture_width;
    const float y_high_normalize = 1.f - r * height / texture_height;
    const float y_low_normalize = y_high_normalize - height / texture_height;

    //front
    // 1 - 0
    // |   |
    // 3 - 2
    surfaces[0].text_cord[0] = x_low_normalize;
    surfaces[0].text_cord[1] = y_low_normalize;
    surfaces[1].text_cord[0] = x_high_normalize;
    surfaces[1].text_cord[1] = y_low_normalize;
    surfaces[2].text_cord[0] = x_high_normalize;
    surfaces[2].text_cord[1] = y_high_normalize;
    surfaces[3].text_cord[0] = x_low_normalize;
    surfaces[3].text_cord[1] = y_high_normalize;
    //back
    surfaces[20].text_cord[0] = 1;
    surfaces[20].text_cord[1] = 0;
    surfaces[21].text_cord[0] = 1 - width_normalize;
    surfaces[21].text_cord[1] = 0;
    surfaces[22].text_cord[0] = 1 - width_normalize;
    surfaces[22].text_cord[1] = height_normalize;
    surfaces[23].text_cord[0] = 1;
    surfaces[23].text_cord[1] = height_normalize;
}



// lighting
glm::vec3 lightPos(1,2,3);

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    OpenGL::Window::window_initialize();

    // build and compile our shader zprogram
    // ------------------------------------
    OpenGL::Shader_Program shader;
    {
        using namespace OpenGL;
        Shader<Vertex_Shader> vs {"../opengl/shader/2.2.basic_lighting.vs", File{}};
        Shader<Fragment_Shader> fs{"../opengl/shader/2.2.basic_lighting.fs", File{}};
        shader.init(vs, fs);
    }

    std::shared_ptr<OpenGL::Texture2D> texture = std::make_shared<OpenGL::Texture2D>("../opengl/data/level_0.jpg");
    shader.use();
    shader.set_int("texture1", 0);

    unsigned int VBO, cubeVAO, EBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(cubeVAO);


    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    set_textcord(11, texture->get_width(), texture->get_height(), elements);
    glBufferData(GL_ARRAY_BUFFER, sizeof(elements), &elements[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Card_Element), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Card_Element), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Card_Element), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);




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

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        texture->bind(0);
        // be sure to activate shader when setting uniforms/drawing objects
        shader.use();
        shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        shader.setVec3("lightPos", lightPos);
        shader.setVec3("viewPos", OpenGL::Window::camera.get_position());

        // // view/projection transformations
        // glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // glm::mat4 view = camera.GetViewMatrix();
        // lightingShader.setMat4("projection", projection);
        // lightingShader.setMat4("view", view);

        shader.setMat4("projection", OpenGL::Window::camera.get_projection( OpenGL::Window::src_width, OpenGL::Window::src_height));
        shader.setMat4("view", OpenGL::Window::camera.get_view_mat());
        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        shader.setMat4("model", model);

        // render the cube
        glBindVertexArray(cubeVAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(OpenGL::Window::window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}
