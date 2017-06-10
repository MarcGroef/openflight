#include "view.ih"

View::View(size_t width, size_t height, World &world)
:
    d_winHeight(height),
    d_winWidth(width),
    d_activeShader(NULL),
    d_world(world),
    d_model(fmat(4,4)),
    d_view(fmat(4,4)),
    d_projection(fmat(4,4))
{
    
}