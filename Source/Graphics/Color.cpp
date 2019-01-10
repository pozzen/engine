#include "Color.h"

ST_NS_BEGIN

Color::Color(vec3 components):
	_color(components, 1.0)
{
}

Color::Color(vec4 components):
	_color(components)
{
}

Color::Color(float red, float green, float blue, float alpha):
	_color(red, green, blue, alpha)
{
}

Color Color::fromHTMLNotation(const string &text)
{
	int digits[4][2];
	digits[0][0] = digits[0][1] = 0;
	digits[1][0] = digits[1][1] = 0;
	digits[2][0] = digits[2][1] = 0;
	digits[3][0] = digits[3][1] = 15;

	int base = ((text[0] == '#')? 1: 0);

	unsigned int len = text.size();

	if (len == 3+base || len == 4+base)
	{
		for (unsigned int i = base; i < len; i++)
		{
			if (text[i] >= '0' && text[i] <= '9')
			{
				digits[i-base][0] = digits[i-base][1] = text[i]-'0';
			}
			else if (text[i] >= 'a' && text[i] <= 'f')
			{
				digits[i-base][0] = digits[i-base][1] = text[i]-'a' + 10;
			}
			else if (text[i] >= 'A' && text[i] <= 'F')
			{
				digits[i-base][0] = digits[i-base][1] = text[i]-'A' + 10;
			}
			else
			{
				cerr<<"Error parsing HTML color: "<<text<<". Unrecognized character '"<<text[i]<<"'."<<endl;
				return Color::BLACK;
			}
		}
	}
	else if (len == 6+base || len == 8+base)
	{
		for (unsigned int i = base; i < len; i++)
		{
			if (text[i] >= '0' && text[i] <= '9')
			{
				digits[(i-base)/2][(i-base)%2] = text[i]-'0';
			}
			else if (text[i] >= 'a' && text[i] <= 'f')
			{
				digits[(i-base)/2][(i-base)%2] = text[i]-'a' + 10;
			}
			else if (text[i] >= 'A' && text[i] <= 'F')
			{
				digits[(i-base)/2][(i-base)%2] = text[i]-'A' + 10;
			}
			else
			{
				cerr<<"Error parsing HTML color: "<<text<<". Unrecognized character '"<<text[i]<<"'."<<endl;
				return Color::BLACK;
			}
		}
	}
	else
	{
		cerr<<"Error parsing HTML color: "<<text<<". Incorrect number of digits."<<endl;
		return Color::BLACK;
	}

	return Color((digits[0][0]*16 + digits[0][1]) / 255.0,
				 (digits[1][0]*16 + digits[1][1]) / 255.0,
				 (digits[2][0]*16 + digits[2][1]) / 255.0,
			(digits[3][0]*16 + digits[3][1]) / 255.0);
}

Color Color::fromHSL(float hue, float saturation, float lightness, float alpha)
{
	if (saturation == 0)
	{
		return Color(lightness, lightness, lightness, alpha);
	}
	else
	{
		float q = (lightness > 0.5)?
					lightness * (1 + saturation):
					lightness + saturation - lightness * saturation;
		float p = 2 * lightness - q;

		return Color(hueToRGB(p, q, hue + 1.0/3),
					 hueToRGB(p, q, hue),
					 hueToRGB(p, q, hue - 1.0/3),
					 alpha);
	}
}

glm::vec4 Color::asVec4() const
{
	return _color;
}

glm::vec3 Color::asVec3() const
{
	return vec3(_color);
}

bool Color::operator ==(const Color &other) const
{
	return asVec4() == other.asVec4();
}

float Color::hueToRGB(float p, float q, float t)
{
	if (t < 0) t += 1;
	if (t > 1) t -= 1;
	if (t < 1.0/6.0) return p + (q - p) * 6 * t;
	if (t < 1.0/2.0) return q;
	if (t < 2.0/3.0) return p + (q - p) * (2.0/3 - t) * 6;
	return p;
}

Color Color::WHITE = Color(1.0f, 1.0f, 1.0f);
Color Color::BLACK = Color(0.0f, 0.0f, 0.0f);
Color Color::RED = Color(1.0f, 0.0f, 0.0f);
Color Color::GREEN = Color(0.0f, 1.0f, 0.0f);
Color Color::BLUE = Color(0.0f, 0.0f, 1.0f);

ST_NS_END
