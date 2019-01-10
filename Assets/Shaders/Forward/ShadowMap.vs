#version 300 es
precision highp float;

layout (location = 0) in vec3 position;

uniform mat4 shadowViewProjection;
uniform mat4 model;

void main()
{
	gl_Position = shadowViewProjection * model * vec4(position, 1.0);
}
