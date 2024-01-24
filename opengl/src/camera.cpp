#include "camera.hpp"

namespace OpenGL {
    void Camera::update_camera_vectors() {
        glm::vec3 front;
        front.x = std::cos(glm::radians(_yaw)) * std::cos(glm::radians(_pitch));
        front.y = std::sin(glm::radians(_pitch));
        front.z = std::sin(glm::radians(_yaw)) * std::cos(glm::radians(_pitch));
        _front = glm::normalize(front);

        _right = glm::normalize(glm::cross(_front, _world_up));
        _up    = glm::normalize(glm::cross(_right, _front));
    }

    Camera::Camera(glm::vec3 pos, glm::vec3 world_up, float yaw, float pitch, float fov) : 
        _position{pos},
        _front{glm::vec3{.0f, .0f, -1.f}},
        _world_up{world_up}, 
        _yaw{yaw}, 
        _pitch{pitch}, 
        _movement_speed{default_speed}, 
        _mouse_sensitivity{default_sensitivity}, 
        _zoom{default_zoom}, 
        _fov{fov} {
        update_camera_vectors();
    } 

    void Camera::process_keyboard(Camera_Movement dir, float deltaTime) {
        float v = _movement_speed * deltaTime;
        switch(dir) {
            case Camera_Movement::FORWARD:
                _position += _front * v;
                break;
            case Camera_Movement::BACKWARD:
                _position -= _front * v;
                break;
            case Camera_Movement::LEFT:
                _position -= _right * v;
                break;
            case Camera_Movement::RIGHT:
                _position += _right * v;
                break;
            default:
                //...
                break;
        }
    }

    void Camera::process_mouse_movement(float x_offset, float y_offset, bool constrain_pitch) {
        x_offset *= _mouse_sensitivity;
        y_offset *= _mouse_sensitivity;

        _yaw += x_offset;
        _pitch -= y_offset;

        if(constrain_pitch) {
            _pitch = std::min(_pitch, 89.0f);
            _pitch = std::max(_pitch, -89.0f);
        }

        update_camera_vectors();
    }

    void Camera::process_mouse_scroll(float y_offset) {
        _zoom -= y_offset;
        _zoom = std::max(_zoom, 1.f);
        _zoom = std::min(_zoom, 45.f);
    }
}