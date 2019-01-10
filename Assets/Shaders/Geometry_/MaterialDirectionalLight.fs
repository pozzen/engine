#version 300 es
precision highp float;
#include "Light.in"
#include "Material.in"

in vec4 fragPosition;
in vec2 texCoord0;
in vec3 normal0;
in vec3 color0;

in mat3 TBN;

in vec3 tLightDirection;
in vec3 tFragPosition;
in vec3 tCameraPosition;

out vec4 color;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;
uniform sampler2D texture_normal;

uniform DirLight light;
uniform Material material;

// uniform mat4 model;

void main()
{
	vec3 diffuseColor = vec3(1.0);
	if (material.hasDiffuseMap)
		diffuseColor = vec3(texture2D(texture_diffuse, texCoord0));
	else
		diffuseColor = color0;

	vec3 specularColor = vec3(1.0);
	if (material.hasSpecularMap)
		specularColor = vec3(texture2D(texture_specular, texCoord0));

	vec3 normalColor = vec3(0.0);
	if (material.hasNormalMap)
		normalColor = texture2D(texture_normal, texCoord0).xyz;
		// normalColor = TBN * normalize(model * vec4(texture2D(texture_normal, texCoord0).xyz, 0.0)).xyz;

	vec3 result = calcDirLight(light, normal0, tLightDirection,
					tCameraPosition, tFragPosition,
					diffuseColor * material.diffuse,
					specularColor * material.specular,
					normalColor);

	color = vec4(result, 1.0f);
}
