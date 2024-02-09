#include "Mesh.h"

#include <vector>

#include "ObjLoader.h"

Mesh::Mesh(Vertex* vertices, int numVertices, unsigned int* indices, unsigned int numIndices)
{
    IndexedModel model;
    //
    for (int i = 0; i < numVertices; i++)
    {
        model.positions.emplace_back(vertices[i].position);
        model.texCoords.emplace_back(vertices[i].texCoord);
        model.normals.emplace_back(vertices[i].normal);
    }
    //
    for (unsigned int i = 0; i < numIndices; i++)
    {
        model.indices.emplace_back(indices[i]);
    }
    //
    InitMesh(model);
}

Mesh::Mesh(const std::string& fileName)
{
    IndexedModel model = OBJModel(fileName).ToIndexedModel();
    InitMesh(model);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &vertexArrayObject);
}

void Mesh::Draw()
{
    glBindVertexArray(vertexArrayObject);

    glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, drawCount);
    
    glBindVertexArray(0);
}

void Mesh::InitMesh(const IndexedModel& model)
{
    drawCount = static_cast<unsigned>(model.indices.size());
    
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    
    glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);
    //
    // // setup buffer for positions
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), model.positions.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);
    //
    // // setup buffer for textCoords
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), model.texCoords.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, nullptr);

    // setup buffer for normals
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), model.normals.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, false, 0, nullptr);
    
    //
    // // setup buffer for vertices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), model.indices.data(), GL_STATIC_DRAW);
    //
    glBindVertexArray(0);
}
