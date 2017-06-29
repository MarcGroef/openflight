#ifndef INCLUDED_SCENE_H_
#define INCLUDED_SCENE_H_

#include "../world_object/world_object.h"
#include <vector>

class Scene : public WorldObject
{
  size_t d_width;
  size_t d_height;
  float d_deltaHeight;
  float d_deltaWidth;
public:
  Scene();
};

inline Scene::Scene()
{
  d_deltaHeight = 2.0 / d_height;
  d_deltaWidth = 2.0 / d_width;
}


#endif