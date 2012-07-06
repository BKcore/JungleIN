#version 400

in vec2 uv;

uniform sampler2D texScene;
uniform sampler2D texBloom;

layout (location = 0) out vec4 FragColor;


void main()
{
	//FragColor = vec4(uv.x,uv.y,0.0,1.0);
        vec3 texel = vec3(texture2D(texScene, uv));
        vec3 texelBloom = vec3(texture2D(texBloom, uv));
  	FragColor = vec4( clamp(
  		texel
                + texelBloom
        , 0.0, 1.0), 1.0f );
}
