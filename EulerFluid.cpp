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

	// main loop
	do {
		grid.update();
		gui_state = gui.update();

		grid.update_mouse(gui.get_mouse_position().x, gui.get_mouse_position().y);
	} while (gui_state == GUIManagerState::RUNNING);
}