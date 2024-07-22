#pragma once
#include <memory>
#include <SFML/OpenGL.hpp>

class FluidGrid {
public:
	virtual void init() = 0;
	virtual void update() = 0;
	virtual GLuint get_texture_id() = 0;
	virtual ~FluidGrid() = default;
protected:
	int grid_res = 512;
};