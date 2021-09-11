#pragma once

#include "cinder/Color.h"
#include "cinder/Timeline.h"
#include "cinder/Tween.h"
#include "imgui/imgui.h"

namespace ImGui {

const ImU32 col_green = 0xff00ff00;
const ImU32 col_red = 0xff0000ff;

class ExtendedCheckbox
{
private:
	const float transition_time_ = 0.2f;
	
	const char* label_;
	bool state_;
	bool transitioning_;
	cinder::Timeline* timeline_;
	cinder::Anim<float> knob_position_;
	cinder::Anim<cinder::Color8u> knob_color_;
public:
	ExtendedCheckbox(const char* label, cinder::Timeline* timeline);
	bool Draw();
};
	
}