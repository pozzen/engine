#version 300 es
precision highp float;

uniform samplerCube skybox;

in vec3 texCoord0;

out vec4 color;

void main()
{
	color = texture(skybox, texCoord0);
}

