#include "Transform.h"

Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
    : position(position), rotation(rotation), scale(scale) 
{
    
}

Transform::~Transform()
{
    
}

glm::mat4x4 Transform::GetModel() const
{
    const glm::mat4x4 positionMatrix = glm::translate(position);

    const glm::mat4x4 rotationXMatrix = glm::rotate(rotation.x, glm::vec3(1, 0, 0));
    const glm::mat4x4 rotationYMatrix = glm::rotate(rotation.y, glm::vec3(0, 1, 0));
    const glm::mat4x4 rotationZMatrix = glm::rotate(rotation.z, glm::vec3(0, 0, 1));
    
    const glm::mat4x4 scaleMatrix = glm::scale(scale);

    const glm::mat4x4 rotationMatrix = rotationZMatrix * rotationYMatrix * rotationXMatrix;

    return positionMatrix * rotationMatrix * scaleMatrix;
}
