#pragma once

#include "cinder/Color.h"

struct Color8uInterp
{
	cinder::Color8u operator()(const cinder::Color8u& a, const cinder::Color8u& b, float f) const
	{
		uint8_t red = a.r + f * (b.r - a.r);
		uint8_t green = a.g + f * (b.g - a.g);
		uint8_t blue = a.b + f * (b.b - a.b);
		return cinder::Color8u(red, green, blue);
	}
};