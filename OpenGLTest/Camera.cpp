#include "Camera.h"

Camera::Camera(const glm::vec3& position, const float fov, const float aspect, const float zNear, const float zFar)
    : position(position)
{
    perspective = glm::perspective(fov, aspect, zNear, zFar);
    forward = glm::vec3(0, 0, 1);
    up = glm::vec3(0, 1, 0);
}

glm::mat4x4 Camera::GetFiewProjection() const
{
    return perspective * glm::lookAt(position, position + forward, up);
}
