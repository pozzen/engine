#version 130
//precision highp float;

uniform sampler2D screenTexture;

in vec2 texCoord0;

out vec4 color;

const float kOffset = 1.0/300.0;

const vec2 offsets[9] = vec2[](
	vec2(-kOffset, -kOffset),	vec2(0, -kOffset),	vec2(kOffset, -kOffset),
	vec2(-kOffset, 0),		vec2(0, 0),		vec2(kOffset, 0),
	vec2(-kOffset, kOffset),	vec2(0, -kOffset),	vec2(kOffset, kOffset)
);

const float edges[9] = float[9](
	1.0,  2.0, 1.0,
	2.0,  4.0, 2.0,
	1.0,  2.0, 1.0
);

void main()
{
	vec4 res = vec4(0.0, 0.0, 0.0, 0.0);
	for (int i = 0; i < 9; i++)
	{
		if (texCoord0.x+offsets[i].x < 0) continue;
		if (texCoord0.y+offsets[i].y < 0) continue;

		if (texCoord0.x+offsets[i].x > 1.0) continue;
		if (texCoord0.y+offsets[i].y > 1.0) continue;

		res += texture(screenTexture, texCoord0+offsets[i]) * edges[i]/16.0;
	}

	color = res;
}

