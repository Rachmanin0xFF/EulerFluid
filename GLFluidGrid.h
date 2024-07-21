#pragma once
#include "GLCommon.h"
#include "FluidGrid.cuh"

class GLFluidGrid :
    public FluidGrid
{
public:
    GLFluidGrid(const GLuint& tex_output_ref) : FluidGrid(tex_output_ref) { init(); };
    void update();
    void init();
private:
    glutil::shaderTuple program1;
};

