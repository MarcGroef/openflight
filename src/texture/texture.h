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

inline void Texture::load()
{
    
    if(d_data.size() != 0 && !d_loaded)
    {
        std::cout << "Loading texture: data has " << d_data.size() << " floats\n";
        std::cout << "loading..\n";
        //glEnable(GL_TEXTURE_2D);

        glGenTextures(1, &d_id);
        std::cout << "generated texture id " << d_id << '\n';
        glBindTexture(GL_TEXTURE_2D, d_id);
        //;

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, d_width, d_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &d_data[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
       
        std::cout << "loaded texture\n";
        d_loaded = true;
    }
}

#endif