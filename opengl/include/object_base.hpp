#pragma once

#include <optional>

namespace OpenGL {
    class ObjectBase {
        protected:
            std::optional<unsigned int> _id;
            ObjectBase() : _id{std::nullopt} {}
            ObjectBase(const ObjectBase&) = delete;
            ObjectBase(ObjectBase&& other) { this->swap(other); }
            const ObjectBase& operator=(const ObjectBase&) = delete;
            const ObjectBase& operator=(ObjectBase&& other) { this->swap(other); return *this; }
            ~ObjectBase() {_id = std::nullopt;}
            inline void swap(ObjectBase& other) {
                std::swap(_id, other._id);
            } 
        public:
            auto get_id() const {
                return _id;
            }
    };
}
