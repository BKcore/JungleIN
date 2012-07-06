/*!
 * Based on http://http.developer.nvidia.com/GPUGems3/gpugems3_ch13.html
 */

#version 400

in vec2 uv;
uniform vec3 lightPos;
uniform sampler2D texScene;

layout (location = 0) out vec4 FragColor;

const float exposure = 0.6;
const float decay = 0.93;
const float density = 0.96;
const float weight = 0.4;
const int NUM_SAMPLES = 20;
const float clampMax = 1.0;

void main()
{	
    if(any(greaterThan(lightPos.xy, vec2(1.5,1.5))) || any(lessThan(lightPos.xy, vec2(-0.5,-0.5))))
            discard;

    vec2 deltaTextCoord = vec2(uv - lightPos.xy);
    deltaTextCoord *= 1.0 /  float(NUM_SAMPLES) * density;
    vec2 coord = uv;
    float illuminationDecay = 1.0;

    for(int i=0; i < NUM_SAMPLES ; i++)
    {
            coord -= deltaTextCoord;
            vec4 texel = texture2D(texScene, coord);
            texel *= illuminationDecay * weight;

            FragColor += texel;

            illuminationDecay *= decay;
    }
    FragColor *= exposure;
    FragColor = clamp(FragColor, 0.0, clampMax) * vec4(1.0,1.0,0.94, 1.0);
}
