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
#include "../texture/texture.h"

class RenderObject : public PhysicsModel
{
    std::vector<RenderObject> d_childs;
    
    std::vector<GLfloat> d_vertices;
    
    Texture* d_texture;
    size_t d_textureIdx;
    std::string d_textureFile;
    
    GLuint d_vboId;
    
    GLuint d_vaoId;
    GLuint d_eboId;
    
    GLuint d_vnbId;
    GLuint d_vnElId;
    
    bool d_loaded;
    bool d_hasUV;
    bool d_hasTexture;
    float d_scale;
    
public:
    RenderObject();
    RenderObject(glm::vec3 const &position, float scale, size_t textureIdx);
    ~RenderObject();
    void loadObject(ObjParser &&objParser);
    void loadObject(std::string const &objParser);
    void loadObject(std::vector<GLfloat> const &data);
    void setTextureIdx(size_t idx);
    void setTexture(Texture* texture);
    size_t getTextureIdx() const;
    void load();
    std::vector<RenderObject> &getChilds();
    void draw(GLuint shaderProgramId, glm::mat4 const &view, glm::vec3 const &lightpos);
    void drawSlave(GLuint shaderProgramId);
    void setTextureFile(std::string const &file);
    std::string const& getTextureFile();
};

inline void RenderObject::setTextureFile(std::string const &file)
{
    d_textureFile = file;
}

inline std::string const& RenderObject::getTextureFile()
{
    return d_textureFile;
}

inline void RenderObject::drawSlave(GLuint shaderProgramId)
{
    glBindVertexArray(d_vaoId);
    if(d_hasTexture)
        d_texture->bind();
    
    GLuint textId = glGetUniformLocation(shaderProgramId, "text");
    glUniform1i(textId, 0);
    
     //cout << d_vertIdc.size();
    glDrawArrays(GL_TRIANGLES,0,  (d_vertices.size() * 3)/ 8 );
    glBindVertexArray(0);
}



inline RenderObject::RenderObject()
:
    PhysicsModel(1.0, {0.,0,100}, {0,0,0}, {1,1,1}),
    d_textureIdx(0),
    d_loaded(false),
    d_hasUV(false),
    d_hasTexture(false),
    d_scale(1)
{
}

inline RenderObject::RenderObject(glm::vec3 const &position, float scale, size_t textureIdx)
:
    PhysicsModel(1.0,position, {0,0,0}, {1,1,1}),
    d_textureIdx(textureIdx),
    d_loaded(false),
    d_hasUV(false),
    d_hasTexture(true),
    d_scale(scale)
{
    
}

inline std::vector<RenderObject> &RenderObject::getChilds()
{
    return d_childs;
}
inline void RenderObject::setTextureIdx(size_t idx)
{
    d_textureIdx = idx;
    d_hasTexture = true;
}
inline void RenderObject::setTexture(Texture* texture)
{
    d_texture = texture;
}

inline size_t RenderObject::getTextureIdx() const
{
    return d_textureIdx;
}


inline void RenderObject::loadObject(std::string const &objfile)
{
    loadObject(ObjParser(objfile));
    
}

inline void RenderObject::loadObject(ObjParser &&objParser)
{

    d_vertices = std::move(objParser.d_objects[0].d_interleaved);
    d_hasUV = true;//objParser.d_uv.size() != 0;//TODO remove d_hasUV
    d_loaded = true;
    size_t nObjects = objParser.d_objects.size();
    for (size_t idx = 1; idx != nObjects; ++idx)
    {
        d_childs.push_back(RenderObject());
        d_childs[idx - 1].setTextureFile(objParser.d_objects[idx].d_material.d_map_Kd);
        std::cout << objParser.d_objects[idx].d_material.d_map_Kd << '\n';
        d_childs[idx - 1].setTextureIdx(0); //FIXME set correct texture
        d_childs[idx - 1].loadObject(objParser.d_objects[idx].d_interleaved);
    }
}

inline void RenderObject::loadObject(std::vector<GLfloat> const &data)
{

    d_vertices = data;
    d_hasUV = true;//objParser.d_uv.size() != 0;//TODO remove d_hasUV
    d_loaded = true;
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