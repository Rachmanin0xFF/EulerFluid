#pragma once
#include "GLCommon.h"

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

enum GUIManagerState {
	RUNNING=1,
	EXIT=0
};

class GUIManager
{
public:
	GUIManager(const int& width, const int& height)
		: window(sf::VideoMode(width, height), "OpenGL", sf::Style::Default, sf::ContextSettings(0, 0, 0, 4, 1)) {
		window.setVerticalSyncEnabled(true);
		window.setActive(true);
		display_tex_res = width;
		init();
		glutil::load_shader("shaders/generic.vert", "shaders/generic.frag", generic_shader);
	};
	GUIManagerState update();
	void init();

	// TODO: make more memory-safe
	//		 need to think about other use cases...
	void set_texture_id(const GLuint &new_id) {
		display_tex = new_id;
	}

	GLuint get_texture_id() { return display_tex; }
	~GUIManager() {
		glDeleteTextures(1, &display_tex);
	};
	sf::Vector2i get_mouse_position() {
		return sf::Mouse::getPosition(window);
	}
private:
	sf::Window window;
	GLuint display_tex;
	int display_tex_res = 512;
	glutil::shaderTuple generic_shader;
};

