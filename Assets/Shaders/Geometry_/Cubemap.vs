#version 300 es
precision highp float;

in vec3 position;

out vec3 texCoord0;

uniform mat4 viewProjection;

void main()
{
	gl_Position = (viewProjection * vec4(position, 1.0)).xyww;
	texCoord0 = position;
}

