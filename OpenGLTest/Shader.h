#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>

#include "Camera.h"
#include "Transform.h"

class Shader
{
public:
    Shader(const std::string& fileName);
    virtual ~Shader();
    
    void GenerateShaders(const std::string& fileName);
    void AttachAllShaders() const;
    void RemoveAllShaders() const;
    void Bind() const;
    void Update(const Transform& transform, const Camera& camera);
    
    
protected:
    
private:
    Shader(const Shader& other) = default;
    void operator=(const Shader& other) const {}

    static constexpr unsigned int NUM_SHADERS = 2;

    static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
    static GLuint CreateShaderHelper(const std::string& text, GLenum shaderType);
    static std::string LoadShader(const std::string& fileName);

    const std::string LINK_ERROR_MESSAGE = "Error: Program linking failed!\n";
    const std::string VALIDATOR_ERROR_MESSAGE = "Error: Program is invalid!\n";

    enum
    {
        TRANSFORM_UNIFORM,

        NUM_UNIFORMS
    };
    
    GLuint program;
    GLuint shaders[NUM_SHADERS];
    GLint uniforms[NUM_UNIFORMS];
};
