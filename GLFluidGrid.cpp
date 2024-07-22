#include "GLFluidGrid.h"
#include <vector>

GLuint GLFluidGrid::get_texture_id() {
    return buffer_out.color_tex;
}

void GLFluidGrid::init() {
    // generate the two buffers we'll ping-pong between
    glutil::gen_colorFBOTuple(grid_res, grid_res, buffer_A);
    glutil::gen_colorFBOTuple(grid_res, grid_res, buffer_B);

    // buffers for color information and output texture
    glutil::gen_colorFBOTuple(grid_res, grid_res, buffer_C);
    glutil::gen_colorFBOTuple(grid_res, grid_res, buffer_out);

    glutil::load_shader("generic.vert", "advection.frag", advection);
    glutil::load_shader("generic.vert", "divergence.frag", divergence);
    glutil::load_shader("generic.vert", "jacobi.frag", jacobi);
    glutil::load_shader("generic.vert", "integrate.frag", integrate);
    glutil::load_shader("generic.vert", "color_transport.frag", color_transport);
    glutil::load_shader("generic.vert", "generic.frag", generic);
    glutil::load_shader("generic.vert", "final_pass.frag", final_pass);
 }

void GLFluidGrid::update_mouse(const int& mx, const int& my, const int& dmx, const int& dmy) {
    mouseX = mx;
    mouseY = my;
    dmouseX = dmx;
    dmouseY = dmy;
}

void GLFluidGrid::set_uniforms(glutil::shaderTuple& t) {
    glUseProgram(t.program);
    glUniform2f(glGetUniformLocation(t.program, "RES"), grid_res, grid_res);
    
    glUniform1f(glGetUniformLocation(t.program, "dt"), 0.001);
    glUniform1f(glGetUniformLocation(t.program, "rho"), 100.01);

    // external input / non-const. stuff
    glUniform2f(glGetUniformLocation(t.program, "mouse"), mouseX, grid_res - mouseY);

    glUniform2f(glGetUniformLocation(t.program, "dmouse"), dmouseX, -dmouseY);
    // TODO: time setter
    glUniform1f(glGetUniformLocation(t.program, "time"), time);

    time += 0.002;
}

void GLFluidGrid::update() {
    set_uniforms(advection);
    set_uniforms(jacobi);
    set_uniforms(divergence);
    set_uniforms(integrate);
    set_uniforms(color_transport);
    set_uniforms(final_pass);

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


    
    glEnable(GL_TEXTURE1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, buffer_C.color_tex);
    FBO_to_FBO(buffer_A, buffer_B, color_transport);
    FBO_to_FBO(buffer_B, buffer_C, generic);

    FBO_to_FBO(buffer_A, buffer_out, final_pass);
}