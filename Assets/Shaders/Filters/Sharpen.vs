#version 130
//precision highp float;

attribute vec2 position;
attribute vec2 texCoord;

out vec2 texCoord0;

void main()
{
	gl_Position = vec4(position.xy, 0.0, 1.0);
	texCoord0 = texCoord;
}

