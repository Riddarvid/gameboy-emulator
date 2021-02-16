/*
 * RenderView
 * This class handles the rendering of the Game Boy lcd.
 *
 * Author: Andreas Palmqvist
 */

#include "RenderView.h"

RenderView::RenderView(int screenMultiplier) {
    this->screenMultiplier = screenMultiplier;

    // Initialize screen quad.
    screenVertices[0] = {-1.0f, -1.0f};
    screenVertices[1] = {1.0f, -1.0f};
    screenVertices[2] = {1.0f, 1.0f};
    screenVertices[3] = {-1.0f, -1.0f};
    screenVertices[4] = {1.0f, 1.0f};
    screenVertices[5] = {-1.0f, 1.0f};

    vertexArrayObject = 0;
    glGenVertexArrays(1, &vertexArrayObject);
    labhelper::createAddAttribBuffer(vertexArrayObject,
                                     screenVertices,
                                     sizeof(screenVertices),
                                     0,
                                     2,
                                     GL_FLOAT);

    // Initialize shader programs, if renderShaderProgram is 0, the shader program could not
    // be loaded.
    renderShaderProgram = labhelper::loadShaderProgram("../src/shaders/test.vert",
                                                       "../src/shaders/test.frag",
                                                       false);
    fxShaderProgram = 0; // TO-DO Implement post process fx
}

RenderView::RenderView() : RenderView(1) {}

RenderView::~RenderView() {}

void RenderView::render() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, GAME_BOY_LCD_WIDTH, GAME_BOY_LCD_HEIGHT);
    glClearColor(0., 0., 0., 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(renderShaderProgram);

    glBindVertexArray(vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, VERTEX_AMOUNT);
}