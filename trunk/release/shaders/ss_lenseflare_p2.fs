#version 400

in vec2 uv;

uniform sampler2D texScene;

uniform int flareSamples;
uniform float flareDispersal;
uniform float flareHaloWidth;
uniform vec3 flareChromaDispertion;

layout (location = 0) out vec4 FragColor;

vec3 textureDistorted(
	in sampler2D tex,
	in vec2 sampleCenter,
	in vec2 sampleVector,
	in vec3 distortion // per-channel distortion coeffs
) {
        /*return vec3(
		texture(texScene, sampleCenter + sampleVector * distortion.r).r,
		texture(texScene, sampleCenter + sampleVector * distortion.g).g,
		texture(texScene, sampleCenter + sampleVector * distortion.b).b
        );*/

        return texture2D(texScene, sampleCenter + sampleVector).rgb;
}

void main()
{
        vec2 imageCenter = vec2(0.5);
	vec2 sampleVector = (imageCenter - uv) * flareDispersal;
	vec2 haloVector = normalize(sampleVector) * flareHaloWidth;

        vec3 result = textureDistorted(texScene, uv + haloVector, haloVector, flareChromaDispertion).rgb;

	for (int i = 0; i < flareSamples; ++i) {
                vec2 offset = sampleVector * float(i);
		result += textureDistorted(texScene, uv + offset, offset, flareChromaDispertion).rgb;
	}

  	FragColor = vec4(result, 1.0f);
}
