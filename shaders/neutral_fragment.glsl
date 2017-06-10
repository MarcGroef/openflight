#version 330

// A sampler for sampling the original image to blur
uniform sampler2D source;
uniform int width;
uniform int height;

// The output color
layout (location = 0) out vec4 fragColor;

void main()
{
    vec2 uv = gl_FragCoord.xy / vec2(width, height);

    fragColor = texture(source, uv).rgba;
}
