#version 300 es
precision highp float;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

in vec2 texCoord0;
out vec4 color;

void main()
{
    // Retrieve data from G-buffer
    vec3 FragPos = texture(gPosition, texCoord0).rgb;
    vec3 Normal = texture(gNormal, texCoord0).rgb;
    vec3 Albedo = texture(gAlbedoSpec, texCoord0).rgb;
    float Specular = texture(gAlbedoSpec, texCoord0).a;

	if (FragPos.z <= 0.99) discard;

    // // Then calculate lighting as usual
    // vec3 lighting = Albedo * 0.1; // hard-coded ambient component
    // vec3 viewDir = normalize(viewPos - FragPos);
    // for(int i = 0; i < NR_LIGHTS; ++i)
    // {
    //     // Diffuse
    //     vec3 lightDir = normalize(lights[i].Position - FragPos);
    //     vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Albedo * lights[i].Color;
    //     lighting += diffuse;
    // }

    color = vec4(Albedo * (1.0 + Specular), 1.0);
}
