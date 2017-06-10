#include "shader.ih"

Shader::Shader(string const &file, GLenum type)
:
    d_type(type)
{
    loadFromFile(file);
    cout << "read shader from file: " << d_shader << '\n';
}

