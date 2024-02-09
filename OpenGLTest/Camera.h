#pragma once

#include "glm/glm.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"

class Camera
{
public:
    Camera(const glm::vec3& position, float fov, float aspect, float zNear, float zFar);
    ~Camera() = default;

    glm::mat4x4 GetFiewProjection() const;
protected:
private:
    glm::mat4x4 perspective;
    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 up;
};
