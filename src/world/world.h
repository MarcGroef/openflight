#ifndef INCLUDED_WORLD_H_
#define INCLUDED_WORLD_H_

#include <vector>
#include "../world_object/world_object.h"
#include <glm/glm.hpp>

class World
{
    std::vector<WorldObject> d_objects;
    glm::vec3 d_lightpos;
public:
    World();
    std::vector<WorldObject>& getObjects();
    void addObject(WorldObject &&object);
    void load();
    void render(GLuint shaderId, glm::mat4 const &view, glm::vec3 const &campos);
};

inline World::World()
:
    d_lightpos(glm::vec3(0,100,0))
{
}


inline void World::render(GLuint shaderId, glm::mat4 const &view, glm::vec3 const &campos)
{
    for (WorldObject &obj : d_objects)
    {
        //obj.applyForce({0, -5,0});
        //obj.applyTorque({0,0,0.02});
        obj.update(0.01f);
        obj.draw(shaderId, view, d_lightpos, campos);
    }
}


inline void World::load()
{
    for (WorldObject &obj : d_objects)
    {
        obj.load();
        
    }
}

inline void World::addObject(WorldObject &&object)
{
    d_objects.push_back(object);
}

inline std::vector<WorldObject>& World::getObjects()
{
    return d_objects;
}
#endif