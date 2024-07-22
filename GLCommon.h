#pragma once
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <fstream>
#include <iostream>

// general opengl utilitiy functions (making textures, fbos, loading shaders, etc.)
namespace glutil {

    // not really a 'tuple', lol
    struct shaderTuple {
        GLuint vs;
        GLuint fs;
        GLuint program;
        ~shaderTuple();
    };

    struct colorFBOTuple {
        GLuint color_tex;
        GLuint FBO;
        int w;
        int h;
        ~colorFBOTuple();
    };

    void immediate_mode_rect();

    colorFBOTuple get_screen_buffer();
    void FBO_to_FBO(const colorFBOTuple &in, const colorFBOTuple &out, const shaderTuple &transform);

    std::string load_str(const char* path);

    void load_shader(const char* vert_path, const char* frag_path, shaderTuple& ids);

    void gen_colorFBOTuple(const int& width, const int& height, colorFBOTuple& ids);
}