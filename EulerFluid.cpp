#include <GL/glew.h>
#include <iostream>

#include "GUIManager.h"
#include "GLFluidGrid.h"

int main() {
	GUIManager gui(512, 512);
	
	GLFluidGrid grid;
	GUIManagerState gui_state;
	gui.set_texture_id(grid.get_texture_id());

	
	do {
		grid.update();
		gui_state = gui.update();

		grid.update_mouse(gui.get_mouse_position().x, gui.get_mouse_position().y);
	} while (gui_state == GUIManagerState::RUNNING);
}