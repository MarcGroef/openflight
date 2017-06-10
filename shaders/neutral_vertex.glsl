#version 330
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


layout(location=0) in vec3 vertex;

void main()
{
    gl_Position = vec4(vertex, 1);
}
