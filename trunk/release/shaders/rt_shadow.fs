#version 400

in vec2 fTexcoord;

uniform sampler2D texAlpha;
uniform int useAlpha;


void main()
{
    if(useAlpha == 1)
    {
        float texelAlpha = texture2D(texAlpha, fTexcoord).r;
        if(texelAlpha < 0.8) discard;
    }
    // Depth is automatically stored
}
