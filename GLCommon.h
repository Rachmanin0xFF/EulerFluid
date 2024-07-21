#pragma once
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <fstream>
#include <iostream>

namespace glutil {
    struct shaderTuple {
        GLuint vs;
        GLuint fs;
        GLuint program;
        ~shaderTuple() {
            glDeleteProgram(program);
            glDeleteShader(vs);
            glDeleteShader(fs);
        }
    };

    std::string load_str(const char* path);

    void load_shader(const char* vert_path, const char* frag_path, shaderTuple& data);
}