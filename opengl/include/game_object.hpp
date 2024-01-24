#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.hpp>
#include <vector>
#include <memory>
#include <cstdint>
#include "object_base.hpp"
#include "type_traits"

namespace OpenGL {

    class GameObject {
        protected:
            unsigned int _id;
            glm::vec3 _scaling;
            glm::mat3 _rotation;
            glm::vec3 _translation;

        public:
            GameObject(unsigned int id, glm::vec3 scaling, glm::mat3 rotation, 
            glm::vec3 translation) : _id{id}, _scaling{scaling}, 
            _rotation{rotation}, _translation{translation} {}

            unsigned int get_id() const {
                return _id;
            }

            glm::mat4 get_model_mat4() const;

            virtual void draw() const = 0;

            void relative_to_absolute_rot(const GameObject& other) {
                _rotation = other._rotation * _rotation;
            }

            glm::vec3 get_scale() const { return _scaling; }

            void set_scale(glm::vec3 scale) { _scaling = std::move(scale); }

            glm::mat3 get_rot() const { return _rotation; }

            void set_rot(glm::mat3 rot) { _rotation = std::move(rot); }

            glm::vec3 get_trans() const { return _translation; }

            void set_trans(glm::vec3 trans) { _translation = std::move(trans); }
    };


    glm::mat4 GameObject::get_model_mat4() const {
        glm::mat4 RT {_rotation};
        RT[3][0] = _translation[0];
        RT[3][1] = _translation[1];
        RT[3][2] = _translation[2];
        RT[3][3] = 1;
        /*
            Here RT is:
            ---               ---
            |   R(3x3)  T(3x1)  |  
            |                   |
            |   0(1x3)  1       |
            ---               --- (4x4)
        */
        return RT * glm::scale(glm::mat4{1}, _scaling);
    }
}