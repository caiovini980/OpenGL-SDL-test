#include "Texture.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION

#include "STB_IMAGE/stb_image.h"
#include "cassert"

Texture::Texture(const std::string& fileName)
{
    int width;
    int height;
    int numComponents;
    
    // load the texture data
    stbi_uc* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

    if (imageData == nullptr)
    {
        std::cerr << "Texture loading failed for: " << fileName << "\n";
    }
    
    // get space for the texture and bind it as a texture2D
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    // Handle when texture go out of bounds
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    // handle reducing or expanding the texture (minification and magnification)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    
    // delete the texture data
    stbi_image_free(imageData);
}

Texture::~Texture()
{
    glDeleteTextures(1, &texture);
}

void Texture::Bind(unsigned unit)
{
    assert(unit <= 31);
    
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, texture);
}
