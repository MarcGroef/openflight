#include "view.ih"

void View::render()
{
    for (WorldObject &obj : d_world.getObjects())
    {
        obj.draw();
    }
}