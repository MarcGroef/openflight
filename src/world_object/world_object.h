#ifndef INCLUDED_WORLD_OBJECT_H_
#define INCLUDED_WORLD_OBJECT_H_

#include "../render_object/render_object.h"
#include <string>


class WorldObject : public RenderObject
{
public:
    WorldObject();
    WorldObject(glm::vec3 const &position);
    WorldObject(glm::vec3 const &position, std::string const &obj, float scale, std::string const &textureFile);
    void loadTexture();
};

inline WorldObject::WorldObject()
:
    RenderObject()
{
    
}

inline WorldObject::WorldObject(glm::vec3 const &position, std::string const &obj, float scale, std::string const &textureFile)
:
    RenderObject(position, scale, textureFile)
{
    //loadTexture(textureFile);
    loadObject(obj);
}

inline WorldObject::WorldObject(glm::vec3 const &position)
:
    RenderObject(position, 1.0, "textures/moon.png")
{
    loadObject("objects/sphere.obj");
}



#endif