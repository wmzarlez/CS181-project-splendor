#include "glad/glad.h"
#include "window_manager.hpp"
#include <iostream>
#include <cstdlib>

namespace OpenGL {
    namespace Window {
        // the width of the window
        unsigned int src_width = 1600;
        unsigned int src_height = 1200;

        float lastX = src_width / 2.0f;
        float lastY = src_height / 2.0f;

        bool first_mouse = true;

        float delta_time = 0.0f;
        float last_frame = 0.0f;

        GLFWwindow* window = nullptr;

        Camera camera {glm::vec3{0, 0, 3}};

        glm::vec3 light_pos {0,0,5};
        glm::vec3 light_color {1,1,1};

        void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
            src_width = width;
            src_height = height;
        }

        void mouse_callback(GLFWwindow* window, double xInPos, double yInPos) {
            float xpos = static_cast<float>(xInPos);
            float ypos = static_cast<float>(yInPos);
            if(first_mouse) {
                first_mouse = false;
                lastX = xpos;
                lastY = ypos;
            }
            float xoffset = xpos - lastX;
            float yoffset = ypos - lastY;
            lastX = xpos;
            lastY = ypos;
            camera.process_mouse_movement(xoffset, yoffset);
        }

        void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
            camera.set_fov(camera.get_fov()-static_cast<float>(yoffset));
        }

        void process_input(GLFWwindow* window) {
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, true);

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                camera.process_keyboard(OpenGL::Camera::Camera_Movement::FORWARD, delta_time);
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                camera.process_keyboard(OpenGL::Camera::Camera_Movement::BACKWARD, delta_time);
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                camera.process_keyboard(OpenGL::Camera::Camera_Movement::LEFT, delta_time);
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                camera.process_keyboard(OpenGL::Camera::Camera_Movement::RIGHT, delta_time);
        }

        void window_initialize() {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            #ifdef __APPLE__
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            #endif 

            window = glfwCreateWindow(800, 600, "splendor", NULL, NULL);

            if(!window) {
                std::cerr << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                exit(-1);
            }

            glfwMakeContextCurrent(window);
            glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
            glfwSetCursorPosCallback(window, mouse_callback);
            glfwSetScrollCallback(window, scroll_callback);

            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                std::cerr << "Failed to initialize GLAD" << std::endl;
                glfwTerminate();
                exit(-1);
            }

            glEnable(GL_DEPTH_TEST);
        }
    }
}