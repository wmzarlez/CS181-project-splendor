#pragma once

#include "object_base.hpp"
#include "stb_image.h"
#include "util.hpp"
#include <array>

namespace OpenGL {

    struct TextureBase {
        public:
            virtual void bind(unsigned int idx) const = 0;
            int get_width() const { return _width; }
            int get_height()const { return _height; }
            int get_channel() const { return _channel; }
        protected:
            int _width;
            int _height;
            int _channel;
    };
    
    class Texture2D : public ObjectBase, public TextureBase {
        public:
            Texture2D(const char* input_path) {
                unsigned int texture_id;
                glGenTextures(1, &texture_id);
                _id = texture_id;
                glBindTexture(GL_TEXTURE_2D, *_id);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                stbi_set_flip_vertically_on_load(true);
                unsigned char *data = stbi_load(input_path, &_width, &_height, &_channel, 0);
                if(data) {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                }
                stbi_image_free(data);
            }

            void bind(unsigned int idx) const override {
                glActiveTexture(GL_TEXTURE0 + idx);
                glBindTexture(GL_TEXTURE_2D, *_id);
            }

            Texture2D() = default;

            ~Texture2D() {
                if(_id) {
                    unsigned int id = *_id;
                    glDeleteTextures(1, &id);
                    _id = std::nullopt;
                }
            }
    };
}

