#version 400

in vec2 uv;

uniform sampler2D texScene;
uniform sampler2D texGodrays;

layout (location = 0) out vec4 FragColor;


void main()
{
	//FragColor = vec4(uv.x,uv.y,0.0,1.0);
        vec3 texel = vec3(texture2D(texScene, uv));
        vec3 texelGodrays = vec3(texture2D(texGodrays, uv));
        FragColor = vec4( clamp(texel + texelGodrays , 0.0, 1.0), 1.0f );
}
