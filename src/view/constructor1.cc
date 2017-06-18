#include "view.ih"

View::View(size_t width, size_t height, World &world)
:
    d_winHeight(height),
    d_winWidth(width),
    d_activeShader(NULL),
    d_world(world),
    d_xRotation(-180),
    d_yRotation(0),
    d_fov(45.0)
{
    
}