#version 330 core
in vec3 normal;

uniform mat3 normalMat;
uniform vec3 lightPos;
uniform sampler2D text;
uniform bool useTexture;

//material:

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform vec3 Ke;
uniform float Ni;
uniform float d;
uniform int illum;

in vec2 uv;

out vec4 color;
void main()
{
    vec3 normnorm = normalize(normal);
    vec3 norm = normalize(normnorm * normalMat);
    
    vec3 lightDir = normalize(lightPos - gl_FragCoord.xyz);
    vec3 reflection = lightDir - 2 * dot(lightDir, norm) * norm;
    vec3 eye = vec3(-0, 1 , 0);
    
    float dotNormal = dot(lightDir, norm);
    float dotReflection = dot(reflection, eye);
    
    vec4 light = vec4(Ka, d);//vec4(1,1,1, 1.0);//vec4(1.0f, 0.0f, 0.0f, 1.0f);
    
    if(dotNormal > 0) 
    {
        light += dotNormal * vec4(Kd,1);//0.8;
        if(dotReflection > 0) 
            light += pow(dotReflection, Ni) * vec4(Ks,1);
    }
    
    if(useTexture)
    {
        color = texture2D(text, vec2(uv.x, 1 - uv.y)) * light;
    }
    else
    {
        color = light;
        //color.w = d;
    }
    //color.w = 0.2;
}