#pragma once

#include <functional>
#include <cmath>
#include <memory>
#include <list>
#include "glm/glm.hpp"
#include "game_object.hpp"

namespace OpenGL {
    struct Movement {
        /**
         * @param t the current time
         * @return whether this Movement is finished
        */
        virtual bool update(float t) = 0;
    };

    std::function<glm::mat3(float)> gen_y_negative(float degree) {
        return [=](float t)->glm::mat3 {
            const float theta = glm::radians(t * degree);
            return glm::mat3{
                std::cos(theta), 0, std::sin(theta), 
                0, 1, 0, 
                -std::sin(theta), 0, std::cos(theta)
            };
        };
    }

    std::function<glm::mat3(float)> gen_x_negative(float degree) {
        return [=](float t)->glm::mat3 {
            const float theta = glm::radians(t * degree);
            return glm::mat3{
                1, 0, 0, 
                0, std::cos(theta), -std::sin(theta), 
                0, std::sin(theta), std::cos(theta)
            };
        };
    }

    std::function<glm::mat3(float)> gen_z_negative(float degree) {
        return [=](float t)->glm::mat3 {
            const float theta = glm::radians(t * degree);
            return glm::mat3 {
                std::cos(theta), -std::sin(theta), 0, 
                std::sin(theta), std::cos(theta) , 0, 
                0, 0, 1
            };
        };
    }

    std::function<glm::vec3(float)> gen_Bezier_path_2(glm::vec3 p_start, glm::vec3 p_end, glm::vec3 ref_up) {
        /*              
                p1-----p2 
                |
                |
                p0
                where |p0p1|=|p1p2| and p0p1 is perpendicular to p2p1
        */
        const glm::vec3 X = p_end - p_start;
        glm::vec3 Y = glm::cross(ref_up, X);
        float length = glm::length(X);
        glm::vec3 Z =glm::normalize(glm::cross(X, Y));
        glm::vec3 p1 = 0.5f * (p_start + p_end) + (0.5f * length * Z);
        return [=](float t)->glm::vec3 {
            const glm::vec3 _p0 = p_start;
            const glm::vec3 _p1 = p1;
            const glm::vec3 _p2 = p_end;
            return (1-t) * (1-t) * _p0 + 2 * t * (1-t) * _p1 + t * t * _p2;
        };
    }

    struct Rotation : public Movement{
            Rotation(std::shared_ptr<GameObject> object, float curr_t, float t_scale, std::function<glm::mat3(float)> update_f) : 
                _object{object}, _last_t{curr_t}, _residue_t{1}, _t_scale{t_scale}, _update{update_f} {}

            bool update(float t) override {
                const float delta_t = t - _last_t;
                _last_t = t;
                const float normalize_t = delta_t * _t_scale;
                const float update_t = std::min(_residue_t, normalize_t);
                _residue_t -= update_t;
                _object->set_rot(_object->get_rot() * _update(update_t));
                return _residue_t <= 0;
            }
        private:
            std::shared_ptr<GameObject> _object;
            float _last_t;
            float _residue_t;
            const float _t_scale;
            std::function<glm::mat3(float)> _update;
    };

    struct Translation : public Movement {
        private:
            std::shared_ptr<GameObject> _object;
            const float _start_t;
            const float _t_scale;
            std::function<glm::vec3(float)> _update;
        public:
            Translation(std::shared_ptr<GameObject> object, float curr_t, float t_scale, std::function<glm::vec3(float)> update_f) : 
                _object{object}, _start_t{curr_t}, _t_scale{t_scale}, _update{update_f} {}
            
            bool update(float t) override {
                const float normalize_t = std::min((t - _start_t) * _t_scale, 1.f);
                _object->set_trans(_update(normalize_t));
                return normalize_t >= 1;
            }

    };

    class Movement_Manager {
        private:
            std::list<std::shared_ptr<Movement>> _data;
        public:
            Movement_Manager() = default;

            void add_movement(std::shared_ptr<Movement> new_movement) {
                _data.push_back(new_movement);
            }

            void update(float curr_t) {
                for(auto iter = _data.begin() ; iter != _data.end() ; ) {
                    auto ret = (*iter)->update(curr_t);
                    if(ret) {
                        iter = _data.erase(iter);
                    } else {
                        ++iter;
                    }
                }
            }
    };
}
