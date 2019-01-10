#version 300 es
precision highp float;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec2 texCoord0;

layout (std140) uniform Matrices
{
    mat4 viewProjection;
};
uniform mat4 model;

void main()
{
	gl_Position = viewProjection * model * vec4(position, 1.0);
	texCoord0 = texCoord;
}

