#version 130
//precision highp float;

uniform sampler2D screenTexture;

in vec2 texCoord0;

out vec4 color;

void main()
{
	color = texture(screenTexture, texCoord0);

	// Gamma Corrected
	//float gamma = 2.2;
	//vec3 fColor = pow(texture(screenTexture, texCoord0).xyz, vec3(1.0/gamma));
	//color = vec4(fColor, 1.0);

	// BGR
	//color = texture(screenTexture, texCoord0).zyxw;

	// Wavy paper
	//vec2 cs = texCoord0;
	//cs.x += sin(distance(cs.x, cs.y)*60.0)/60.0;
	//color = texture(screenTexture, cs);
}
