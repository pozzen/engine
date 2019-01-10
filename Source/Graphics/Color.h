#ifndef _COLOR_H_INCLUDED_
#define _COLOR_H_INCLUDED_

#include "Engine.h"

ST_NS_BEGIN

class Color
{
public:
	Color(vec3 components);
	Color(vec4 components);
	Color(float red, float green, float blue, float alpha = 1.0f);
	static Color fromHTMLNotation(const string &text);
	static Color fromHSL(float hue, float saturation, float lightness, float alpha = 1.0);

	static Color WHITE;
	static Color BLACK;
	static Color RED;
	static Color GREEN;
	static Color BLUE;

	vec4 _color;

	vec4 asVec4() const;
	vec3 asVec3() const;

	bool operator ==(const Color &other) const;

	static float hueToRGB(float p, float q, float t);

};

ST_NS_END

#endif // _COLOR_H_INCLUDED_
