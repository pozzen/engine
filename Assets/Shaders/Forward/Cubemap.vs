#version 300 es
precision highp float;

in vec3 position;

out vec3 texCoord0;

uniform mat4 cubeViewProjection;
uniform mat4 model;

void main()
{
	gl_Position = (cubeViewProjection * vec4((model * vec4(position, 0.0)).xyz, 1.0)).xyww;
	texCoord0 = position;
}
