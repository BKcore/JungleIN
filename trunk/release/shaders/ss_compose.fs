#version 400

in vec2 uv;

uniform sampler2D texScene;

layout (location = 0) out vec4 FragColor;


void main()
{
	//FragColor = vec4(uv.x,uv.y,0.0,1.0);
	vec3 texel = vec3(texture(texScene, uv));
        FragColor = vec4( texel, 1.0f );
}
