#pragma once

#include <string>
#include "cinder/gl/Texture.h"
#include "cinder/Color.h"
#include "glm/vec3.hpp"

struct harmonica_segment_group
{
	std::string file_name;
	cinder::gl::Texture2dRef texture;
	cinder::ColorA color_mul;
	bool color_mul_changed;
	glm::bvec3 channels;

	harmonica_segment_group(std::string file_name, cinder::gl::Texture2dRef texture) :
		file_name(file_name),
		texture(texture),
		color_mul(cinder::ColorA::white()),
		color_mul_changed(false),
		channels(true, true, true)
	{
	}
};