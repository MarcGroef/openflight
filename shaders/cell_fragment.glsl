#version 330
uniform vec3 matColor;
uniform vec4 matProps;
uniform vec3 lightPos;
uniform mat3 normalMat;
uniform sampler2D texture;

in vec3 normal;
in vec2 uv;

out vec4 fColor;

#define SHADING_LEVELS 4

void main()
{
    vec3 normalizedNormal = normalize(normal * normalMat);

    vec3 lightDir = normalize(lightPos - gl_FragCoord.xyz);
    vec3 reflection = lightDir - 2 * dot(lightDir, normalizedNormal) * normalizedNormal;
    vec3 eye = vec3(0, 0, -1);

    float dotNormal = dot(lightDir, normalizedNormal);
    float dotReflection = dot(reflection, eye);
    float light = matProps.x;

    if(dotNormal > 0 ) {
        // Add diffuse term
        light += dotNormal * matProps.y;

        // Add specular term
        if(dotReflection > 0) light += pow(dotReflection, matProps.w) * matProps.z;
    }

    // Draw back outlines if this is an edge
    if(dot(normalizedNormal, eye) < -0.3) {
        // Use discrete steps in light level for a toon shading effect, using integer rounding
        float lightLevel = ((1 / float(SHADING_LEVELS)) * int(light * SHADING_LEVELS));

        fColor = texture2D(texture, uv) * lightLevel;

    } else {
        fColor = vec4(1, 1, 1 ,1);
    }
}
