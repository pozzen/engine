#version 130
//precision highp float;

uniform sampler2D screenTexture;

in vec2 texCoord0;

out vec4 color;

void main()
{
	float depthValue = texture(screenTexture, texCoord0).x;
	color = vec4(vec3(depthValue), 1.0);
}

