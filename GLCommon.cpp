#include "GLCommon.h"

glutil::colorFBOTuple glutil::get_screen_buffer() {
    colorFBOTuple t;
    t.FBO = 0;
    return t;
}

// "filters" one FBO to another using some shader
void glutil::FBO_to_FBO(const colorFBOTuple& in, const colorFBOTuple& out, const shaderTuple& transform) {
    
    glEnable(GL_TEXTURE_2D);
    glBindFramebuffer(GL_FRAMEBUFFER, out.FBO);
    glUseProgram(transform.program);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, in.color_tex);

    immediate_mode_rect();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// todo: vertex array object? low priority
void glutil::immediate_mode_rect() {
    glDisable(GL_DEPTH_TEST);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(-1, -1);
    glTexCoord2f(0, 1); glVertex2f(-1, 1);
    glTexCoord2f(1, 1); glVertex2f(1, 1);
    glTexCoord2f(1, 0); glVertex2f(1, -1);
    glEnd();
}

glutil::colorFBOTuple::~colorFBOTuple() {
    glDeleteFramebuffers(1, &FBO);
    glDeleteTextures(1, &color_tex);
}

// FBO generation code!
// makes a 16-bit floating-point RGBA texture with NO depth map
void glutil::gen_colorFBOTuple(const int& width, const int& height, colorFBOTuple& ids) {
    ids.w = width;
    ids.h = height;
    glGenFramebuffers(1, &(ids.FBO));
    glBindFramebuffer(GL_FRAMEBUFFER, ids.FBO);
    glGenTextures(1, &(ids.color_tex));
    glBindTexture(GL_TEXTURE_2D, ids.color_tex);

    glTexImage2D(GL_TEXTURE_2D, 
        0, 
        GL_RGBA16F, 
        ids.w, ids.h, 
        0, 
        GL_RGBA, 
        GL_FLOAT, 
        NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ids.color_tex, 0);
    
    const GLenum buffer[]{ GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, buffer);

    GLenum status;
    status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
    switch (status) {
        case GL_FRAMEBUFFER_COMPLETE:
            break;
        default:
            std::cerr << "Framebuffer creation failed. Aborting." << std::endl;
            // note for debugging: maybe format not allowed? check GL_FRAMEBUFFER_UNSUPPORTED
            exit(-1);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

glutil::shaderTuple::~shaderTuple() {
        glDeleteProgram(program);
        glDeleteShader(vs);
        glDeleteShader(fs);
}

// for loading shaders (not safe, TODO)
std::string glutil::load_str(const char* path) {
    std::string line, text;
    std::ifstream in(path);
    while (std::getline(in, line))
    {
        text += line + "\n";
    }
    return text;
}

// icky function....
void glutil::load_shader(const char* vert_path, const char* frag_path, shaderTuple& data) {
    std::string vertex_shader = load_str(vert_path);
    std::string fragment_shader = load_str(frag_path);

    data.vs = glCreateShader(GL_VERTEX_SHADER);
    const char* c_str = vertex_shader.c_str();
    glShaderSource(data.vs, 1, &c_str, NULL);
    glCompileShader(data.vs);
    GLint isCompiled = 0;
    glGetShaderiv(data.vs, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(data.vs, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(data.vs, maxLength, &maxLength, &errorLog[0]);

        for (int i = 0; i < maxLength - 1; i++) {
            std::cout << errorLog[i];
        }

        glDeleteShader(data.fs);
        return;
    }

    data.fs = glCreateShader(GL_FRAGMENT_SHADER);
    c_str = fragment_shader.c_str();
    glShaderSource(data.fs, 1, &c_str, NULL);
    glCompileShader(data.fs);
    glGetShaderiv(data.fs, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(data.fs, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(data.fs, maxLength, &maxLength, &errorLog[0]);

        for (int i = 0; i < maxLength - 1; i++) {
            std::cout << errorLog[i];
        }

        glDeleteShader(data.vs);
        return;
    }

    data.program = glCreateProgram();
    glAttachShader(data.program, data.fs);
    glAttachShader(data.program, data.vs);
    glLinkProgram(data.program);
    glUseProgram(data.program);
}