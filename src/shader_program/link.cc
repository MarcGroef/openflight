#include "shader_program.ih"

void ShaderProgram::link()
{
    d_id = glCreateProgram();
    cout << "shader program id = " << d_id << '\n';
    cout << "attaching shader id's " << d_vertexShader.id() << " and " << d_fragmentShader.id() << '\n';
    glAttachShader(d_id, d_vertexShader.id());
    glAttachShader(d_id, d_fragmentShader.id());
    cout << "attached shader id's " << d_vertexShader.id() << " and " << d_fragmentShader.id() << '\n';
    glLinkProgram(d_id);
    GLint linked;
    glGetProgramiv(d_id, GL_LINK_STATUS, &linked);
    if (linked == GL_TRUE)
    {
        cout << "linking shader programs successfull!\n";
    }else
    {
        cout << "something went wrong linking shaders...\n" << linked << '\n';
        int maxLen;
        int len;
        glGetProgramiv(d_id,GL_INFO_LOG_LENGTH,&maxLen);
        char* log = new char[maxLen];
        glGetProgramInfoLog(d_id,maxLen,&len,log);
        cout << len << '\n';
        cout << log << '\n';
        delete[] log;
    }
    glDeleteShader(d_vertexShader.id());
    glDeleteShader(d_fragmentShader.id());
}