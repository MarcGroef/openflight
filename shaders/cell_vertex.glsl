#version 330
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 uv;

layout(location=0) in vec3 posAttr;     // vertex position
layout(location=1) in vec3 normalAttr;  // vertex normal
layout(location=2) in vec2 uvAttr;

out vec3 normal;

void main()
{
    gl_Position = projection * view * model * vec4(posAttr, 1.0);
    normal = normalAttr;
    uv = uvAttr;
}
