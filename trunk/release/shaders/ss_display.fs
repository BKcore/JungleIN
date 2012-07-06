#version 400

in vec2 uv;

uniform sampler2D texScene;
uniform vec3 gammaRGB;
uniform float aspect;

layout (location = 0) out vec4 FragColor;

/*
** Photoshop & misc math
** Blending modes, RGB/HSL/Contrast/Desaturate, levels control
**
** Romain Dura | Romz
** https://twitter.com/#!/romzr
*/
	/*
	** Desaturation
	*/
	vec4 Desaturate(vec3 color, float Desaturation)
	{
		vec3 grayXfer = vec3(0.3, 0.59, 0.11);
		vec3 gray = vec3(dot(grayXfer, color));
		return vec4(mix(color, gray, Desaturation), 1.0);
	}
	/*
	** Contrast, saturation, brightness
	** Code of this function is from TGM's shader pack
	** http://irrlicht.sourceforge.net/phpBB2/viewtopic.php?t=21057
	*/
	// For all settings: 1.0 = 100% 0.5=50% 1.5 = 150%
	vec3 ContrastSaturationBrightness(vec3 color, float brt, float sat, float con)
	{
		// Increase or decrease theese values to adjust r, g and b color channels seperately
		const float AvgLumR = 0.5;
		const float AvgLumG = 0.5;
		const float AvgLumB = 0.5;
		
		const vec3 LumCoeff = vec3(0.2125, 0.7154, 0.0721);
		
		vec3 AvgLumin = vec3(AvgLumR, AvgLumG, AvgLumB);
		vec3 brtColor = color * brt;
		vec3 intensity = vec3(dot(brtColor, LumCoeff));
		vec3 satColor = mix(intensity, brtColor, sat);
		vec3 conColor = mix(AvgLumin, satColor, con);
		return conColor;
	}
	/*
	** Float blending modes
	** Adapted from here: http://www.nathanm.com/photoshop-blending-math/
	** But I modified the HardMix (wrong condition), Overlay, SoftLight, ColorDodge, ColorBurn, VividLight, PinLight (inverted layers) ones to have correct results
	*/
	#define BlendLinearDodgef 			BlendAddf
	#define BlendLinearBurnf 			BlendSubstractf
	#define BlendAddf(base, blend) 		min(base + blend, 1.0)
	#define BlendSubstractf(base, blend) 	max(base + blend - 1.0, 0.0)
	#define BlendLightenf(base, blend) 		max(blend, base)
	#define BlendDarkenf(base, blend) 		min(blend, base)
	#define BlendLinearLightf(base, blend) 	(blend < 0.5 ? BlendLinearBurnf(base, (2.0 * blend)) : BlendLinearDodgef(base, (2.0 * (blend - 0.5))))
	#define BlendScreenf(base, blend) 		(1.0 - ((1.0 - base) * (1.0 - blend)))
	#define BlendOverlayf(base, blend) 	(base < 0.5 ? (2.0 * base * blend) : (1.0 - 2.0 * (1.0 - base) * (1.0 - blend)))
	#define BlendSoftLightf(base, blend) 	((blend < 0.5) ? (2.0 * base * blend + base * base * (1.0 - 2.0 * blend)) : (sqrt(base) * (2.0 * blend - 1.0) + 2.0 * base * (1.0 - blend)))
	#define BlendColorDodgef(base, blend) 	((blend == 1.0) ? blend : min(base / (1.0 - blend), 1.0))
	#define BlendColorBurnf(base, blend) 	((blend == 0.0) ? blend : max((1.0 - ((1.0 - base) / blend)), 0.0))
	#define BlendVividLightf(base, blend) 	((blend < 0.5) ? BlendColorBurnf(base, (2.0 * blend)) : BlendColorDodgef(base, (2.0 * (blend - 0.5))))
	#define BlendPinLightf(base, blend) 	((blend < 0.5) ? BlendDarkenf(base, (2.0 * blend)) : BlendLightenf(base, (2.0 *(blend - 0.5))))
	#define BlendHardMixf(base, blend) 	((BlendVividLightf(base, blend) < 0.5) ? 0.0 : 1.0)
	#define BlendReflectf(base, blend) 		((blend == 1.0) ? blend : min(base * base / (1.0 - blend), 1.0))
	/*
	** Vector3 blending modes
	*/
	// Component wise blending
	#define Blend(base, blend, funcf) 		vec3(funcf(base.r, blend.r), funcf(base.g, blend.g), funcf(base.b, blend.b))
	#define BlendNormal(base, blend) 		(blend)
	#define BlendLighten				BlendLightenf
	#define BlendDarken				BlendDarkenf
	#define BlendMultiply(base, blend) 		(base * blend)
	#define BlendAverage(base, blend) 		((base + blend) / 2.0)
	#define BlendAdd(base, blend) 		min(base + blend, vec3(1.0))
	#define BlendSubstract(base, blend) 	max(base + blend - vec3(1.0), vec3(0.0))
	#define BlendDifference(base, blend) 	abs(base - blend)
	#define BlendNegation(base, blend) 	(vec3(1.0) - abs(vec3(1.0) - base - blend))
	#define BlendExclusion(base, blend) 	(base + blend - 2.0 * base * blend)
	#define BlendScreen(base, blend) 		Blend(base, blend, BlendScreenf)
	#define BlendOverlay(base, blend) 		Blend(base, blend, BlendOverlayf)
	#define BlendSoftLight(base, blend) 	Blend(base, blend, BlendSoftLightf)
	#define BlendHardLight(base, blend) 	BlendOverlay(blend, base)
	#define BlendColorDodge(base, blend) 	Blend(base, blend, BlendColorDodgef)
	#define BlendColorBurn(base, blend) 	Blend(base, blend, BlendColorBurnf)
	#define BlendLinearDodge			BlendAdd
	#define BlendLinearBurn			BlendSubstract
	// Linear Light is another contrast-increasing mode
	// If the blend color is darker than midgray, Linear Light darkens the image by decreasing the brightness. If the blend color is lighter than midgray, the result is a brighter image due to increased brightness.
	#define BlendLinearLight(base, blend) 	Blend(base, blend, BlendLinearLightf)
	#define BlendVividLight(base, blend) 	Blend(base, blend, BlendVividLightf)
	#define BlendPinLight(base, blend) 		Blend(base, blend, BlendPinLightf)
	#define BlendHardMix(base, blend) 		Blend(base, blend, BlendHardMixf)
	#define BlendReflect(base, blend) 		Blend(base, blend, BlendReflectf)
	#define BlendGlow(base, blend) 		BlendReflect(blend, base)
	#define BlendPhoenix(base, blend) 		(min(base, blend) - max(base, blend) + vec3(1.0))
	#define BlendOpacity(base, blend, F, O) 	(F(base, blend) * O + blend * (1.0 - O))
	/*
	** Gamma correction
	*/
	#define GammaCorrection(color, gamma)								pow(color, 1.0 / gamma)
	/*
	** Levels control (input (+gamma), output)
	*/
	#define LevelsControlInputRange(color, minInput, maxInput)				min(max(color - vec3(minInput), vec3(0.0)) / (vec3(maxInput) - vec3(minInput)), vec3(1.0))
	#define LevelsControlInput(color, minInput, gamma, maxInput)				GammaCorrection(LevelsControlInputRange(color, minInput, maxInput), gamma)
	#define LevelsControlOutputRange(color, minOutput, maxOutput) 			mix(vec3(minOutput), vec3(maxOutput), color)
	#define LevelsControl(color, minInput, gamma, maxInput, minOutput, maxOutput) 	LevelsControlOutputRange(LevelsControlInput(color, minInput, gamma, maxInput), minOutput, maxOutput)

/**
 * Display shader
 */

vec3 Vignette(vec3 color)
{
	float tolerance = 0.3;
	float vignette_size = 0.6;
	vec2 powers = pow(abs(vec2(uv.x - 0.5,(uv.y - 0.5)/aspect)),vec2(2.0));
	float radiusSqrd = vignette_size*vignette_size;
	float gradient = smoothstep(radiusSqrd-tolerance, radiusSqrd+tolerance, powers.x+powers.y);

	return BlendOverlay(color, vec3(0.6-gradient));
}

void main()
{
    vec3 texel = texture2D(texScene, uv).rgb;
        vec3 color = Vignette(ContrastSaturationBrightness(texel, 1.0, 1.1, 1.1));
    //if(uv.x < 0.5)
        FragColor = vec4( color, 1.0f );
    //else
    //    FragColor = vec4( texel, 1.0f );
}
