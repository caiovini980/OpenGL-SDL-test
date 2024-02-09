#pragma once

#include "glm/glm.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"

class Transform
{
public:
    Transform(
        const glm::vec3& position = glm::vec3(0.f, 0.f, 0.f),
        const glm::vec3& rotation = glm::vec3(0.f, 0.f, 0.f),
        const glm::vec3& scale = glm::vec3(1.f, 1.f, 1.f));
    
    ~Transform();

    glm::mat4x4 GetModel() const;
    
    glm::vec3& GetPosition() { return position; }
    glm::vec3& GetRotation() { return rotation; }
    glm::vec3& GetScale() { return scale; }

    void SetPosition(const glm::vec3& newPosition) { position = newPosition; }
    void SetRotation(const glm::vec3& newRotation) { rotation = newRotation; }
    void SetScale(const glm::vec3& newScale) { scale = newScale; }

protected:
    
private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};
