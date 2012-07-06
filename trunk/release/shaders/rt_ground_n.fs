#version 400

in vec3 fPosition;
in vec3 fNormal;
in vec4 fShadowcoord;
in vec3 fLightDir;

// Normal mapping
in vec3 fTangent;
in vec3 fBinormal;
uniform sampler2D texNormalEarth;
uniform sampler2D texNormalShatter;
uniform sampler2D texNormalMoss;

// Shadow mapping
uniform sampler2D texShadow;
uniform float shadowResolution;
uniform int shadowQuality;

uniform float tileSize;
uniform float heightRange;
uniform sampler2D texEarth;
uniform sampler2D texShatter;
uniform sampler2D texMoss;

const float TILE_RATIO = 80.0;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 FragThreshold;

vec3 computeNormal(vec3 texel)
{
    vec3 normalTex = normalize(texel * 2.0 - 1.0);
    mat3 tsb = mat3(normalize(fTangent), normalize(fBinormal), normalize(fNormal));

    return normalize(tsb * normalTex);
}

float shadowLookup(in vec4 coord, in vec2 offset)
{
    float distanceFromLight = texture2D(texShadow,coord.xy+offset/shadowResolution).z;

    float shadow = 1.0;
    if (fShadowcoord.w > 0.0)
        shadow = (float)(distanceFromLight >= coord.z);

    return shadow;
}

float computeShadow()
{
    float shadow = 1.0;
    if(all(lessThan(fShadowcoord.xy, vec2(1.0,1.0))) && all(greaterThan(fShadowcoord.xy, vec2(0.0,0.0))))
    {
        vec4 shadowCoordinate = fShadowcoord;// / fShadowcoord.w ;
        // Used to lower moiré pattern and self-shadowing
        shadowCoordinate.z -= 0.001;

        float sum = 0.0;
        if(shadowQuality == 1)
        {
            for(int i = -1; i < 2; ++i) for(int j = -1; j < 2; ++j)
            {
                sum += shadowLookup(shadowCoordinate, vec2(i*1.0,j*1.0));
            }

            shadow = sum / 9.0;
        }
        else
        {
            shadow = shadowLookup(shadowCoordinate, vec2(0.0,0.0));
        }
    }

    return shadow;
}

const float LOG2 = 1.442695;
const vec3 FOG_COLOR = vec3(0.796,0.918,0.949)*0.8;
const float FOG_DENSITY = 0.006;

vec3 computeFog(vec3 finalColor)
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

const float Ka = 0.5;
const float Kd = 0.7;
const float Ks = 0.4;
const float Shininess = 4.0;

vec3 illumination(vec3 texel, vec3 normal)
{
    float shadow = computeShadow();

    // [OPT] Early exit
    if(shadow < 0.05) return texel * Ka;

    vec3 n = normal;
    vec3 s = normalize(-fLightDir);
    vec3 v = normalize(-fPosition);
    vec3 h = normalize(v + s);

    vec3 color = texel * ( 
                    // Ambient
                    Ka +
                    // Diffuse
                    shadow * Kd * max(dot(s, n), 0.0)
                ) + // Specular
                    shadow * Ks * pow(max(dot(h,n), 0.0), Shininess);

    return color;
}

void main()
{
    vec2 texcoords = fPosition.xz/(tileSize/TILE_RATIO);
    float hStep = heightRange / 4.0;

    vec3 texel;
    vec3 texelNormal;
    float amount;

    if(fPosition.y < hStep)
    {
        texel = texture2D(texShatter, texcoords).rgb;
        texelNormal = texture2D(texNormalShatter, texcoords).rgb;
    }
    else if(fPosition.y < 2*hStep)
    {
        amount = (fPosition.y - hStep) / hStep;
        texel = mix(texture2D(texShatter, texcoords),
                    texture2D(texEarth, texcoords),
                    amount).rgb;
        texelNormal = mix(texture2D(texNormalShatter, texcoords),
                    texture2D(texNormalEarth, texcoords),
                    amount).rgb;
    }
    else if(fPosition.y < 3*hStep)
    {
        amount = (fPosition.y - 2*hStep) / hStep;
        texel = mix(texture2D(texEarth, texcoords),
                    texture2D(texMoss, texcoords),
                    amount).rgb;
        texelNormal = mix(texture2D(texNormalEarth, texcoords),
                    texture2D(texNormalMoss, texcoords),
                    amount).rgb;
    }
    else
    {
        texel = texture2D(texMoss, texcoords).rgb;
        texelNormal = texture2D(texNormalMoss, texcoords).rgb;
    }

    FragColor = vec4(
                    computeFog(
                        illumination(
                            texel, 
                            computeNormal(texelNormal)
                        )
                    )
                , 1.0);

    FragThreshold = vec4(0.0,0.0,0.0,1.0);

    //FragColor = texture2D(texDiffuse, fTexcoord);
}
