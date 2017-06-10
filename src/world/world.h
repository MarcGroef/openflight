#ifndef INCLUDED_WORLD_H_
#define INCLUDED_WORLD_H_

#include <vector>
#include "../world_object/world_object.h"

class World
{
    std::vector<WorldObject> d_objects;
public:
    std::vector<WorldObject>& getObjects();
    void addObject(WorldObject const &object);
};

inline void World::addObject(WorldObject const &object)
{
    d_objects.push_back(object);
}

inline std::vector<WorldObject>& World::getObjects()
{
    return d_objects;
}
#endif