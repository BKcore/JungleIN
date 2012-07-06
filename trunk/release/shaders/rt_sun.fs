#version 400

in vec3 fPosition;
in vec2 fTexcoord;

uniform sampler2D texDiffuse;
uniform sampler2D texAlpha;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 FragThreshold;

void main()
{
    float texelAlpha = texture2D(texAlpha, fTexcoord).r;

    vec3 texelDiffuse = texture2D(texDiffuse, fTexcoord).rgb;

    FragColor = vec4(texelDiffuse,texelAlpha);
    FragThreshold = FragColor;
    //FragColor = texture2D(texDiffuse, fTexcoord);
}
