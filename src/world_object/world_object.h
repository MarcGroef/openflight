#ifndef INCLUDED_WORLD_OBJECT_H_
#define INCLUDED_WORLD_OBJECT_H_

#include "../physics_model/physics_model.h"
#include "../render_object/render_object.h"

class WorldObject : public RenderObject, public PhysicsModel
{
public:
    WorldObject();
};

inline WorldObject::WorldObject()
:
    RenderObject(),
    PhysicsModel(1.0, {0,0,0}, {0,0,0}, {1,1,1})
{
    loadTriangle();
}

#endif