#version 130
//precision highp float;

uniform sampler2D screenTexture;

in vec2 texCoord0;

out vec4 color;

void main()
{
	vec2 cs = texCoord0;
	cs.x += sin(cs.x*200.0)/200.0;
	cs.y += cos(cs.y*200.0)/200.0;
	color = texture(screenTexture, cs);
}

