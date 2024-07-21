#include "GLFluidGrid.h"
#include <vector>

void GLFluidGrid::init() {
    std::vector<unsigned char> texDat(50*50);

    glutil::load_shader("generic.vert", "fluid_GL_1.frag", program1);
    
}

void GLFluidGrid::update() {
    glUseProgram(program1.program);
}