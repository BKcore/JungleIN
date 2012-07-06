#version 400

in vec2 uv;

uniform sampler2D texScene;

uniform vec3 flareThreshold;

layout (location = 0) out vec4 FragColor;


void main()
{
	// Flip / Downscale
	vec2 vu = -uv + 1.0;
	vec3 texel = vec3(texture(texScene, vu));

	// Threshold
        vec3 color = clamp((texel - flareThreshold), 0.0, 1.0);

  	FragColor = vec4( color, 1.0f );
}
