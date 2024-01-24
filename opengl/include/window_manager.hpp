#pragma once
#include "GLFW/glfw3.h"
#include "camera.hpp"

namespace OpenGL {
    /**
     * @brief This namespace save the information of the window and IO
    */
    namespace Window {
        //window width
        extern unsigned int src_width;
        //window height
        extern unsigned int src_height;

        //x coordinate of the last mouse click
        extern float lastX;
        //y coordinate of the last mouse click
        extern float lastY;
        //whether this is the first frame
        extern bool first_mouse;

        //the time between this frame and last frame
        extern float delta_time;
        //the time point of the last frame
        extern float last_frame;

        //the window pointer
        extern GLFWwindow* window;

        //the camera 
        extern Camera camera;

        extern glm::vec3 light_pos;
        extern glm::vec3 light_color;


        void framebuffer_size_callback(GLFWwindow* window, int width, int height);

        void mouse_callback(GLFWwindow* window, double xpos, double ypos);

        void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

        //this function handle keyboard input
        void process_input(GLFWwindow* window);

        //initialize the window
        void window_initialize();
    }
}