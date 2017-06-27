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
    struct material
    {
        glm::vec3 d_Ka;
        glm::vec3 d_Kd;
        glm::vec3 d_Ks;
        glm::vec3 d_Ke;
        float d_Ni;
        float d_d;
        int d_illum;
    };
    
    material d_material;
    std::vector<RenderObject> d_childs;
    
    std::vector<GLfloat> d_vertices;
    
    Texture* d_texture;
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
    RenderObject(glm::vec3 const &position, float scale, std::string const &textureFile);
    ~RenderObject();
    void loadObject(ObjParser &&objParser);
    void loadObject(std::string const &objParser);
    void loadObject(std::vector<GLfloat> const &data);

    void setTexture(Texture* texture);
    void load();
    std::vector<RenderObject> &getChilds();
    void draw(GLuint shaderProgramId, glm::mat4 const &view, glm::vec3 const &lightpos, glm::vec3 const &campos);
    void drawSlave(GLuint shaderProgramId);
    void setTextureFile(std::string const &file);
    std::string const& getTextureFile() const;
    
private:
    void bindMaterial(GLuint pid);
};

inline void RenderObject::bindMaterial(GLuint shaderProgramId)
{
    GLuint matId = glGetUniformLocation(shaderProgramId, "Ka");
    glUniform3f(matId, d_material.d_Ka.x, d_material.d_Ka.y, d_material.d_Ka.z);
    
    matId = glGetUniformLocation(shaderProgramId, "Kd");
    glUniform3f(matId, d_material.d_Kd.x, d_material.d_Kd.y, d_material.d_Kd.z);
    
    matId = glGetUniformLocation(shaderProgramId, "Ks");
    glUniform3f(matId, d_material.d_Ks.x, d_material.d_Ks.y, d_material.d_Ks.z);
    
    matId = glGetUniformLocation(shaderProgramId, "Ke");
    glUniform3f(matId, d_material.d_Ke.x, d_material.d_Ke.y, d_material.d_Ke.z);
    
    matId = glGetUniformLocation(shaderProgramId, "Ni");
    glUniform1f(matId, d_material.d_Ni);
    
    matId = glGetUniformLocation(shaderProgramId, "d");
    glUniform1f(matId, d_material.d_d);
    
    matId = glGetUniformLocation(shaderProgramId, "illum");
    glUniform1i(matId, d_material.d_illum);
}

inline void RenderObject::setTextureFile(std::string const &file)
{
    if (file != "")
    {
        d_textureFile = file;
        d_hasTexture = true;
    }
}

inline std::string const& RenderObject::getTextureFile() const
{
    return d_textureFile;
}





inline RenderObject::RenderObject()
:
    PhysicsModel(1.0, {0.,0,100}, {0,0,0}, {1,1,1}),
    d_textureFile(""),
    d_loaded(false),
    d_hasUV(false),
    d_hasTexture(false),
    d_scale(1)
{
}

inline RenderObject::RenderObject(glm::vec3 const &position, float scale, std::string const &textureIdx)
:
    PhysicsModel(1.0,position, {0,0,0}, {1,1,1}),
    d_textureFile(textureIdx),
    d_loaded(false),
    d_hasUV(false),
    d_hasTexture(true),
    d_scale(scale)
{
    if(textureIdx == "")
        d_hasTexture = false;
}

inline std::vector<RenderObject> &RenderObject::getChilds()
{
    return d_childs;
}

inline void RenderObject::setTexture(Texture* texture)
{
    d_texture = texture;
}


inline void RenderObject::loadObject(std::string const &objfile)
{
    loadObject(ObjParser(objfile));
    
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
        //glDeleteVertexArrays(1, &d_vaoId); //TODO frees, check cpy & moves
        //glDeleteBuffers(1, &d_vboId);
        //glDeleteBuffers(1, &d_eboId);
    }
}


#endif