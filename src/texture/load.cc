#include "texture.ih"

void Texture::load()
{
    
    if(d_data.size() != 0 && !d_loaded)
    {
        //std::cout << "Loading texture: data has " << d_data.size() << " floats\n";
        //std::cout << "loading..\n";
        //glEnable(GL_TEXTURE_2D);

        glGenTextures(1, &d_id);
        //std::cout << "generated texture id " << d_id << '\n';
        glBindTexture(GL_TEXTURE_2D, d_id);
        //;

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, d_width, d_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &d_data[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
       
        //std::cout << "loaded texture\n";
        d_loaded = true;
    }
}