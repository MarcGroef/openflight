#version 330 core
in vec3 normal;

uniform mat3 normalMat;
uniform vec3 lightPos;
uniform sampler2D text;
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
    
    vec4 light = vec4(1,1,1, 1.0);//vec4(1.0f, 0.0f, 0.0f, 1.0f);
    
    if(dotNormal > 0) 
    {
        light += dotNormal * 0.8;
        if(dotReflection > 0) 
            light += pow(dotReflection, 0.00001) * 0.01;
    }
    
    //color = vec4(norm,1) * light;
    color = vec4(0.2,0.3,0.2,1) * light;
    //vec2 uv2 = vec2(1, 1);
    //color = texture2D(text, uv);// * light;
    color = texture2D(text, vec2(0.5,0.5)) * light;;
    color = vec4(uv, 1, 1);
}