#include "GLFluidGrid.h"
#include <vector>

GLuint GLFluidGrid::get_texture_id() {
    return buffer_A.color_tex;
}

void GLFluidGrid::init() {
    // generate the two buffers we'll ping-pong between
    glutil::gen_colorFBOTuple(grid_res, grid_res, buffer_A);
    glutil::gen_colorFBOTuple(grid_res, grid_res, buffer_B);

    glutil::load_shader("generic.vert", "advection.frag", advection);
    glutil::load_shader("generic.vert", "divergence.frag", divergence);
    glutil::load_shader("generic.vert", "jacobi.frag", jacobi);
    glutil::load_shader("generic.vert", "integrate.frag", integrate);
 }

void GLFluidGrid::update_mouse(const int& mx, const int& my, const int& dmx, const int& dmy) {
    mouseX = mx;
    mouseY = my;
    dmouseX = dmx;
    dmouseY = dmy;
}

void GLFluidGrid::set_uniforms(glutil::shaderTuple& t) {
    glUseProgram(t.program);
    unsigned int resLocation = glGetUniformLocation(t.program, "RES");
    glUniform2f(resLocation, grid_res, grid_res);
    unsigned int dtLocation = glGetUniformLocation(t.program, "dt");
    glUniform1f(dtLocation, 0.001);
    unsigned int rhoLocation = glGetUniformLocation(t.program, "rho");
    glUniform1f(rhoLocation, 100.01);

    // external input / non-const. stuff
    unsigned int mouseLocation = glGetUniformLocation(t.program, "mouse");
    glUniform2f(mouseLocation, mouseX, grid_res - mouseY);

    unsigned int dmouseLocation = glGetUniformLocation(t.program, "dmouse");
    glUniform2f(dmouseLocation, dmouseX, -dmouseY);
    // TODO: time setter
    unsigned int timeLocation = glGetUniformLocation(t.program, "time");
    glUniform1f(timeLocation, time);
    time += 0.002;
}

void GLFluidGrid::update() {
    set_uniforms(advection);
    set_uniforms(jacobi);
    set_uniforms(divergence);
    set_uniforms(integrate);

    // transport velocities without conservation
    FBO_to_FBO(buffer_A, buffer_B, advection);
    // compute divergence of new velocity field
    FBO_to_FBO(buffer_B, buffer_A, divergence);

    // find pressures (solve via jacobi method / diffusion)
    for (int i = 0; i < 40; i++) {
        FBO_to_FBO(buffer_A, buffer_B, jacobi);
        FBO_to_FBO(buffer_B, buffer_A, jacobi);
    }
    FBO_to_FBO(buffer_A, buffer_B, jacobi);

    // update velocities
    FBO_to_FBO(buffer_B, buffer_A, integrate);
}