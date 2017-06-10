#include "shader.ih"

void Shader::compile()
{
    d_id = glCreateShader(d_type);
    cout << "shader id = " << d_id << '\n';
    const char* data = d_shader.c_str();
    int length = d_shader.size();
    glShaderSource(d_id, 1, &data, &length);
    glCompileShader(d_id);
    GLint compiled;
    glGetShaderiv(d_id, GL_COMPILE_STATUS, &compiled);
    if(compiled)
      cout << "shader " << d_id << " compiled successfull!\n";
    else
     cout << "shader " << d_id << " compile error!\n";
}