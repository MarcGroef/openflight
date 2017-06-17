#ifndef INCLUDED_VIEW_H_
#define INCLUDED_VIEW_H_


#include <iostream>
#include <string>
#include <vector>

#include "../world/world.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
//#include <GL/glu.h>
#include <GL/glext.h>

#include <glm/glm.hpp>

#include "../shader_program/shader_program.h"
#include "../texture_manager/texture_manager.h"
#include "../world_object/world_object.h"

class View
{
    size_t d_winHeight;
    size_t d_winWidth;
    bool d_loop;
    
    std::vector<ShaderProgram> d_shaders;
    ShaderProgram* d_activeShader;
    
    TextureManager d_textureManager;
    World d_world;
    

    
    glm::vec4 d_eye;
    glm::vec3 d_up;
    
    float d_xRotation;
    float d_yRotation;
    
    glm::mat4 d_view;
    
    GLuint d_frameBuffer;
    GLuint d_frameBufferTexture;
    GLuint d_frameBufferDepth;
    
public:
    View(size_t width, size_t height, World& world);
    void initFramebuffer();
    void loop();
    void compile();
    void linkShaders();
    void addShaders(ShaderProgram const &shader);
    void setActiveShaderProgram(size_t idx);
    void addTexture(std::string const &texureFile);
    void setTextures(); //link texture ptrs to renderObjects in d_world
private:
    void setProjection();
};

inline void View::setTextures()
{
    std::vector<WorldObject>& objects = d_world.getObjects();
    for (WorldObject &wo : objects)
    {
        wo.setTexture(d_textureManager.getTexturePtr(wo.getTextureIdx()));
    }
}

inline void View::addTexture(std::string const &textureFile)
{
    d_textureManager.addTexture(textureFile);
}

#include "view.implh"

#endif