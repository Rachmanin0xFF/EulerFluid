#pragma once
#include "GLCommon.h"
#include "FluidGrid.cuh"

class GLFluidGrid :
    public FluidGrid
{
public:
    GLFluidGrid(const int& res) { grid_res = res; init(); }
    void update();
    void init();
    GLuint get_texture_id();
    void update_mouse(const int& mx, const int& my, const int& dmx, const int& dmy); // should be in virtual
private:
    void set_uniforms(glutil::shaderTuple& t);
    glutil::shaderTuple advection;
    glutil::shaderTuple divergence;
    glutil::shaderTuple jacobi;
    glutil::shaderTuple integrate;
    glutil::shaderTuple color_transport;
    glutil::shaderTuple generic;
    glutil::colorFBOTuple buffer_A;
    glutil::colorFBOTuple buffer_B;
    glutil::colorFBOTuple buffer_C;
    glutil::colorFBOTuple buffer_out;
    float mouseX;
    float mouseY;
    float dmouseX;
    float dmouseY;
    float time{ 0 };
};

