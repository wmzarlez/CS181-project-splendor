#pragma once

#include <unordered_map>
#include <memory>
#include "game_object.hpp"

namespace OpenGL {
    class Render_Manager {
        private:
            std::unordered_map<unsigned int, std::shared_ptr<GameObject>> _data;
        public:
            Render_Manager() = default;

            void add_game_object(std::shared_ptr<GameObject> new_object) {
                _data[new_object->get_id()] = new_object;
            } 

            void render() {
                for(const auto&[id, object] : _data) {
                    object->draw();
                }
            }
            /**
             * @return true if remove successfully, otherwise false
            */
            bool remove(unsigned int id) {
                auto iter = _data.find(id);
                if(iter == _data.end()) {
                    return false;
                }
                else {
                    _data.erase(iter);
                    return true;
                }
            }
    };
}