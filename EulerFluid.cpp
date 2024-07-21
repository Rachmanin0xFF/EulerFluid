#include <GL/glew.h>

#include "GUIManager.h"
#include "GLFluidGrid.h"

int main() {
	GUIManager gui(800, 600);
	
	GLFluidGrid grid(gui.get_texture_id());
	GUIManagerState gui_state;
	do {
		grid.update();
		gui_state = gui.update();
	} while (gui_state == GUIManagerState::RUNNING);
}