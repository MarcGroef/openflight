#ifndef INCLUDED_WORLD_OBJECT_H_
#define INCLUDED_WORLD_OBJECT_H_

#include "../render_object/render_object.h"

class WorldObject : public RenderObject
{
public:
    WorldObject();
    WorldObject(glm::vec3 const &position);
};

inline WorldObject::WorldObject()
:
    RenderObject()
{
    loadObject("objects/sphere.obj");
}

inline WorldObject::WorldObject(glm::vec3 const &position)
:
    RenderObject(position)
{
    loadObject("objects/sphere.obj");
}

#endif