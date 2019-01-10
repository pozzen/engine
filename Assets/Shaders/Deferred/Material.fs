#version 300 es
precision highp float;
#include "../Geometry/Material.in"

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec4 fragPosition;
in vec2 texCoord0;
in vec3 normal0;
in vec3 color0;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;
uniform sampler2D texture_normal;

uniform Material material;

void main()
{
	vec3 diffuse = vec3(1.0);
	if (material.hasDiffuseMap)
		diffuse = vec3(texture2D(texture_diffuse, texCoord0));
	else
		diffuse = color0;

	float specular = material.specular;
	if (material.hasSpecularMap)
		specular *= vec3(texture2D(texture_specular, texCoord0)).r;

	vec3 normal = normal0;
	if (material.hasNormalMap)
		normal = vec3(texture2D(texture_normal, texCoord0));

    gPosition = fragPosition.xyz;
    gNormal = normal;
    gAlbedoSpec.rgb = diffuse;
    gAlbedoSpec.a = specular;
}
