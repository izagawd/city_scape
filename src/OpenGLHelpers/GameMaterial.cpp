//
// Created by theiz on 11/16/2024.
//

#include "GameMaterial.h"




static GLuint lastProgram = 0;
void GameMaterial::bind() {

    auto program = shader->getProgramId();

    if(lastProgram != program) {
        glUseProgram(program);
        lastProgram = program;
    }

    texture->Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repeat horizontally
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repeat vertically


}
