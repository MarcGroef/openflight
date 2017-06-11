#ifndef INCLUDED_RENDER_OBJECT_H_
#define INCLUDED_RENDER_OBJECT_H_

#include <string> 
#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
//#include <GL/glu.h>
#include <GL/glext.h>
#include <glm/glm.hpp>

#include "../physics_model/physics_model.h"
#include "../obj_parser/obj_parser.h"

class RenderObject : public PhysicsModel
{
    std::vector<GLfloat> d_vertices;
    std::vector<GLuint> d_vertIdc;
    std::vector<GLuint> d_normIdc;
    std::vector<GLfloat> d_normals;
    
    GLuint d_vboId;
    
    GLuint d_vaoId;
    GLuint d_eboId;
    
    GLuint d_vnbId;
    GLuint d_vnElId;
    
    bool d_loaded;
    
public:
    RenderObject();
    RenderObject(glm::vec3 const &position);
    ~RenderObject();
    void loadTriangle();//debug
    void loadObject(ObjParser &&objParser);
    void loadObject(std::string const &objParser);
    void load();
    void draw(GLuint shaderProgramId, glm::mat4 const &view, glm::vec3 const &lightpos);
};

inline void RenderObject::loadObject(std::string const &objfile)
{
    loadObject(ObjParser(objfile));
    
}

inline void RenderObject::loadObject(ObjParser &&objParser)
{
    d_vertices = (objParser.d_vertices);
    //d_normals = (objParser.d_normals);
    //d_vertIdc = (objParser.d_vertIdc);
    //d_normIdc = objParser.d_normIdc;
    d_loaded = true;
    //std::cout << d_vertices.size() << " vertices, " << d_normals.size() << " normals, " << d_vertIdc.size() << " idc " << d_normIdc.size() << " normIdc\n";
}

inline RenderObject::RenderObject()
:
    PhysicsModel(1.0, {0.,0,100}, {0,0,0}, {1,1,1}),
    d_loaded(false)
{
}

inline RenderObject::RenderObject(glm::vec3 const &position)
:
    PhysicsModel(1.0,position, {0,0,0}, {1,1,1}),
    d_loaded(false)
{
}

inline RenderObject::~RenderObject()
{
    if(d_loaded)
    {
        //glDeleteVertexArrays(1, &d_vaoId);
        //glDeleteBuffers(1, &d_vboId);
        //glDeleteBuffers(1, &d_eboId);
    }
}


#endif