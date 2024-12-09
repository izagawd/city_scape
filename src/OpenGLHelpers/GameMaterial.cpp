//
// Created by theiz on 11/16/2024.
//

#include "GameMaterial.h"



static GLuint lastBoundTexture = 0;
static GLuint lastProgram = 0;
void GameMaterial::bind() {

    auto program = shader->getProgramId();

    // caching the last program to avoid redundant program binding
    if(lastProgram != program) {
        glUseProgram(program);
        lastProgram = program;
    }

    auto textureId = texture->GetGLTexture();
    if(textureId != lastBoundTexture) {
        texture->Bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repeat horizontally
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repeat vertically
        lastBoundTexture = textureId;
    }



}
