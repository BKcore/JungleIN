#version 400

in vec3 pos;

uniform samplerCube texCube;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 FragThreshold;

void main()
{
    FragColor = clamp(texture(texCube, pos)*1.4, 0.0f,1.0f);//vec4( pos, 1.0f );
    FragThreshold = vec4(0.0,0.0,0.0,1.0);
}
