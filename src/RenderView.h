/*
 * RenderView
 * This class handles the rendering of the Game Boy lcd.
 *
 * Author: Andreas Palmqvist
 */

#pragma once

#include <labhelper.h> // includes glew.h and glm.hpp

#include "Palette.h"
#include "gameboy/Definitions.h"

class RenderView {
private:
    const static int VERTEX_AMOUNT = 6;

    int screenMultiplier;
    glm::vec2 screenVertices[VERTEX_AMOUNT];
    GLuint vertexArrayObject;
    GLuint screenTexture;
    GLuint renderShaderProgram;
    GLuint fxShaderProgram;
    Palette palette;

public:
    RenderView(int screenMultiplier, Palette palette);
    RenderView();

    void initGL();
    void render() const;
    void setScreenTexture(uint8_t textureData[]);
    void setPalette(Palette palette);

    int getWidth() const;
    int getHeight() const;
};
