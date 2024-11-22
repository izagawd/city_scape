#pragma once
#include <glm/fwd.hpp>
#include <glm/ext/matrix_transform.hpp>

/**
 * Euler representation of rotation, since quarternion is a bit more complex to understand
 */
struct Rotation : public glm::vec3{

    glm::mat4 getRotationMatrix() const {
        glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));

        return  rotZ * rotY * rotX;

    }
    operator glm::vec3() const {
        return glm::vec3(x, y, z);
    }

    Rotation& operator=(const glm::vec3& inVec) {
        x = inVec.x;
        y = inVec.y;
        z = inVec.z;
        return *this;
    }
    Rotation() : glm::vec3() {}
    Rotation(glm::vec3 inVec) : glm::vec3(inVec) {}
    Rotation(float inX, float inY, float inZ) : glm::vec3(inX, inY, inZ) {}
    glm::vec3 getForward() {
        return  normalize(glm::vec3(getRotationMatrix()[2]));
    }
    glm::vec3 getUp() {
        return normalize(glm::vec3(getRotationMatrix()[1]));
    }
    glm::vec3 getRight() {
        return normalize(glm::vec3(getRotationMatrix()[0]));
    }
};


