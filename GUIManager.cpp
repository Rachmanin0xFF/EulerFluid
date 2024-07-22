#include <GL/glew.h>

#include "GUIManager.h"
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <vector>


void GUIManager::init() {
    std::vector<unsigned char> texDat(display_tex_res * display_tex_res);
    for (int i = 0; i < display_tex_res* display_tex_res; ++i)
        texDat[i] = ((i ^ (i / display_tex_res)) % 57 > 30) * 255; // test initialization texture
    glGenTextures(1, &display_tex);
    glBindTexture(GL_TEXTURE_2D, display_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, display_tex_res, display_tex_res, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, &(texDat[0]));
    glBindTexture(GL_TEXTURE_2D, 0);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
}

GUIManagerState GUIManager::update() {
    
    // check for resize (though we don't exactly handle it well lol)
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            return GUIManagerState::EXIT;
        }
        else if (event.type == sf::Event::Resized) {
            glViewport(0, 0, event.size.width, event.size.height);
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.f, 1.f, 1.f, 0.f);

    glViewport(0, 0, window.getSize().x, window.getSize().y);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, display_tex);

    glUseProgram(generic_shader.program);

    glutil::immediate_mode_rect();

    window.display();
    
    return GUIManagerState::RUNNING;
}