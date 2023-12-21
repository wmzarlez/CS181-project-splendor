#pragma once

#include "glad/glad.h"
#include <vector>
#include <span>
#include <optional>
#include <memory>
#include <tuple>
#include <algorithm>


namespace OpenGL{
    

    class ObjectBase {
        protected:
            std::optional<unsigned int> _id;
            ObjectBase() : _id{std::nullopt} {}
            ObjectBase(const BaseObject&) = delete;
            ObjectBase(ObjectBase&& other) { this->swap(other); }
            const ObjectBase& operator=(const ObjectBase&) = delete;
            const ObjectBase& operator=(ObjectBase&& other) { this->swap(other); return *this; }
            ~ObjectBase() {_id = std::nullopt;}
            inline void swap(ObjectBase& other) {
                std::swap(_id, other._id);
            } 
    };

    template<typename T>
    class BufferBase : public ObjectBase {
        public:
            enum struct DrawPolicy : unsigned int{
                //The data is set only once and used many times.
                STATIC  = GL_STATIC_DRAW, 
                //The data is changed a lot and used many times.
                DYNAMIC = GL_DYNAMIC_DRAW,
                //The data is set only once and used by the GPU at most a few times.
                STREAM  = GL_STREAM_DRAW
            };

        private:
            std::vector<T>      _data;
            DrawPolicy          _drawPolicy;

        public:
            BufferBase() : ObjectBase(), _drawPolicy(DrawPolicy::STATIC) {}

            BufferBase(std::span<const T> data, DrawPolicy drawPolicy = DrawPolicy::STATIC) : 
                ObjectBase(),
                _data{std::cbegin(data), std::cend(data)}, 
                _drawPolicy{drawPolicy} {
                unsigned int newId;
                glGenBuffers(1, &newId);
                _id = newId;
            }

            ~BufferBase() {
                if(_id) {
                    glDeleteBuffers(1, &(*_id));
                }
            }

            inline void swap(BufferBase& other) {
                ObjectBase::swap(other);
                std::swap(_data, other._data);
                std::swap(_drawPolicy, other._drawPolicy);
            }

            const BufferBase& operator=(BufferBase&& other) {
                this->swap(other);
                return *this;
            }

            inline std::vector<T>& get_data() { return _data; }

            inline void bind() const {
                if constexpr (std::is_same_v<T, float>) {
                    glBindBuffer(GL_ARRAY_BUFFER, *_id);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(T) * _data.size(), (const void*)_data.data(), static_cast<unsigned int>(_drawPolicy));
                } else if constexpr (std::is_same_v<T, float>)
            }
    };

    using VBO = BufferBase<float>;
    using EBO = BufferBase<unsigned int>;


    class VAO : public ObjectBase {
        private:
            std::vector<std::tuple<std::shared_ptr<VBO>, std::shared_ptr<EBO>>> _data;
        public:
            template<typename... Args>
            VAO(Args... args) : _data{args...} {
                unsigned int newId;
                glGenVertexArrays(1, &newId);
                _id = newId;
                std::for_each(std::cbegin)
            }

            ~VAO() {
                if(_id) {
                    glDeleteVertexArrays(1, &(*_id));
                }
            }

            inline void swap(VAO& other) {
                ObjectBase::swap(other);
                std::swap(_data, other._data);
            }

            const VAO& operator=(VAO&& other) {
                this->swap(other);
                return *this;
            }
    };
}