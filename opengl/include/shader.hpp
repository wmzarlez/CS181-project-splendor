#pragma once

#include <string>
#include <fstream>
#include <iterator>
#include <numeric>
#include <array>
#include <cstddef>
#include <format>
#include <optional>
#include "glad/glad.h"
#include "utils.hpp"



namespace OpenGL {
    enum struct shader_t : unsigned int {
        VERTEX = GL_VERTEX_SHADER, 
        FRAGMENT = GL_FRAGMENT_SHADER,
    };

    enum struct loader_t {
        FILE = 0, 
        STRING = 1,
    };

    template<shader_t Shader_t>
    class Shader {

        std::string _source;
        std::optional<unsigned int> _id;

        inline void init() {
            constexpr std::size_t buf_l = 512;
            int ok;
            char err_buf[buf_l];

            _id = glCreateShader(static_cast<GLenum>(Shader_t));
            const char* strs[] = {_source.c_str()};
            glShaderSource(*_id, 1, strs, nullptr);
            glCompileShader(*_id);

            glGetShaderiv(*_id, GL_COMPILE_STATUS, &ok);
            if(!ok) {
                glGetShaderInfoLog(*_id, buf_l, nullptr, err_buf);
                const char* shader_name = "null";
                if constexpr (Shader_t == shader_t::VERTEX) { shader_name = "vertex"; }
                else if constexpr (Shader_t == shader_t::FRAGMENT) { shader_name = "fragment"; }

                runtime_error(std::format("{} shader compile error!", shader_name));
            }
        }

    public:

        Shader() = default;

        Shader(std::string_view src, loader_t loadWay) {

            switch(loadWay) {
                case loader_t::FILE: {
                    std::ifstream f{std::cbegin(src)};
                    if(!f)
                        runtime_error(std::format("Could not open the file {}\n", src));
                    
                    int c;
                    while(f) {
                        c = f.get();
                        if(c != EOF)
                            _source.push_back(c);
                    }
                    break;
                }

                case loader_t::STRING : {
                    _source = src;
                }
            }

            init();
        }

        Shader(const Shader& other) = delete;
        Shader(Shader&& other) { this->swap(other); }
        const Shader& operator=(const Shader&) = delete;
        const Shader& operator=(Shader&& other) { this->swap(other); return *this; }
        ~Shader() { 
            if (_id) {
                glDeleteShader(*_id); 
                _id = std::nullopt;
            }
        }
        inline unsigned int get_id() const { return *_id; }

        inline void swap(Shader& other) {
            std::swap(_source, other._source);
            std::swap(_id, other._id);
        }
    };

    template<typename T>
    concept Shader_concept = requires(const T& shader) {
        shader.get_id();
    };

    using Vertex_Shader     = Shader<shader_t::VERTEX>;
    using Fragment_Shader   = Shader<shader_t::FRAGMENT>;

    inline Shader<shader_t::VERTEX> createVertexShaderFromFile(std::string_view str) {
        return std::move(Shader<shader_t::VERTEX>(str, loader_t::FILE));
    }

    inline Shader<shader_t::FRAGMENT> createFragmentShaderFromFile(std::string_view str) {
        return std::move(Shader<shader_t::FRAGMENT>(str, loader_t::FILE));
    }

    class Shader_Program {
        private:
            std::optional<unsigned int> _id;

            inline void is_valid() const {
                if(!_id)
                    runtime_error("Shader is not valid!");
            }

        public:
            Shader_Program() = default;

            template<Shader_concept... Shaders>
            Shader_Program(Shaders&&... shaders) {
                constexpr std::size_t buf_l = 512;

                int ok;
                char err_buf[buf_l];

                _id = glCreateProgram();

                apply([=, this](const auto& shader){
                    glAttachShader(*_id, shader.get_id());
                }, std::forward<Shaders>(shaders)...);

                glLinkProgram(*_id);

                glGetProgramiv(*_id, GL_LINK_STATUS, &ok);
                if(!ok) {
                    glGetProgramInfoLog(*_id, buf_l, nullptr, err_buf);
                    runtime_error(std::format("ERROR::SHADER_PROGRAM::LINK_FAILED\n{}\n", err_buf));
                }
            }

            Shader_Program(const Shader_Program&) = delete;
            Shader_Program(Shader_Program&& other) { this->swap(other); }

            const Shader_Program& operator=(const Shader_Program&) = delete;
            const Shader_Program& operator=(Shader_Program&& other) { this->swap(other); return *this; }

            inline void use() const {
                is_valid();
                glUseProgram(*_id);
            }

            inline void swap(Shader_Program& other) {
                std::swap(_id, other._id);
            }

            ~Shader_Program() {
                if (_id) {
                    glDeleteProgram(*_id);
                    _id = std::nullopt;
                }
            }

            inline void set_bool(const std::string& str, bool v) const {
                glUniform1i(glGetUniformLocation(*_id, str.c_str()), (int)v);
            }

            inline void set_int(const std::string& str, int v) const {
                glUniform1i(glGetUniformLocation(*_id, str.c_str()), v);
            }

            inline void set_float(const std::string& str, float v) const {
                glUniform1f(glGetUniformLocation(*_id, str.c_str()), v);
            }

    };
}

template<OpenGL::shader_t Shader_t>
inline void std::swap(OpenGL::Shader<Shader_t>& l, OpenGL::Shader<Shader_t>& r) {
    l.swap(r);
}

template<>
inline void std::swap(OpenGL::Shader_Program& l, OpenGL::Shader_Program& r) {
    l.swap(r);
}
