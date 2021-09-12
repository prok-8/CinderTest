#pragma once

#include <string>
#include "cinder/gl/Texture.h"
#include "cinder/Color.h"

struct harmonica_segment_group
{
	std::string file_name;
	cinder::gl::Texture2dRef texture;
	cinder::Color color_mul;
	bool color_mul_changed;
};