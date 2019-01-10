#version 300 es
precision highp float;

uniform sampler2D texture1;

in vec2 texCoord0;

out vec4 color;

void main()
{
	color = texture(texture1, texCoord0);
}

