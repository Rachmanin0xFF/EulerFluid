#include "GLFluidGrid.h"
#include <vector>

GLuint GLFluidGrid::get_texture_id() {
    return buffer_A.color_tex;
}

void GLFluidGrid::init() {
    glutil::gen_colorFBOTuple(grid_res, grid_res, buffer_A);
    glutil::gen_colorFBOTuple(grid_res, grid_res, buffer_B);

    glutil::load_shader("generic.vert", "advection.frag", advection);
    glutil::load_shader("generic.vert", "divergence.frag", divergence);
    glutil::load_shader("generic.vert", "jacobi.frag", jacobi);
    glutil::load_shader("generic.vert", "integrate.frag", integrate);
 }

void GLFluidGrid::update_mouse(const int& mx, const int& my) {
    mouseX = mx;
    mouseY = my;
}

void GLFluidGrid::set_uniforms(glutil::shaderTuple& t) {
    glUseProgram(t.program);
    unsigned int resLocation = glGetUniformLocation(t.program, "RES");
    glUniform2f(resLocation, grid_res, grid_res);
    unsigned int dtLocation = glGetUniformLocation(t.program, "dt");
    glUniform1f(dtLocation, 0.001);
    unsigned int rhoLocation = glGetUniformLocation(t.program, "rho");
    glUniform1f(rhoLocation, 100.0);
    unsigned int mouseLocation = glGetUniformLocation(t.program, "mouse");
    glUniform2f(mouseLocation, mouseX, grid_res - mouseY);
    unsigned int timeLocation = glGetUniformLocation(t.program, "time");
    glUniform1f(timeLocation, time);
    time += 0.01;
}

void GLFluidGrid::update() {
    set_uniforms(advection);
    set_uniforms(jacobi);
    set_uniforms(divergence);
    set_uniforms(integrate);

    FBO_to_FBO(buffer_A, buffer_B, advection);
    FBO_to_FBO(buffer_B, buffer_A, divergence);

    // diffusion
    for (int i = 0; i < 5; i++) {
        FBO_to_FBO(buffer_A, buffer_B, jacobi);
        FBO_to_FBO(buffer_B, buffer_A, jacobi);
    }
    FBO_to_FBO(buffer_A, buffer_B, jacobi);

    FBO_to_FBO(buffer_B, buffer_A, integrate);
}