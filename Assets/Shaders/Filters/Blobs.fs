#version 300 es
precision highp float;

in vec2 texCoord0;
in vec3 points[5];

out vec4 color;

void main()
{
	color = vec4(0.0, 0.0, 0.0, 1.0);
	vec2 screenCoord = (texCoord0*2.0) - 1.0;
	for (int i = 0; i < 5; i++)
	{
		//float a = max(0.4 - distance(screenCoord, points[i].xy), 0.0);
		//color.x += pow(a, 0.4);

		float dist = distance(screenCoord, points[i].xy);
		if (dist < 0.4)
		{
			if (dist < 0.1) color.x = 1.0;
			else color.x += 1.0 - max(dist-0.1, 0.0)*10.0/3.0;
		}
	}
	//color = vec4(points[0], 1.0);
}

