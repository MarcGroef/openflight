#ifndef INCLUDED_SHADER_H_
#define INCLUDED_SHADER_H_

#include <string>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
//#include <GL/glu.h>
#include <GL/glext.h>


class Shader
{
    GLenum d_type;
    GLuint d_id;
    std::string d_shader;
public:
    Shader(std::string const &file, GLenum type);
    void compile();
    GLuint const id() const;
private:
    void loadFromFile(std::string const &file);
};

inline GLuint const Shader::id() const
{
    return d_id;
}
#endif