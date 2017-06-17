#ifndef INCLUDED_TEXTURE_MANAGER_H_
#define INCLUDED_TEXTURE_MANAGER_H_

#include <vector>
#include <string>

#include "../texture/texture.h"

class TextureManager
{
   std::vector<Texture> d_textures;
public:
   void addTexture(std::string const &textFile);
   Texture* getTexturePtr(size_t idx);
};

inline Texture* TextureManager::getTexturePtr(size_t idx)
{
    return &d_textures[idx];
}

inline void TextureManager::addTexture(std::string const &textFile)
{
    d_textures.push_back(Texture(textFile));
}

#endif
