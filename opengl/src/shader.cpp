#include "shader.hpp"

namespace OpenGL {
    //The implementation of Shader_Program

    void Shader_Program::assert_empty() const {
        if(_id)
            error(std::format("The shader has been init."));
    }

    void Shader_Program::assert_valid() const {
        if(!_id)
            error(std::format("The shader hasn't been init."));
    }

    void Shader_Program::use() const {
        assert_valid();
        glUseProgram(*_id);
    }


    Shader_Program::~Shader_Program() noexcept {
        if(_id) {
            glDeleteProgram(*_id);
            _id = std::nullopt;
        }
    }

    void Shader_Program::set_bool(const std::string& name, bool v) const {
        glUniform1i(glGetUniformLocation(*_id, name.c_str()), (GLint)v);
    }

    void Shader_Program::set_int(const std::string& name, int v) const {
        glUniform1i(glGetUniformLocation(*_id, name.c_str()), v);
    }

    void Shader_Program::set_float(const std::string& name, float v) const {
        glUniform1f(glGetUniformLocation(*_id, name.c_str()), v);
    }

    void Shader_Program::setVec2(const std::string& name, const glm::vec2& v) const {
        glUniform2fv(glGetUniformLocation(*_id, name.c_str()), 1, &v[0]);
    }

    void Shader_Program::setVec2(const std::string& name, float x, float y) const {
        glUniform2f(glGetUniformLocation(*_id, name.c_str()), x, y);
    }

    void Shader_Program::setVec3(const std::string& name, const glm::vec3& v) const {
        glUniform3fv(glGetUniformLocation(*_id, name.c_str()), 1, &v[0]);
    }

    void Shader_Program::setVec3(const std::string& name, float x, float y, float z) const {
        glUniform3f(glGetUniformLocation(*_id, name.c_str()), x, y, z);
    }

    void Shader_Program::setVec4(const std::string& name, const glm::vec4& v) const {
        glUniform4fv(glGetUniformLocation(*_id, name.c_str()), 1, &v[0]);
    }

    void Shader_Program::setVec4(const std::string& name, float x, float y, float z, float w) const {
        glUniform4f(glGetUniformLocation(*_id, name.c_str()), x, y, z, w);
    }

    void Shader_Program::setMat2(const std::string& name, const glm::mat2& v) const {
        glUniformMatrix2fv(glGetUniformLocation(*_id, name.c_str()), 1, GL_FALSE, &v[0][0]);
    }

    void Shader_Program::setMat3(const std::string& name, const glm::mat3& v) const {
        glUniformMatrix3fv(glGetUniformLocation(*_id, name.c_str()), 1, GL_FALSE, &v[0][0]);
    }

    void Shader_Program::setMat4(const std::string& name, const glm::mat4& v) const {
        glUniformMatrix4fv(glGetUniformLocation(*_id, name.c_str()), 1, GL_FALSE, &v[0][0]);
    }
}