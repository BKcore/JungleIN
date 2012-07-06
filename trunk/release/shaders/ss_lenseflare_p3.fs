#version 400

in vec2 uv;

uniform sampler2D texScene;
uniform sampler2D texFlare;
uniform sampler2D texDirt;
uniform float flareIntensity;

layout (location = 0) out vec4 FragColor;


void main()
{
	//FragColor = vec4(uv.x,uv.y,0.0,1.0);
	vec3 texel = vec3(texture(texScene, uv));
	vec3 texelFlare = vec3(texture(texFlare, uv));
	vec3 texelDirt = vec3(texture(texDirt, uv));
  	FragColor = vec4( clamp(
  		texel
                + texelDirt * texelFlare * 1.4 * flareIntensity
                + texelFlare * 0.10 * flareIntensity
        , 0.0, 1.0), 1.0f );
}
