#include "texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

Texture::Texture(const std::string &fileName) {

    int width, height, numComponents;
    //stbi_set_flip_vertically_on_load(1);
    unsigned char* imageData =  stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

    if(imageData == NULL)
        std::cerr << "The texture \"" << fileName << "\" could not be loaded." << '\n';

    glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_2D, this->texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    stbi_image_free(imageData);
}

void Texture::bind(unsigned int unit) {

    assert(unit >= 0 && unit <=31);

    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, this->texture);
}

Texture::~Texture() {
    glDeleteTextures(1, &this->texture);
}