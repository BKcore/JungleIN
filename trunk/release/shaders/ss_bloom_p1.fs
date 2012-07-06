#version 400

in vec2 uv;

uniform sampler2D texScene;

layout (location = 0) out vec4 FragColor;


void main()
{
        // Downscale
        vec3 texel = texture2D(texScene, uv).rgb;

        // desaturate
	/*const float AvgLumR = 0.5;
        const float AvgLumG = 0.5;
        const float AvgLumB = 0.5;
        const vec3 LumCoeff = vec3(0.2125, 0.7154, 0.0721);

        vec3 AvgLumin = vec3(AvgLumR, AvgLumG, AvgLumB);
        vec3 intensity = vec3(dot(texel, LumCoeff));
	vec3 satColor = mix(intensity, texel, 0.5);*/

	float grey = max(texel.r, max(texel.g, texel.b));


	// Threshold
        vec3 color = vec3(clamp(((grey) - 0.3), 0.0, 0.3));

        // Highlight boost
        //color = 1.0f-min(0.25+(1.0f-color), 1.0f);


  	FragColor = vec4( color, 1.0f );
}
