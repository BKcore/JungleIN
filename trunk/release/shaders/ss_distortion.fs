#version 400

/*
 * Radial calculation and fast noise blur based on work by Francois Tarlier and Martins Upitis
 * Vignette by Thibaut Despoulain.
 */

uniform sampler2D texScene;
uniform vec2 resolution;

in vec2 uv;

layout (location = 0) out vec4 FragColor;

float blurIntensity = 2.0;

vec2 rand(vec2 co) //needed for fast noise based blurring
{
        float noise1 =  (fract(sin(dot(co ,vec2(12.9898,78.233))) * 43758.5453));
        float noise2 =  (fract(sin(dot(co ,vec2(12.9898,78.233)*2.0)) * 43758.5453));
        return clamp(vec2(noise1,noise2),0.0,1.0);
}

vec3 blur(vec2 coords, float blurAmount)
{
        vec2 noise = rand(uv);
        float tolerance = 0.2;
        float vignette_size = 0.5;
        vec2 powers = pow(abs(vec2(uv.x - 0.5,uv.y - 0.5)),vec2(2.0));
        float radiusSqrd = vignette_size*vignette_size;
        float gradient = smoothstep(radiusSqrd-tolerance, radiusSqrd+tolerance, powers.x+powers.y);

        // [OPT] Early exit
        if(gradient < 0.07) return texture2D(texScene, uv).rgb;

        vec4 col = vec4(0.0);

        float X1 = coords.x + blurAmount * noise.x*0.004 * gradient;
        float Y1 = coords.y + blurAmount * noise.y*0.004 * gradient;
        float X2 = coords.x - blurAmount * noise.x*0.004 * gradient;
        float Y2 = coords.y - blurAmount * noise.y*0.004 * gradient;

        float invX1 = coords.x + blurAmount * ((1.0-noise.x)*0.004) * (gradient * 0.5);
        float invY1 = coords.y + blurAmount * ((1.0-noise.y)*0.004) * (gradient * 0.5);
        float invX2 = coords.x - blurAmount * ((1.0-noise.x)*0.004) * (gradient * 0.5);
        float invY2 = coords.y - blurAmount * ((1.0-noise.y)*0.004) * (gradient * 0.5);


        col += texture2D(texScene, vec2(X1, Y1))*0.1;
        col += texture2D(texScene, vec2(X2, Y2))*0.1;
        col += texture2D(texScene, vec2(X1, Y2))*0.1;
        col += texture2D(texScene, vec2(X2, Y1))*0.1;

        col += texture2D(texScene, vec2(invX1, invY1))*0.15;
        col += texture2D(texScene, vec2(invX2, invY2))*0.15;
        col += texture2D(texScene, vec2(invX1, invY2))*0.15;
        col += texture2D(texScene, vec2(invX2, invY1))*0.15;

        return col.rgb;
}

void main(void)
{
        vec3 inputDistort = blur(uv, blurIntensity);

        FragColor = vec4(inputDistort.r,inputDistort.g,inputDistort.b,1.0);
}
