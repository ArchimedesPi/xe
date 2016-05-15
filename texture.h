#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <GL/glew.h>

class Texture {
public:
    Texture();
    Texture &wrapping(GLenum wrapping);
    Texture &filtering(GLenum end, GLenum filtering);
    Texture &mipmapFiltering(GLenum end, GLenum filtering);
    Texture &generateMipmap();

    void bind();
    void unbind();

private:
    int width_, height_;
    unsigned char *image_; // this is loaded with SOIL

    GLuint texture_id;
};

#endif
