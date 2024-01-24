#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

namespace OpenGL {
    class Camera {
        public:
            enum struct Camera_Movement {
                FORWARD = 0, 
                BACKWARD = 1, 
                LEFT = 2, 
                RIGHT = 3
            };

            static constexpr float default_yaw          = -90.f;
            static constexpr float default_pitch        = 0.0f;
            static constexpr float default_speed        = 2.5f;
            static constexpr float default_sensitivity  = 0.1f;
            static constexpr float default_zoom         = 45.f;
        private:
            glm::vec3 _position;
            glm::vec3 _front;
            glm::vec3 _up;
            glm::vec3 _right;
            glm::vec3 _world_up;
            float _yaw;
            float _pitch;
            float _movement_speed;
            float _mouse_sensitivity;
            float _zoom;
            float _fov;
        public:
            Camera(glm::vec3 pos = glm::vec3{0.0f, 0.0f, 0.0f}, 
                   glm::vec3 world_up  = glm::vec3{0.0f, 1.0f, 0.0f}, 
                   float yaw = default_yaw,
                   float pitch = default_sensitivity, 
                   float fov = 44.0f);

            inline glm::mat4 get_view_mat() const {
                return glm::lookAt(_position, _position + _front, _up);
            }

            void process_keyboard(Camera_Movement dir, float deltaTime);

            void process_mouse_movement(float x_offset, float y_offset, bool constrain_pitch = true);

            void process_mouse_scroll(float y_offset);

            inline float get_zoom() const { return _zoom; }

            inline glm::vec3 get_position() const { return _position; }

            inline float get_fov() const { return _fov; }

            inline void set_fov(float fov) {
                _fov = std::max(1.0f, std::min(fov, 45.0f));
            }

            inline glm::mat4 get_projection(unsigned int window_width, unsigned int window_height) {
                return glm::perspective(glm::radians(_fov), (float)window_width / window_height, 0.1f, 100.f);
            }
        private:
            void update_camera_vectors();
    };
}