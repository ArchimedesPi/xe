#include <SOIL.h>

#include "texture.h"


Texture::Texture() {
    glGenTextures(1, &texture_id);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, texture_id);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
