#include "texture.ih"

Texture::Texture(string const &file)
:
    d_loaded(false)
{
    if (file.size() != 0)
    {   
        cout << "loading " + file + "\n";
        decode(d_data, d_width, d_height, file);
        cout << "h: " << d_height << ", w: " << d_width << ", c:" << (d_data.size() / (d_height * d_width)) << '\n';
    }
}