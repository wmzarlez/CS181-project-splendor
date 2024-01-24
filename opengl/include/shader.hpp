#pragma once

#include <string>
#include <fstream>
#include <iterator>
#include <numeric>
#include <array>
#include <cstddef>
#include <format>
#include <optional>
#include <concepts>
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "utils.hpp"
#include "object_base.hpp"

namespace OpenGL {

    struct Vertex_Shader {
        static constexpr GLenum type_id = GL_VERTEX_SHADER;
        static constexpr char name[]    = "vertex shader";
    };
    struct Fragment_Shader{
        static constexpr GLenum type_id = GL_FRAGMENT_SHADER;
        static constexpr char name[]    = "fragment shader";
    };

    template<typename T>
    concept Shaders =  requires(const T& v) {
        T::type_id;
        T::name;
        requires  std::disjunction_v<std::is_same<T, Vertex_Shader>, std::is_same<T, Fragment_Shader>>;
    };

    struct File {};
    struct String{};

    template<typename T>
    concept Load_Methods = requires(const T& v) {
        requires std::disjunction_v<std::is_same<T, File>, std::is_same<T, String>>;
    };

    template<Shaders S>
    class Shader : public ObjectBase {
        private:
            void init(const std::string& src);
        public:
            Shader(const std::string&, File);
            Shader(const std::string&, String);
            void swap(Shader& other) noexcept;
            ~Shader();
    };

    template<Shaders S>
    inline void Shader<S>::init(const std::string& src) {
        constexpr std::size_t buf_l = 512;
        int ok;
        char err_buf[buf_l] = {0};

        _id = glCreateShader(S::type_id);
        auto p_str = src.c_str();
        glShaderSource(*_id, 1, &p_str, nullptr);
        glCompileShader(*_id);

        glGetShaderiv(*_id, GL_COMPILE_STATUS, &ok);
        if(!ok) {
            glGetShaderInfoLog(*_id, buf_l, nullptr, err_buf);
            error(std::format("{} compile error with information {}.", S::name, err_buf));
        }
    }

    template<Shaders S>
    Shader<S>::~Shader() {
        if (_id) {
            glDeleteShader(*_id); 
            _id = std::nullopt;
        }
    }

    template<Shaders S>
    Shader<S>::Shader(const std::string& file_path, File) {
        std::string src;
        std::ifstream f{file_path};
        if(!f) {
            error(std::format("Could not open the file {}\n", file_path));
        }
        int c;
        while(f) {
            c = f.get();
            if(c != EOF)
                src.push_back(c);
        }

        init(src);
    }

    template<Shaders S>
    Shader<S>::Shader(const std::string& src, String) {
        init(src);
    }

    template<Shaders S>
    inline void Shader<S>::swap(Shader<S>& other) noexcept {
        ObjectBase::swap(reinterpret_cast<ObjectBase&>(other));
    }

    class Shader_Program : public ObjectBase{
        protected:
            /**
             * @brief Ensure this object hasn't been init.
            */
            void assert_empty() const;
            /**
             * @brief Ensure this object has been init.
            */
            void assert_valid() const;
        public:
            Shader_Program() = default;

            template<Shaders... Shader_Type>
            void init(const Shader<Shader_Type>&... shaders);

            void use() const;

            inline void swap(Shader_Program& other) noexcept {
                ObjectBase::swap(reinterpret_cast<ObjectBase&>(other));
            }

            ~Shader_Program() noexcept;

            void set_bool(const std::string& name, bool v) const;
            void set_int(const std::string& name, int v) const;
            void set_float(const std::string& name, float v) const;
            void setVec2(const std::string& name, const glm::vec2& v) const;
            void setVec2(const std::string& name, float x, float y) const;
            void setVec3(const std::string& name, const glm::vec3& v) const;
            void setVec3(const std::string& name, float x, float y, float z) const;
            void setVec4(const std::string& name, const glm::vec4& v) const;
            void setVec4(const std::string& name, float x, float y, float z, float w) const;
            void setMat2(const std::string& name, const glm::mat2& v) const;
            void setMat3(const std::string& name, const glm::mat3& v) const;
            void setMat4(const std::string& name, const glm::mat4& v) const;
            /**
             * @brief Tell VAO how to interpret the data in VBO.
            */
            //virtual void interpret() const = 0;
    };

    template<Shaders... Shader_Type>
    void Shader_Program::init(const Shader<Shader_Type>&... shaders) {
        _id = glCreateProgram();
        apply([this](const auto& shader){
            glAttachShader(*(this->_id), *shader.get_id());
        }, shaders...);
        glLinkProgram(*_id);

        int ok;
        constexpr std::size_t buf_l = 1024;
        char err_buf[buf_l] = {0};

        glGetProgramiv(*_id, GL_LINK_STATUS, &ok);
        if(!ok) {
            glGetProgramInfoLog(*_id, buf_l, nullptr, err_buf);
            error(std::format("shader program link error with information {}.", err_buf));
        }
    }
}

namespace std {
    template<OpenGL::Shaders S>
    inline void swap(OpenGL::Shader<S>& l, OpenGL::Shader<S>& r) {
        l.swap(r);
    }

    inline void swap(OpenGL::Shader_Program& l, OpenGL::Shader_Program& r) {
        l.swap(r);
    }
}

