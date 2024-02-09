#pragma once
#include <string>

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "ObjLoader.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texCoord;
    glm::vec3 normal;
};

class Mesh
{
public:
    Mesh(Vertex* vertices, int numVertices, unsigned int* indices, unsigned int numIndices);
    Mesh(const std::string& fileName);
    virtual ~Mesh();

    void Draw();
protected:

private:
    void InitMesh(const IndexedModel& model);
        
    enum
    {
        POSITION_VB,
        TEXCOORD_VB,
        NORMAL_VB,

        INDEX_VB,

        NUM_BUFFERS
    };
    
    GLuint vertexArrayObject;
    GLuint vertexArrayBuffers[NUM_BUFFERS];

    unsigned int drawCount;
    
};
