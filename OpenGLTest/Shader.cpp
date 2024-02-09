#include "Shader.h"

Shader::Shader(const std::string& fileName)
{
    program = glCreateProgram();
    GenerateShaders(fileName);
    AttachAllShaders();

    glBindAttribLocation(program, 0, "position");
    glBindAttribLocation(program, 1, "texCoord");
    glBindAttribLocation(program, 2, "normal");
    
    glLinkProgram(program);
    CheckShaderError(program, GL_LINK_STATUS, true, LINK_ERROR_MESSAGE);

    glValidateProgram(program);
    CheckShaderError(program, GL_VALIDATE_STATUS, true, VALIDATOR_ERROR_MESSAGE);

    uniforms[TRANSFORM_UNIFORM] = glGetUniformLocation(program, "transform");
}

Shader::~Shader()
{
    RemoveAllShaders();
    glDeleteProgram(program);
}

void Shader::Bind() const
{
    glUseProgram(program);
}

void Shader::Update(const Transform& transform, const Camera& camera)
{
    glm::mat4 model = camera.GetFiewProjection() * transform.GetModel();
    glUniformMatrix4fv(uniforms[TRANSFORM_UNIFORM], 1, GL_FALSE, &model[0][0]);
}

void Shader::GenerateShaders(const std::string& fileName)
{
    shaders[0] = CreateShaderHelper(LoadShader(fileName + ".vertex"), GL_VERTEX_SHADER);
    shaders[1] = CreateShaderHelper(LoadShader(fileName + ".fragment"), GL_FRAGMENT_SHADER);
}

void Shader::AttachAllShaders() const
{
    for (unsigned int i = 0; i < NUM_SHADERS; i++)
    {
        glAttachShader(program, shaders[i]);
    }
}

void Shader::RemoveAllShaders() const
{
    for (unsigned int i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(program, shaders[i]);
        glDeleteShader(shaders[i]);
    }
}

// Helper Methods
GLuint Shader::CreateShaderHelper(const std::string& text, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);

    if (shader == 0)
    {
        std::cerr << "Error: Shader creation failed!\n";
    }

    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringLengths[1];
    
    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringLengths[0] = static_cast<int>(text.length());

    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
    glCompileShader(shader);

    const std::string shaderCompilationErrorMessage = "Error: Shader compilation failed!\n";
    CheckShaderError(shader, GL_COMPILE_STATUS, false, shaderCompilationErrorMessage);
    
    return shader;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if (isProgram)
    {
        glGetProgramiv(shader, flag, &success);
    }
    else
    {
        glGetShaderiv(shader, flag, &success);
    }

    if (success == GL_FALSE)
    {
        if (isProgram)
        {
            glGetProgramInfoLog(shader, sizeof(error), nullptr, error);
        }
        else
        {
            glGetShaderInfoLog(shader, sizeof(error), nullptr, error);
        }

        std::cerr << errorMessage << ": '" << error << "'\n";
    }
}

std::string Shader::LoadShader(const std::string& fileName)
{
    std::ifstream file;
    file.open(fileName.c_str());

    std::string output;
    std::string line;

    if (file.is_open())
    {
        while (file.good())
        {
            std::getline(file, line);
            output.append(line + "\n");
        }
    }
    else
    {
        std::cerr << "Unable to load shader: " << fileName << "\n";
    }

    return output;
}
