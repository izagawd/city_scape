//
// Created by theiz on 11/16/2024.
//
#pragma once
#include <memory>


#include "../../wolf/W_Common.h"
#include "../../wolf/W_Texture.h"

class Shader {
    GLuint programId;
    public:
    GLuint getProgramId() const {
        return programId;
    }
    Shader(const std::string& vertexShader,const std::string& pixelShader) {
      programId =  wolf::LoadShaders( vertexShader, pixelShader);
    }
};
class GameMaterial {
private:

    wolf::Texture* texture;
    Shader* shader;




     glm::vec2 textureMultiplier = glm::vec2(1,1);
    public:
    /**
     *This is essentially the scale of the texture.
     * @return the current texture multiplier
     */
    glm::vec2 getTextureMultiplier() const{
        return textureMultiplier;
    }

    wolf::Texture* getTexture() const {
        return texture;
    }
    /**
     *
     * sets the texture multiplier
     * object
     */
    void setTextureMultiplier(glm::vec2 textureMultiplier){
        this->textureMultiplier = textureMultiplier;

    }


    GLuint getProgramId() const {
        return shader->getProgramId();
    }
    GameMaterial(wolf::Texture* texture,
        Shader* shader)
    : texture(texture), shader(shader) {

    }
    void bind();


};
