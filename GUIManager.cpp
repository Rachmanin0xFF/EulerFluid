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
    
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            return GUIManagerState::EXIT;
        }
        else if (event.type == sf::Event::Resized) {
            glViewport(0, 0, event.size.width, event.size.height);
        }
    }
    glClearColor(1.f, 0.f, 1.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, display_tex);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, display_tex_res, 0, display_tex_res, -1, 1);
    glUseProgram(generic_shader.program);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(-1, -1);
    glTexCoord2f(0, 1); glVertex2f(-1, 1);
    glTexCoord2f(1, 1); glVertex2f(1, 1);
    glTexCoord2f(1, 0); glVertex2f(1, -1);
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    window.display();
    
    return GUIManagerState::RUNNING;
}