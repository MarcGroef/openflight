#ifndef INCLUDED_VIEW_H_
#define INCLUDED_VIEW_H_

#include <armadillo>

#include <iostream>
#include <string>
#include <vector>

#include "../world/world.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
//#include <GL/glu.h>
#include <GL/glext.h>

#include "../shader_program/shader_program.h"

class View
{
    size_t d_winHeight;
    size_t d_winWidth;
    bool d_loop;
    
    std::vector<ShaderProgram> d_shaders;
    ShaderProgram* d_activeShader;
    World d_world;
    
    arma::fmat d_model;
    arma::fmat d_view;
    arma::fmat d_projection;
    
    arma::fmat d_eye;
    arma::fmat d_up;
    
    
public:
    View(size_t width, size_t height, World& world);
    void initFramebuffer();
    void loop();
    void render();
    void compile();
    void loadObjects();
    void linkShaders();
    void addShaders(ShaderProgram const &shader);
    void setActiveShaderProgram(size_t idx);
    
private:
    void setProjection();
};

inline void View::loadObjects()
{
    for (WorldObject &obj : d_world.getObjects())
    {
        obj.load();
    }
}


inline void View::setActiveShaderProgram(size_t idx)
{
    d_activeShader = &d_shaders[idx];
}

inline void View::linkShaders()
{
    for (ShaderProgram &sp : d_shaders)
        sp.link();
}
inline void View::addShaders(ShaderProgram const &shaders)
{
    d_shaders.push_back(shaders);
}
#endif