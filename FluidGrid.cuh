#pragma once
#include <memory>
#include <SFML/OpenGL.hpp>

class FluidGrid {
public:
	virtual void init() = 0;
	virtual void update() = 0;
	virtual ~FluidGrid() = default;
	FluidGrid(const GLuint& tex_output_ref) : gl_display_texture(tex_output_ref) {};
protected:
	GLuint gl_display_texture;
};