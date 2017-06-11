#ifndef INCLUDED_TEXTURE_H_
#define INCLUDED_TEXTURE_H_

#include <vector>
#include <string>
#include <GL/gl.h>

class Texture
{
    GLuint d_id;
    std::vector<unsigned char> d_data;
    unsigned int d_width;
    unsigned int d_height;
public:
    Texture(std::string const &textureFile);
    void load();
};

inline void Texture::load()
{
    glGenTextures(1, &d_id);
    glBindTexture(GL_TEXTURE_2D, d_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, d_width, d_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, d_data.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

#endif