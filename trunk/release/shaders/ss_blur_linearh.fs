#version 400

in vec2 uv;

uniform sampler2D texScene;
uniform vec2 resolution;

uniform float offset[3] = float[]( 0.0, 1.3846153846, 3.2307692308 );
uniform float weight[3] = float[]( 0.2270270270, 0.3162162162, 0.0702702703 );

layout (location = 0) out vec4 FragColor;

void main(void)
{
	FragColor = texture2D( texScene, uv ) * weight[0];
	for (int i=1; i<3; ++i) {
		vec2 samplePos = vec2(offset[i] * resolution.x, 0.0);
		FragColor += texture2D( texScene, uv + samplePos ) * weight[i];
		FragColor += texture2D( texScene, uv - samplePos ) * weight[i];
	}
}
