#include "render_object.ih"

void RenderObject::loadTriangle()
{
    #include "../../objects/teapod/teapod.vtc"
    d_vertices = teapod;
    /*{
         0.5f,  0.5f, 0.0f,  // Top Right
         0.5f, -0.5f, 0.0f,  // Bottom Right
        -0.5f, -0.5f, 0.0f,  // Bottom Left
        -0.5f,  0.5f, 0.0f   // Top Left 
    };*/
    
    
    //d_vertIdc// = 
    /*{  
        0, 1, 3,  // First Triangle
        1, 2, 3   // Second Triangle
    };*/
    for(size_t idx = 0; idx != d_vertices.size(); ++idx)
       d_vertIdc.push_back((int)idx);
    //cout << d_vertices.size() << '\n';
}