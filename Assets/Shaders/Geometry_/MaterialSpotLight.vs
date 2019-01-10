#version 300 es
precision highp float;
#include "Light.in"

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 color;
layout (location = 4) in vec3 tangent;
layout (location = 5) in vec3 bitangent;

out vec4 fragPosition;
out vec2 texCoord0;
out vec3 normal0;
out vec3 color0;

out vec3 tLightPosition;
out vec3 tLightDirection;
out vec3 tFragPosition;
out vec3 tCameraPosition;

layout (std140) uniform Matrices
{
	mat4 viewProjection;
	vec3 cameraPosition;
};
uniform mat4 model;

uniform SpotLight light;

void main()
{
	fragPosition = model * vec4(position, 1.0);
	gl_Position = viewProjection * model * vec4(position, 1.0);
	texCoord0 = texCoord;
	color0 = color;

	mat3 TBN = calcTBN(model, tangent, normal, bitangent);

	tLightPosition = TBN * light.position;
	tLightDirection = TBN * light.direction;
	tFragPosition  = TBN * fragPosition.xyz;
	tCameraPosition  = TBN * cameraPosition;
	normal0 = normalize(TBN * normalize(model * vec4(normal, 0.0)).xyz);
}
