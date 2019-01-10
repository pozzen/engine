#version 300 es
precision highp float;

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec4 color;

out vec2 texCoord0;
out vec4 color0;
flat out int textureIndex;

uniform float screenWidth;
uniform float screenHeight;
uniform float maxSize;

void main()
{
	vec2 dim = vec2(screenWidth, screenHeight);
	vec2 posNegY = vec2(position.x, - position.y);

	gl_Position = vec4(posNegY * 2.0 / dim - vec2(1.0, -1.0), 0.0, 1.0);
	texCoord0 = vec2(mod(texCoord.x, maxSize), texCoord.y)/maxSize;
	textureIndex = int(texCoord.x);
	color0 = color;
}

