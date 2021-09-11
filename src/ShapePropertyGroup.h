#pragma once

#include "Shape.h"
#include "ExtendedCheckbox.h"

class shape_property_group
{
protected:
	shape* data_;
	ImGui::ExtendedCheckbox rogue_cb_;

	void draw_internal()
	{
		rogue_cb_.Draw();
		if (data_->rogue)
			ImGui::BeginDisabled();
		ImGui::DragFloat2("Location", &data_->location);
		ImGui::ColorEdit3("Color", &data_->color);
	}
	
public:
	const char* name;
	shape_property_group(const char* name, shape* data, ci::Timeline* timeline) :
		data_(data),
		rogue_cb_("Rogue", &data->rogue, timeline),
		name(name)
	{
	}
	
	virtual void draw() = 0;	
};

class circle_property_group : public shape_property_group
{
public:
	circle_property_group(circle* data, ci::Timeline* timeline) :
		shape_property_group("Circle", data, timeline)
	{
	}
	
	void draw() override
	{
		draw_internal();
		ImGui::DragFloat("Radius", &static_cast<circle*>(data_)->radius);
		if (data_->rogue)
			ImGui::EndDisabled();
	}
};

class square_property_group : public shape_property_group
{
public:
	square_property_group(square* data, ci::Timeline* timeline) :
		shape_property_group("Square", data, timeline)
	{	
	}
	
	void draw() override
	{
		draw_internal();
		ImGui::DragFloat("Side", &static_cast<square*>(data_)->side);
		if (data_->rogue)
			ImGui::EndDisabled();
	}
};

class rectangle_property_group : public shape_property_group
{
public:
	rectangle_property_group(rectangle* data, ci::Timeline* timeline) :
		shape_property_group("Rectangle", data, timeline)
	{	
	}
	
	void draw() override
	{
		draw_internal();
		ImGui::DragFloat2("Size", &static_cast<rectangle*>(data_)->size);
		if (data_->rogue)
			ImGui::EndDisabled();
	}
};