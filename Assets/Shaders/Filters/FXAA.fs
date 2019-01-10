#version 300 es
precision highp float;

uniform sampler2D screenTexture;
uniform vec2 invTexSize;

in vec2 texCoord0;

out vec4 color;

#define FXAA_REDUCE_MIN (1.0/128.0)
#define FXAA_REDUCE_MUL (1.0/4.0)
#define FXAA_SPAN_MAX 4.0

void main()
{
	vec3 luma = vec3(0.299, 0.587, 0.114);
	vec4 texColor = texture2D(screenTexture, texCoord0);

	float lumaNW = dot(luma, texture2D(screenTexture, texCoord0 + (vec2(-1.0, -1.0) * invTexSize)).xyz);
	float lumaNE = dot(luma, texture2D(screenTexture, texCoord0 + (vec2(-1.0, 1.0) * invTexSize)).xyz);
	float lumaSW = dot(luma, texture2D(screenTexture, texCoord0 + (vec2(1.0, -1.0) * invTexSize)).xyz);
	float lumaSE = dot(luma, texture2D(screenTexture, texCoord0 + (vec2(1.0, 1.0) * invTexSize)).xyz);
	float lumaM = dot(luma, texColor.xyz);

	vec2 dir;
	dir.x = -((lumaNW + lumaNE) - (lumaSW + lumaSE));
	dir.y = ((lumaNW + lumaSW) - (lumaNE + lumaSE));

	float dirReduce = max((lumaNW + lumaNE + lumaSW + lumaSE) * (0.25 * FXAA_REDUCE_MUL), FXAA_REDUCE_MIN);
	float invDirMin = 1.0 / (min(abs(dir.x), abs(dir.y)) + dirReduce);

	dir = min(vec2(FXAA_SPAN_MAX, FXAA_SPAN_MAX),
			max(vec2(-FXAA_SPAN_MAX, -FXAA_SPAN_MAX),
				dir * invDirMin)) * invTexSize;

	vec3 resA = 0.5 * (
		texture2D(screenTexture, texCoord0 + dir * (1.0/3.0 - 0.5)).xyz +
		texture2D(screenTexture, texCoord0 + dir * (2.0/3.0 - 0.5)).xyz);

	vec3 resB = resA * 0.5 + 0.25 * (
		texture2D(screenTexture, texCoord0 + dir * -0.5).xyz +
		texture2D(screenTexture, texCoord0 + dir * 0.5).xyz);

	float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
	float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));

	float lumaB = dot(luma, resB);
	if ((lumaB < lumaMin) || (lumaB > lumaMax))
		color = vec4(resA, texColor.a);
	else
		color = vec4(resB, texColor.a);
}
