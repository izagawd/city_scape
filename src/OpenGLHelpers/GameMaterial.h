//
// Created by theiz on 11/16/2024.
//

#ifndef MATERIAL_H
#define MATERIAL_H
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
     *
     * @return the current texture multiplier
     */
    glm::vec2 getTextureMultiplier() const{
        return textureMultiplier;
    }

    /**
     *
     * sets the texture scale
     * NOTE: if texture scale is enabled, the texture scale will have a fixed size, no matter the scale of the
     * object
     */
    void setTextureMultiplier(glm::vec2 textureScale){
        this->textureMultiplier = textureScale;

    }


    GLuint getProgramId() const {
        return shader->getProgramId();
    }
    GameMaterial(wolf::Texture* texture,
        Shader* shader)
    : texture(texture), shader(shader) {

    }
    void bind();

    static void unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
        glUseProgram(0);
    }
};

#endif //MATERIAL_H
