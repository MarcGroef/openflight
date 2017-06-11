#include "texture.ih"

Texture::Texture(string const &file)
{
    decode(d_data, d_width, d_height, file);
}