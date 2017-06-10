#ifndef INCLUDED_RENDER_OBJECT_H_
#define INCLUDED_RENDER_OBJECT_H_

#include <vector>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
//#include <GL/glu.h>
#include <GL/glext.h>

class RenderObject
{
    std::vector<GLfloat> d_vertices;
    std::vector<GLuint> d_vertIdc;
    
    GLuint d_vboId;
    GLuint d_vaoId;
    GLuint d_eboId;
    
public:
    ~RenderObject();
    void loadTriangle();//debug
    void load();
    void draw();
};

inline RenderObject::~RenderObject()
{
    glDeleteVertexArrays(1, &d_vaoId);
    glDeleteBuffers(1, &d_vboId);
    glDeleteBuffers(1, &d_eboId);
}

inline void RenderObject::loadTriangle()
{
    d_vertices = {
         0.5f,  0.5f, 0.0f,  // Top Right
         0.5f, -0.5f, 0.0f,  // Bottom Right
        -0.5f, -0.5f, 0.0f,  // Bottom Left
        -0.5f,  0.5f, 0.0f   // Top Left 
    };
    
    d_vertIdc =  {  
        0, 1, 3,  // First Triangle
        1, 2, 3   // Second Triangle
    };
}

#endif