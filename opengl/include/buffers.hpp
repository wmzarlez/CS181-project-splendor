#pragma once

#include <glad/glad.h>
#include "stb_image.h"
#include "object_base.hpp"

#include <vector>


namespace OpenGL{

    struct _VBO {
        static constexpr GLenum target = GL_ARRAY_BUFFER;
    };

    struct _EBO {
        static constexpr GLenum target = GL_ELEMENT_ARRAY_BUFFER;
    };

    template<typename T>
    concept Buffers = requires(const T& x) {
        T::target;
        requires std::disjunction_v<std::is_same<T, _VBO>, std::is_same<T, _EBO>>;
    };

    enum struct Buffer_Usage : GLenum {
        Stream_Draw = GL_STREAM_DRAW,
        Static_Draw = GL_STATIC_DRAW, 
        Dynamic_Draw = GL_DYNAMIC_DRAW, 
    };

    template<Buffers Which, typename T>
    class Buffer : public ObjectBase {
        private:
            std::vector<T> _data;
            Buffer_Usage _usage;
        public:
            Buffer() : _usage{Buffer_Usage::Static_Draw} {
                unsigned int id = 0;
                glGenBuffers(1, &id);
                _id = id;
            }

            Buffer(std::vector<T> data, Buffer_Usage usage = Buffer_Usage::Static_Draw) : 
                _data(std::move(data)), 
                _usage(usage) {
                unsigned int id = 0;
                glGenBuffers(1, &id);
                _id = id;
            }

            void bind() const {
                glBindBuffer(Which::target, *_id);
                glBufferData(Which::target, sizeof(T) * _data.size(), (void*)_data.data(), static_cast<GLenum>(_usage));
            }

            Buffer_Usage get_usage() const { return _usage; }

            void set_usage(Buffer_Usage usage) { _usage = usage; }

            const std::vector<T> get_data() const { return _data; }

            void set_data(std::vector<T> data) { _data = std::move(data); }

            ~Buffer() {
                if(_id) {
                    unsigned int id = *_id;
                    glDeleteBuffers(1, &id);
                    _id = std::nullopt;
                }
            }

    };

    template<typename T>
    using VBO = Buffer<_VBO, T>;

    template<typename T>
    using EBO = Buffer<_EBO, T>;

    class VAO : public ObjectBase {
        public:
            VAO() {
                unsigned int id;
                glGenVertexArrays(1, &id);
                _id = id;
            }

            void bind() const {
                assert(_id);
                glBindVertexArray(*_id);
            }

            void unbind() const {
                assert(_id);
                glBindVertexArray(0);
            }

            ~VAO() {
                if(_id) {
                    unsigned int id = *_id;
                    glDeleteVertexArrays(1, &id);
                    _id = std::nullopt;
                }
            }
    };
}