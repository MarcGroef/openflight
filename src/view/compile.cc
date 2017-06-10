#include "view.ih"

void View::compile()
{
    for (ShaderProgram &shader : d_shaders)
    {
        shader.compile();
    }
    setActiveShaderProgram(0);
}