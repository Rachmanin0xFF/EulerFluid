#pragma once
#include "GLCommon.h"
#include "FluidGrid.cuh"

class GLFluidGrid :
    public FluidGrid
{
public:
    GLFluidGrid() { init(); }
    void update();
    void init();
    GLuint get_texture_id();
    void update_mouse(const int& mx, const int& my); // should be in virtual
private:
    void set_uniforms(glutil::shaderTuple& t);
    glutil::shaderTuple advection;
    glutil::shaderTuple divergence;
    glutil::shaderTuple jacobi;
    glutil::shaderTuple integrate;
    glutil::colorFBOTuple buffer_A;
    glutil::colorFBOTuple buffer_B;
    float mouseX;
    float mouseY;
    float time{ 0 };
};

