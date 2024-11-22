//
// Created by theiz on 11/16/2024.
//

#include "GameMaterial.h"

void GameMaterial::bind() {


    glUseProgram(shader->getProgramId());
    texture->Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repeat horizontally
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repeat vertically


}
