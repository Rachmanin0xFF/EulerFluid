#include "GLCommon.h"

std::string glutil::load_str(const char* path) {
    std::string line, text;
    std::ifstream in(path);
    while (std::getline(in, line))
    {
        text += line + "\n";
    }
    return text;
}

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