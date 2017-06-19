#ifndef INCLUDED_TEXTURE_MANAGER_H_
#define INCLUDED_TEXTURE_MANAGER_H_

#include <map>
#include <string>

#include "../texture/texture.h"

class TextureManager
{
   std::map<std::string, Texture> d_textures;
public:
   void addTexture(std::string const &textFile);
   Texture* getTexturePtr(size_t idx);
   Texture* getTexturePtr(std::string const &textFile);
};



inline Texture* TextureManager::getTexturePtr(std::string const &textFile)
{
    //std::cout << "trying to access texture " << textFile << '\n';
    
    return &d_textures.at(textFile);
}

inline void TextureManager::addTexture(std::string const &textFile)
{
    //std::cout << "asking for adding texture " << textFile << '\n';
    if(d_textures.count(textFile) == 0)
    {
        //std::cout << "adding texture " << textFile << '\n';

        d_textures.emplace(textFile, Texture(textFile));
    } //else
        //std::cout << "texture was already there\n";
}

#endif
