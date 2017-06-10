#ifndef INCLUDED_SHADER_PROGRAM_H_
#define INCLUDED_SHADER_PROGRAM_H_

#include "../shader/shader.h"
#include <string>



class ShaderProgram
{
    Shader d_vertexShader;
    Shader d_fragmentShader;
    GLuint d_id;
public:
    ShaderProgram(std::string const &fragmentShader, std::string const &vertexShader);
    void compile();
    void link();
    void bind();
    GLuint id();
};



inline GLuint ShaderProgram::id()
{
    return d_id;
}

inline ShaderProgram::ShaderProgram(std::string const &fragmentShader, std::string const &vertexShader):
    d_vertexShader(Shader(vertexShader, GL_VERTEX_SHADER)),
    d_fragmentShader(Shader(fragmentShader, GL_FRAGMENT_SHADER))
{   
}

inline void ShaderProgram::compile()
{
    d_vertexShader.compile();
    d_fragmentShader.compile();   
}



inline void ShaderProgram::bind()
{
}
#endif