#pragma once

//#include "cinder/CinderImGui.h"
#include "Shape.h"

template<typename T>
void draw_properties(T& object)
{
}

template<>
inline void draw_properties(shape& object)
{
	ImGui::DragFloat2("Location", &object.location);
	ImGui::ColorEdit3("Color", &object.color);
}

template<>
inline void draw_properties(circle& object)
{
	draw_properties<shape>(object);
	ImGui::DragFloat("Radius", &object.radius);
}

template<>
inline void draw_properties<square>(square& object)
{
	draw_properties<shape>(object);
	ImGui::DragFloat("Side", &object.side);
}

template<>
inline void draw_properties<rectangle>(rectangle& object)
{
	draw_properties<shape>(object);
	ImGui::DragFloat2("Size", &object.size);
}