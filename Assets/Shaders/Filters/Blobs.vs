#version 300 es
precision highp float;

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;

layout (std140) uniform Matrices
{
    mat4 viewProjection;
};
uniform mat4 model;
uniform vec3 orbits[5];
uniform float time;

out vec2 texCoord0;
out vec3 points[5];

void main()
{
	for (int i = 0; i < 5; i++)
	{
		float ct = cos(time * float(i));
		float st = sin(time * float(i));
		vec3 point = vec3(orbits[i].x*ct, orbits[i].y*st, orbits[i].z*st*ct);
		points[i] = (model * vec4(point, 1.0)).xyz;
	}
	gl_Position = vec4(position.xy, 0.0, 1.0);
	texCoord0 = texCoord;
}

