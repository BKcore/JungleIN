#version 400

in vec4 fPosition;
in vec4 fNormal;
in vec4 fShadowcoord;
in vec4 fShadowcoordCascade;
in vec4 fLightDir;

uniform sampler2D texShadow;
uniform int cascadeShadow;
uniform sampler2D texShadowCascade;
uniform float shadowResolution;
uniform int shadowQuality;

uniform float tileSize;
uniform float heightRange;
uniform sampler2D texPlants;
uniform sampler2D texEarth;
uniform sampler2D texShatter;
uniform sampler2D texMoss;

const float TILE_RATIO = 70.0;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 FragThreshold;

float shadowLookup(in bool useCascade, in vec4 coord, in vec2 offset)
{
    float distanceFromLight = useCascade ? texture2D(texShadowCascade,coord.xy+offset/shadowResolution).z : texture2D(texShadow,coord.xy+offset/shadowResolution).z;
    bool s = (distanceFromLight < coord.z);
    return 1.0f-float(s);
}

float compShadow()
{
    if(fShadowcoord.w <= 0.0) return 1.0f;

    float shadow = 1.0f;
    vec4 shadowCoordinate;
    bool useCascade = false;

    if(all(lessThan(fShadowcoord.xy, vec2(0.999,0.999))) && all(greaterThan(fShadowcoord.xy, vec2(0.001,0.001))))
    {
        shadowCoordinate = fShadowcoord;
        useCascade = false;
    }
    else if(cascadeShadow == 1)
    {
        shadowCoordinate = fShadowcoordCascade;
        useCascade = true;
    }
    else
    {
        return 0.0;
    }

    // Used to lower moir? pattern and self-shadowing
    shadowCoordinate.z -= 0.001;

    if(shadowQuality == 1)
    {
        float sum = 0.0;

        sum += shadowLookup(useCascade, shadowCoordinate, vec2(-0.8, 0.0));
        sum += shadowLookup(useCascade, shadowCoordinate, vec2(-0.8, 0.0));
        sum += shadowLookup(useCascade, shadowCoordinate, vec2( 0.0,-0.8));
        sum += shadowLookup(useCascade, shadowCoordinate, vec2( 0.0, 0.8));
        sum += shadowLookup(useCascade, shadowCoordinate, vec2( 0.0, 0.0));
        sum += shadowLookup(useCascade, shadowCoordinate, vec2( 0.8, 0.8));
        sum += shadowLookup(useCascade, shadowCoordinate, vec2(-0.8,-0.8));
        sum += shadowLookup(useCascade, shadowCoordinate, vec2(-0.8, 0.8));
        sum += shadowLookup(useCascade, shadowCoordinate, vec2( 0.8,-0.8));

        shadow = sum / 9.0;
    }
    else
    {
        shadow = shadowLookup(useCascade, shadowCoordinate, vec2(0.0,0.0));
    }


    return shadow;
}

const float LOG2 = 1.442695;
const vec3 FOG_COLOR = vec3(0.42,0.67,0.88)*0.65;
const float FOG_DENSITY = 0.004;

vec3 compFog(vec3 finalColor)
{
    float z = gl_FragCoord.z / gl_FragCoord.w;
    float fogFactor = exp2( -FOG_DENSITY *
                           FOG_DENSITY *
                           z *
                           z *
                           LOG2 );
    fogFactor = clamp(fogFactor, 0.0, 1.0);

    return mix(FOG_COLOR, finalColor, fogFactor);
}

const float Ka = 0.1;
const float Kd = 2.0;
//const float Ks = 0.0;
//const float Shininess = 10.0;

// No specular calculation since we don't have good looking normal textures.
vec3 illumination(vec3 texel)
{
    float shadow = compShadow();

    vec3 n = normalize(fNormal.xyz);
    vec3 s = normalize(-fLightDir.xyz);
    //vec3 v = normalize(vec3(-fPosition));
    //vec3 h = normalize(v + s);

    return texel * (
                Ka +
                shadow * (
                    Kd * max( dot(s, n), 0.0 )
                ));
                //+ Ks * pow( max( dot(h,n), 0.0 ), Shininess)));
}

void main()
{
    vec2 texcoords = fPosition.xz/(tileSize/TILE_RATIO);
    float hStep = heightRange / 4.0;

    vec3 texel;
    if(fPosition.y < hStep)
        texel = texture2D(texShatter, texcoords).rgb;
    else if(fPosition.y < 2*hStep)
        texel = mix(texture2D(texShatter, texcoords),
                    texture2D(texEarth, texcoords),
                    (fPosition.y - hStep) / hStep).rgb;
    else if(fPosition.y < 3*hStep)
        texel = mix(texture2D(texEarth, texcoords),
                    texture2D(texMoss, texcoords),
                    (fPosition.y - 2*hStep) / hStep).rgb;
    else
        texel = texture2D(texMoss, texcoords).rgb;

    texel = texel * texel; // Fast gamma to linear (2.0 instead of 2.2)

    FragColor = vec4(sqrt(compFog(illumination(texel))),1.0);
    FragThreshold = vec4(0.0,0.0,0.0,1.0);
}
