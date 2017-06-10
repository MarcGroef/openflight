#version 330
uniform vec3 matColor;
uniform vec4 matProps;
uniform vec3 lightPos;
uniform mat3 normalMat;
uniform sampler2D texture;

in vec3 normal;
in vec2 uv;

out vec4 fColor;

void main()
{
    vec3 normalizedNormal = normalize(normal * normalMat);

    vec3 lightDir = normalize(lightPos - gl_FragCoord.xyz);
    vec3 reflection = lightDir - 2 * dot(lightDir, normalizedNormal) * normalizedNormal;
    vec3 eye = vec3(0, 0, -1);

    float dotNormal = dot(lightDir, normalizedNormal);
    float dotReflection = dot(reflection, eye);
    float light = matProps.x;

    if(dotNormal > 0) {
        light += dotNormal * matProps.y;
        if(dotReflection > 0) light += pow(dotReflection, matProps.w) * matProps.z;
    }

    fColor = texture2D(texture, uv) * light;
}
