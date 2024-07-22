#include <GL/glew.h>
#include <iostream>

#include "GUIManager.h"
#include "GLFluidGrid.h"

int main() {
	GUIManager gui(800, 800);
	
	GLFluidGrid grid(800);
	GUIManagerState gui_state;
	// let the gui see the fluid texture
	gui.set_texture_id(grid.get_texture_id());
	
	int pmx = gui.get_mouse_position().x;
	int pmy = gui.get_mouse_position().y;


	// main loop
	do {
		grid.update();
		gui_state = gui.update();

		int mx = gui.get_mouse_position().x;
		int my = gui.get_mouse_position().y;
		grid.update_mouse(mx, my, mx - pmx, my - pmy);
		pmx = mx;
		pmy = my;
	} while (gui_state == GUIManagerState::RUNNING);
}