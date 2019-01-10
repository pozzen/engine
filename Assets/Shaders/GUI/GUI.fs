#version 300 es
precision highp float;

uniform sampler2D textures[1];

in vec2 texCoord0;
in vec4 color0;
flat in int textureIndex;

out vec4 color;

void main()
{
	color = color0*texture(textures[0], texCoord0);
}

