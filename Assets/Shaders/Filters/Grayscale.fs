#version 130
//precision highp float;

uniform sampler2D screenTexture;

in vec2 texCoord0;

out vec4 color;

void main()
{
	vec4 fragColor = texture(screenTexture, texCoord0);
	//float intensity = (fragColor.x + fragColor.y + fragColor.z) / 3.0;
	float intensity = 0.2126 * fragColor.r + 0.7152 * fragColor.g + 0.0722 * fragColor.b;
	color = vec4(intensity, intensity, intensity, 1.0);
}

