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

class View
{
    size_t d_winHeight;
    size_t d_winWidth;
    bool d_loop;
    
    std::vector<ShaderProgram> d_shaders;
    ShaderProgram* d_activeShader;
    World d_world;
    

    
    glm::vec4 d_eye;
    glm::vec3 d_up;
    
    float d_xRotation;
    float d_yRotation;
    
    glm::mat4 d_view;
    
public:
    View(size_t width, size_t height, World& world);
    void initFramebuffer();
    void loop();
    void compile();
    void linkShaders();
    void addShaders(ShaderProgram const &shader);
    void setActiveShaderProgram(size_t idx);
    
private:
    void setProjection();
};

#include "view.implh"

#endif