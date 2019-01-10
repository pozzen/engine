#version 300 es
precision highp float;

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;

out vec2 texCoord0;

void main()
{
	gl_Position = vec4(position*2.0 - vec2(1.0), 0.0, 1.0);
	texCoord0 = texCoord;
}

