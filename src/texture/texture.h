#ifndef INCLUDED_TEXTURE_H_
#define INCLUDED_TEXTURE_H_

#include <vector>
#include <string>
#include <GL/gl.h>
#include <iostream>

class Texture
{
    GLuint d_id = 0;
    bool d_loaded = false;
    std::vector<unsigned char> d_data;
    unsigned int d_width = 0;
    unsigned int d_height = 0;
    std::string d_name;
public:
    
    Texture() = default;
    Texture(std::string const &textureFile);
    void load();
    void bind();
    GLuint id();
private:
};

inline void Texture::bind()
{
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, d_id);
}



inline GLuint Texture::id()
{
    return d_id;
}



#endif